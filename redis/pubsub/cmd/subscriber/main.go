package main

import (
	"context"
	"log"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"

	"github.com/go-redis/redis/v8"
)

func main() {
	redisAddr := os.Getenv("SUBSCRIBER_REDIS_ADDR")
	channel := os.Getenv("SUBSCRIBER_CHANNEL_NAME")

	client := redis.NewClient(&redis.Options{
		Addr:        redisAddr,
		DialTimeout: 10 * time.Second,
	})

	ctx := context.Background()
	_, err := client.Ping(ctx).Result()
	if err != nil {
		log.Fatalf("failed to ping redis: %s", err)
	}

	defer client.Close()

	sub := client.Subscribe(ctx, channel)
	iface, err := sub.Receive(ctx)
	if err != nil {
		log.Printf("failed to receive on subscription: %s", err)
		return
	}

	switch iface.(type) {
	case *redis.Subscription:
		log.Printf("subscribed on channel %s", channel)
	case *redis.Message:
	case *redis.Pong:
	default:
		log.Printf("unexpected response on subscribe: %v", iface)
	}

	var wg sync.WaitGroup
	wg.Add(1)

	cancelCtx, cancel := context.WithCancel(context.Background())

	go func() {
		defer wg.Done()

		ch := sub.Channel()

		for {
			select {
			case <-cancelCtx.Done():
				return
			case m, ok := <-ch:
				if !ok {
					return
				}

				log.Printf("got from channel %s: %s", m.Channel, m.Payload)
			}
		}
	}()

	sigint := make(chan os.Signal, 1)
	signal.Notify(sigint, syscall.SIGINT, syscall.SIGTERM)
	<-sigint

	cancel()
	if err := client.Close(); err != nil {
		log.Printf("failed to close connection to Redis: %s", err)
	}

	wg.Wait()
}

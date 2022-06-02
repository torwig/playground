package main

import (
	"context"
	"log"
	"math/rand"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"

	"github.com/go-redis/redis/v8"
)

const (
	evenNumbersChannel = "even_numbers"
	oddNumbersChannel  = "odd_numbers"
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

func main() {
	redisAddr := os.Getenv("PUBLISHER_REDIS_ADDR")

	client := redis.NewClient(&redis.Options{
		Addr:        redisAddr,
		DialTimeout: 10 * time.Second,
	})

	ctx := context.Background()
	_, err := client.Ping(ctx).Result()
	if err != nil {
		log.Fatalf("failed to ping Redis: %s", err)
	}

	defer client.Close()

	var wg sync.WaitGroup
	wg.Add(1)

	cancelCtx, cancel := context.WithCancel(context.Background())

	go func() {
		defer wg.Done()

		ticker := time.NewTicker(1 * time.Second)
		defer ticker.Stop()

		for {
			select {
			case <-cancelCtx.Done():
				return
			case <-ticker.C:
				number := rand.Int63()

				var channel string
				if number%2 == 0 {
					channel = evenNumbersChannel
				} else {
					channel = oddNumbersChannel
				}

				if err := client.Publish(ctx, channel, number).Err(); err != nil {
					log.Printf("failed to publish to channel %s: %s", channel, err)
					return
				}

				log.Printf("published number %d to channel %s", number, channel)
			}
		}
	}()

	sigint := make(chan os.Signal, 1)
	signal.Notify(sigint, syscall.SIGINT, syscall.SIGTERM)
	<-sigint

	cancel()

	wg.Wait()
}

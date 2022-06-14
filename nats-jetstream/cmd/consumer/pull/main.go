package main

import (
	"context"
	"errors"
	"log"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"

	"github.com/nats-io/nats.go"
)

func main() {
	serverAddr := os.Getenv("CONSUMER_NATS_ADDRESS")
	animal := os.Getenv("CONSUMER_ANIMAL_NAME")

	client, err := nats.Connect(serverAddr)
	if err != nil {
		log.Fatalf("failed to connect to nats server: %s", err)
	}
	defer client.Close()

	jsCtx, err := client.JetStream()
	if err != nil {
		log.Printf("failed to get JetStream context: %s", err)
		return
	}

	subject := "animals." + animal

	sub, err := jsCtx.PullSubscribe(subject, "pull_consumer", nats.StartSequence(4000))
	if err != nil {
		log.Printf("failed to create pull consumer: %s", err)
		return
	}

	ctx, cancel := context.WithCancel(context.Background())

	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()

		ticker := time.NewTicker(10 * time.Second)
		defer ticker.Stop()

		for {
			select {
			case <-ctx.Done():
				return
			case <-ticker.C:
				msgs, err := sub.Fetch(10)
				if err != nil && !errors.Is(err, nats.ErrTimeout) {
					log.Printf("failed to fetch messages: %s", err)
					return
				}

				for _, m := range msgs {
					log.Printf("fetched message: %s", string(m.Data))
				}
			}
		}
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	cancel()
	wg.Wait()

	if err := sub.Unsubscribe(); err != nil {
		log.Printf("failed to unsubscribe from subject '%s': %s", subject, err)
		return
	}

	if err := sub.Drain(); err != nil {
		log.Printf("failed to drain: %s", err)
	}
}

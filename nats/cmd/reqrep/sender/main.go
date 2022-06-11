package main

import (
	"context"
	"log"
	"math/rand"
	"os"
	"os/signal"
	"strconv"
	"sync"
	"syscall"
	"time"

	"github.com/nats-io/nats.go"
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

func main() {
	serverAddr := os.Getenv("SENDER_NATS_ADDRESS")
	subject := os.Getenv("SENDER_SUBJECT")

	client, err := nats.Connect(serverAddr)
	if err != nil {
		log.Fatalf("failed to connect to nats server: %s", err)
	}
	defer client.Close()

	ctx, cancel := context.WithCancel(context.Background())

	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()

		ticker := time.NewTicker(5 * time.Second)
		defer ticker.Stop()

		for {
			select {
			case <-ctx.Done():
				return
			case <-ticker.C:
				body := strconv.FormatInt(time.Now().Unix(), 10)

				msg, err := client.Request(subject, []byte(body), 2*time.Second)
				if err != nil {
					log.Printf("failed to send request: %s", err)
					continue
				}

				log.Printf("published to '%s': %s", subject, body)
				log.Printf("got as reply: %s", string(msg.Data))
			}
		}
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	cancel()
	wg.Wait()
}

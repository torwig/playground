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
	replySubject := os.Getenv("SENDER_REPLY_SUBJECT")

	client, err := nats.Connect(serverAddr)
	if err != nil {
		log.Fatalf("failed to connect to nats server: %s", err)
	}
	defer client.Close()

	sub, err := client.Subscribe(replySubject, func(msg *nats.Msg) {
		log.Printf("got as reply: %s", string(msg.Data))
	})
	if err != nil {
		log.Printf("failed to subscribe to '%s': %s", replySubject, err)
		return
	}

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
				msg := nats.Msg{
					Subject: subject,
					Reply:   replySubject,
					Data:    []byte(body),
				}

				if err := client.PublishMsg(&msg); err != nil {
					log.Printf("failed to publish message: %s", err)
					return
				}

				log.Printf("published to '%s': %s", subject, body)
			}
		}
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	_ = sub.Unsubscribe()
	_ = sub.Drain()

	cancel()
	wg.Wait()
}

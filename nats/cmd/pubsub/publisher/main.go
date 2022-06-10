package main

import (
	"context"
	"fmt"
	"log"
	"math/rand"
	"os"
	"os/signal"
	"strconv"
	"strings"
	"sync"
	"syscall"
	"time"

	"github.com/nats-io/nats.go"
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

func main() {
	serverAddr := os.Getenv("PUBLISHER_NATS_ADDRESS")
	tokens := os.Getenv("PUBLISHER_TOKEN_LIST")
	tokenList := strings.Split(tokens, ",")

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

		ticker := time.NewTicker(1 * time.Second)
		defer ticker.Stop()

		for {
			select {
			case <-ctx.Done():
				return
			case <-ticker.C:
				body := strconv.FormatInt(time.Now().Unix(), 10)
				subject := createSubject(tokenList)
				if err := client.Publish(subject, []byte(body)); err != nil {
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

	cancel()
	wg.Wait()
}

func createSubject(tokens []string) string {
	return fmt.Sprintf("%s.%s.%s", tokens[rand.Int()%len(tokens)], tokens[rand.Int()%len(tokens)], tokens[rand.Int()%len(tokens)])
}

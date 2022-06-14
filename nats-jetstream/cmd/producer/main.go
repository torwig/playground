package main

import (
	"context"
	"log"
	"math/rand"
	"os"
	"os/signal"
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
	serverAddr := os.Getenv("PRODUCER_NATS_ADDRESS")
	animals := os.Getenv("PRODUCER_ANIMAL_LIST")
	actions := os.Getenv("PRODUCER_ACTION_LIST")
	animalList := strings.Split(animals, ",")
	actionList := strings.Split(actions, ",")

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

	_, err = jsCtx.AddStream(&nats.StreamConfig{
		Name:       "animals",
		Subjects:   []string{"animals.*"},
		MaxMsgs:    1_000_000,
		Duplicates: time.Minute,
		Retention:  nats.LimitsPolicy,
		Discard:    nats.DiscardNew,
	})
	if err != nil {
		log.Printf("failed to add a stream: %s", err)
		return
	}

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
				animal := getAnimal(animalList)
				action := getAction(actionList)

				ack, err := jsCtx.Publish("animals."+animal, []byte(action))
				if err != nil {
					log.Printf("failed to publish to a stream: %s", err)
					return
				}

				log.Printf("published to '%s' with seq=%d: %s", animal, ack.Sequence, action)
			}
		}
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	cancel()
	wg.Wait()
}

func getAnimal(animals []string) string {
	return animals[rand.Int()%len(animals)]
}

func getAction(actions []string) string {
	return actions[rand.Int()%len(actions)]
}

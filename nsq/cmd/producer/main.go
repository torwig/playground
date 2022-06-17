package main

import (
	"context"
	"encoding/json"
	"github.com/torwig/playground/nsq/messages"
	"log"
	"math/rand"
	"os"
	"os/signal"
	"strings"
	"sync"
	"syscall"
	"time"

	"github.com/nsqio/go-nsq"
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

func main() {
	nsqAddr := os.Getenv("PRODUCER_NSQD_ADDRESS")
	animalList := os.Getenv("PRODUCER_ANIMAL_LIST")
	actionList := os.Getenv("PRODUCER_ACTION_LIST")
	animals := strings.Split(animalList, ",")
	actions := strings.Split(actionList, ",")

	cfg := nsq.NewConfig()

	producer, err := nsq.NewProducer(nsqAddr, cfg)
	if err != nil {
		log.Fatalf("failed to connect to NSQ: %s", err)
	}
	defer producer.Stop()

	ctx, cancel := context.WithCancel(context.Background())

	var wg sync.WaitGroup
	wg.Add(1)

	go func(ctx context.Context) {
		defer wg.Done()

		ticker := time.NewTicker(1 * time.Second)
		defer ticker.Stop()

		for {
			select {
			case <-ctx.Done():
				return
			case <-ticker.C:
				animal := animals[rand.Int()%len(animals)]
				action := actions[rand.Int()%len(actions)]

				body, _ := createAnimalActionMessage(animal, action)

				if err := producer.Publish(animal, body); err != nil {
					log.Printf("failed to publish a message: %s", err)
					continue
				}

				log.Printf("published: animal=%s action=%s", animal, action)
			}
		}
	}(ctx)

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	cancel()
	wg.Wait()
}

func createAnimalActionMessage(animal string, action string) ([]byte, error) {
	p := messages.AnimalAction{Animal: animal, Action: action}
	return json.Marshal(p)
}

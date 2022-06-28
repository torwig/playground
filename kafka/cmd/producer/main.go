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

	"github.com/confluentinc/confluent-kafka-go/kafka"
)

func main() {
	animalList := os.Getenv("PRODUCER_ANIMAL_LIST")
	animals := strings.Split(animalList, ",")
	actionList := os.Getenv("PRODUCER_ACTION_LIST")
	actions := strings.Split(actionList, ",")
	topic := os.Getenv("PRODUCER_TOPIC_NAME")

	cfg, err := createKafkaConfig()
	if err != nil {
		log.Fatalf("failed to get config: %s", err)
	}

	producer, err := kafka.NewProducer(&cfg)
	if err != nil {
		log.Fatalf("failed to create producer: %s", err)
	}
	defer producer.Close()

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
				animal := animals[rand.Intn(len(animals))]
				action := actions[rand.Intn(len(actions))]

				err := producer.Produce(&kafka.Message{
					TopicPartition: kafka.TopicPartition{Topic: &topic, Partition: kafka.PartitionAny},
					Key:            []byte(animal),
					Value:          []byte(action),
				}, nil)
				if err != nil {
					log.Printf("failed to produce message: %s", err)
				}
			}
		}
	}()

	wg.Add(1)
	go func() {
		defer wg.Done()

		for {
			select {
			case <-ctx.Done():
				return
			case e, ok := <-producer.Events():
				if !ok {
					return
				}

				switch ev := e.(type) {
				case *kafka.Message:
					if ev.TopicPartition.Error != nil {
						log.Printf("failed to deliver message: %s", err)
					} else {
						log.Printf("produced message to topic %s: key=%s value=%s", *ev.TopicPartition.Topic, string(ev.Key), string(ev.Value))
					}
				}
			}
		}
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	cancel()
	wg.Wait()

	producer.Flush(5000)
}

func createKafkaConfig() (kafka.ConfigMap, error) {
	m := make(map[string]kafka.ConfigValue)

	m["acks"] = "all"
	m["bootstrap.servers"] = os.Getenv("PRODUCER_KAFKA_ADDRESS")

	return m, nil
}

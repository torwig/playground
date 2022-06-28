package main

import (
	"log"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"

	"github.com/confluentinc/confluent-kafka-go/kafka"
)

func main() {
	topic := os.Getenv("CONSUMER_TOPIC_NAME")

	cfg, err := createKafkaConfig()
	if err != nil {
		log.Fatalf("failed to get config: %s", err)
	}

	consumer, err := kafka.NewConsumer(&cfg)
	if err != nil {
		log.Fatalf("failed to create consumer: %s", err)
	}
	defer consumer.Close()

	if err := consumer.Subscribe(topic, nil); err != nil {
		log.Printf("failed to subscribe consumer: %s", err)
		return
	}

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)

	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()

		for {
			select {
			case <-sigCh:
				return
			default:
				ev, err := consumer.ReadMessage(500 * time.Millisecond)
				if err != nil {
					continue
				}

				log.Printf("consumed from topic %s: key=%s value=%s",
					*ev.TopicPartition.Topic, string(ev.Key), string(ev.Value))
			}
		}
	}()

	wg.Wait()
}

func createKafkaConfig() (kafka.ConfigMap, error) {
	m := make(map[string]kafka.ConfigValue)

	m["acks"] = "all"
	m["group.id"] = os.Getenv("CONSUMER_GROUP_ID")
	m["bootstrap.servers"] = os.Getenv("CONSUMER_KAFKA_ADDRESS")

	return m, nil
}

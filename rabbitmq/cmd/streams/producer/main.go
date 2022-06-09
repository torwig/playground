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

	"github.com/pkg/errors"
	"github.com/rabbitmq/rabbitmq-stream-go-client/pkg/amqp"
	"github.com/rabbitmq/rabbitmq-stream-go-client/pkg/stream"
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

func main() {
	streamHost := os.Getenv("PRODUCER_STREAM_HOST")
	streamPort := os.Getenv("PRODUCER_STREAM_PORT")
	streamUser := os.Getenv("PRODUCER_STREAM_USER")
	streamPassword := os.Getenv("PRODUCER_STREAM_PASSWORD")
	streamName := os.Getenv("PRODUCER_STREAM_NAME")

	port, err := strconv.ParseInt(streamPort, 10, 64)
	if err != nil {
		log.Fatalf("failed to parse port value: %s", err)
	}

	env, err := stream.NewEnvironment(
		stream.NewEnvironmentOptions().
			SetHost(streamHost).
			SetPort(int(port)).
			SetUser(streamUser).
			SetPassword(streamPassword))
	if err != nil {
		log.Fatalf("failed to create stream environment: %s", err)
	}

	if err := env.DeclareStream(streamName, &stream.StreamOptions{
		MaxLengthBytes: stream.ByteCapacity{}.GB(1),
	}); err != nil && !errors.Is(err, stream.StreamAlreadyExists) {
		log.Fatalf("failed to declare a stream: %s", err)
	}

	producer, err := env.NewProducer(streamName, stream.NewProducerOptions().SetProducerName("producer1"))
	if err != nil {
		log.Fatalf("failed to create producer: %s", err)
	}
	defer producer.Close()

	lastID, err := producer.GetLastPublishingId()
	if err != nil {
		log.Fatalf("failed to get last published ID: %s", err)
	}

	startID := lastID + 1

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

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
				d := strconv.FormatInt(rand.Int63(), 10)
				m := amqp.NewMessage([]byte(d))
				m.SetPublishingId(startID)
				if err := producer.Send(m); err != nil {
					log.Printf("failed to send message: %s", err)
					return
				}

				startID++
				log.Printf("produced message: %s", d)
			}
		}
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	cancel()
	wg.Wait()
}

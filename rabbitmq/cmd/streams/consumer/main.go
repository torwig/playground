package main

import (
	"bytes"
	"log"
	"os"
	"os/signal"
	"strconv"
	"syscall"

	"github.com/pkg/errors"
	"github.com/rabbitmq/rabbitmq-stream-go-client/pkg/amqp"
	"github.com/rabbitmq/rabbitmq-stream-go-client/pkg/stream"
)

func main() {
	streamHost := os.Getenv("CONSUMER_STREAM_HOST")
	streamPort := os.Getenv("CONSUMER_STREAM_PORT")
	streamUser := os.Getenv("CONSUMER_STREAM_USER")
	streamPassword := os.Getenv("CONSUMER_STREAM_PASSWORD")
	streamName := os.Getenv("CONSUMER_STREAM_NAME")
	consumerName := os.Getenv("CONSUMER_NAME")

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

	msgHandler := func(ctx stream.ConsumerContext, msg *amqp.Message) {
		d := bytes.Join(msg.Data, []byte(","))
		log.Printf("consumer received: %s", string(d))
	}

	consumer, err := env.NewConsumer(streamName, msgHandler,
		stream.NewConsumerOptions().SetConsumerName(consumerName).SetOffset(stream.OffsetSpecification{}.First()))
	if err != nil {
		log.Fatalf("failed to create a consumer: %s", err)
	}

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	if err := consumer.Close(); err != nil {
		log.Printf("failed to close consumer: %s", err)
	}
}

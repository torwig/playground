package main

import (
	"log"
	"os"
	"os/signal"
	"syscall"

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
	sub, err := jsCtx.Subscribe(subject, handleMessage, nats.Durable("push_consumer"), nats.DeliverNew())
	if err != nil {
		log.Printf("failed to subscribe to '%s': %s", subject, err)
		return
	}

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	if err := sub.Unsubscribe(); err != nil {
		log.Printf("failed to unsubscribe from subject '%s': %s", subject, err)
		return
	}

	if err := sub.Drain(); err != nil {
		log.Printf("failed to drain: %s", err)
	}
}

func handleMessage(msg *nats.Msg) {
	log.Printf("received: %s", string(msg.Data))
}

package main

import (
	"log"
	"os"
	"os/signal"
	"syscall"

	"github.com/nats-io/nats.go"
)

func main() {
	serverAddr := os.Getenv("SUBSCRIBER_NATS_ADDRESS")
	subject := os.Getenv("SUBSCRIBER_SUBJECT")
	queueGroup := os.Getenv("SUBSCRIBER_QUEUE_GROUP")

	client, err := nats.Connect(serverAddr)
	if err != nil {
		log.Fatalf("failed to connect to nats server: %s", err)
	}
	defer client.Close()

	sub, err := client.QueueSubscribe(subject, queueGroup, processReceivedMessage)
	if err != nil {
		log.Printf("failed to subscribe for subject '%s': %s", subject, err)
		return
	}

	log.Printf("subscribed to '%s' within queue group '%s'", subject, queueGroup)

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

func processReceivedMessage(msg *nats.Msg) {
	log.Printf("got from '%s': %s", msg.Subject, string(msg.Data))
}

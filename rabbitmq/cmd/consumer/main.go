package main

import (
	"context"
	"log"
	"os"
	"os/signal"
	"strconv"
	"sync"
	"syscall"
	"time"

	amqp "github.com/rabbitmq/amqp091-go"
)

func main() {
	amqpAddr := os.Getenv("CONSUMER_AMQP_ADDRESS")
	queueName := os.Getenv("CONSUMER_QUEUE_NAME")

	conn, err := amqp.Dial(amqpAddr)
	if err != nil {
		log.Fatalf("failed to connect to AMQP server '%s': %s", amqpAddr, err)
		return
	}
	defer conn.Close()

	ch, err := conn.Channel()
	if err != nil {
		log.Printf("failed to open a channel: %s", err)
		return
	}

	queue, err := ch.QueueDeclare(queueName, true, false, false, false, nil)
	if err != nil {
		log.Printf("failed to declare a queue: %s", err)
		return
	}

	msgCh, err := ch.Consume(queue.Name, "", false, false, false, false, nil)
	if err != nil {
		log.Printf("failed to start consuming from queue: %s", err)
		return
	}

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()

		for {
			select {
			case <-ctx.Done():
				return
			case msg, ok := <-msgCh:
				if !ok {
					return
				}

				log.Printf("consumed: %s", string(msg.Body))
				n, err := strconv.ParseInt(string(msg.Body), 10, 64)
				if err != nil {
					continue
				}

				simulateSomeWork(n)
				if err := msg.Ack(false); err != nil {
					log.Printf("failed to ack the delivery: %s", err)
					return
				}
			}
		}
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	cancel()
	wg.Wait()
}

func simulateSomeWork(n int64) {
	t := time.Duration(int(n % 10))
	time.Sleep(t * time.Second)
}

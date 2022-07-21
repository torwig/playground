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

	"github.com/go-redis/redis/v8"
)

func main() {
	addr := os.Getenv("REDIS_ADDR")

	if addr == "" {
		log.Printf("set environmental variable REDIS_ADDR")
		return
	}

	rdb := redis.NewClient(&redis.Options{
		Addr: addr,
	})

	if err := rdb.Ping(context.Background()).Err(); err != nil {
		log.Printf("failed to ping redis: %s", err)
		return
	}
	defer rdb.Close()

	start := time.Now()

	sigint := make(chan os.Signal, 10)
	signal.Notify(sigint, syscall.SIGINT, syscall.SIGTERM)

	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()

		for {
			select {
			case <-sigint:
				return
			default:
				res, err := rdb.XAdd(context.Background(), &redis.XAddArgs{
					Stream: "new-test-stream",
					ID:     "*",
					Values: []string{"timestamp_1", strconv.FormatInt(time.Now().Unix(), 10),
						"timestamp_2", strconv.FormatInt(time.Now().Unix(), 10)},
				}).Result()
				if err != nil {
					log.Printf("failed to add entry to the stream: %s", err)
					return
				}

				log.Printf("added: %s", res)
			}
		}
	}()

	wg.Wait()

	log.Printf("done in %f seconds", time.Since(start).Seconds())
}

package main

import (
	"log"
	"os"
	"strconv"
	"time"

	"github.com/bradfitz/gomemcache/memcache"
)

func main() {
	mc := memcache.New(os.Getenv("MEMCACHED_ADDR"))
	if err := mc.Ping(); err != nil {
		log.Fatalf("failed to ping memcached: %s", err)
	}

	if err := mc.Set(&memcache.Item{
		Key:        "key1",
		Value:      []byte("value1"),
		Expiration: int32(time.Now().Add(1 * time.Minute).Unix()),
	}); err != nil {
		log.Printf("failed to write a record to cache: %s", err)
		return
	}

	item, err := mc.Get("key1")
	if err != nil {
		if err == memcache.ErrCacheMiss {
			log.Println("key not found in cache")
			return
		} else {
			log.Printf("failed to get record from cache: %s", err)
			return
		}
	}

	log.Printf("got cached value for key %s: %s", item.Key, string(item.Value))

	_ = mc.Set(&memcache.Item{Key: "key2", Value: []byte("value2"), Expiration: int32(time.Now().Add(5 * time.Minute).Unix())})
	_ = mc.Set(&memcache.Item{Key: "key3", Value: []byte("value3"), Expiration: int32(time.Now().Add(5 * time.Minute).Unix())})
	_ = mc.Set(&memcache.Item{Key: "key4", Value: []byte("value4"), Expiration: int32(time.Now().Add(5 * time.Minute).Unix())})

	values, err := mc.GetMulti([]string{"key2", "key4", "key6"})
	for k, v := range values {
		log.Printf("key %s found in cache, value: %s", k, string(v.Value))
	}

	_ = mc.Set(&memcache.Item{Key: "counter", Value: []byte(strconv.FormatInt(100, 10))})
	item, err = mc.Get("counter")
	if err != nil {
		log.Printf("failed to get counter from cache: %s", err)
		return
	}

	log.Printf("counter value: %s", string(item.Value))

	item.Value = []byte(strconv.FormatInt(200, 10))

	// note: the same item that was returned by Get
	err = mc.CompareAndSwap(item)
	if err != nil {
		log.Printf("failed to CAS counter: %s", err)
		return
	}

	v, err := mc.Increment("counter", 1)
	if err != nil {
		log.Printf("failed to increment counter: %s", err)
		return
	}

	log.Printf("new counter value: %d", v)

	_ = mc.Delete("counter")
	log.Println("counter was deleted from cache")

	item, err = mc.Get("counter")
	if err != nil {
		log.Printf("failed to get counter in cache: %s", err)
	}
}

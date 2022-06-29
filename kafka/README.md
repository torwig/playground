##Run Kafka
```sh
docker-compose up
```

##Run producer
```sh
export PRODUCER_KAFKA_ADDRESS=localhost:9092
export PRODUCER_ANIMAL_LIST=panda,spider,dove,turtle,eagle,cobra
export PRODUCER_ACTION_LIST=run,crawl,jump,fly,eat,bite,sleep
export PRODUCER_TOPIC_NAME=animal_actions
cd cmd/producer
go build .
./producer
```

##Run consumer
```sh
export CONSUMER_KAFKA_ADDRESS=localhost:9092
export CONSUMER_GROUP_ID=consumer1
export CONSUMER_TOPIC_NAME=animal_actions
cd cmd/consumer
go build .
./consumer
```

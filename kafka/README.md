##Run Kafka
```sh
docker-compose up
```

##Run producers
```sh
export PRODUCER_KAFKA_ADDRESS=localhost:9092
export PRODUCER_ANIMAL_LIST=panda,cow,turtle,wolf
export PRODUCER_ACTION_LIST=run,jump,eat,bite,sleep
export PRODUCER_TOPIC_NAME=animals
export PRODUCER_PARTITION=0
cd cmd/producer
go build .
./producer

export PRODUCER_KAFKA_ADDRESS=localhost:9092
export PRODUCER_ANIMAL_LIST=dove,eagle,owl,sparrow
export PRODUCER_ACTION_LIST=fly,eat,bite,sleep
export PRODUCER_TOPIC_NAME=animals
export PRODUCER_PARTITION=1
cd cmd/producer
go build .
./producer
```

##Run consumers (single one receives messages from both partitions)
```sh
export CONSUMER_KAFKA_ADDRESS=localhost:9092
export CONSUMER_GROUP_ID=consumer1
export CONSUMER_TOPIC_NAME=animals
cd cmd/consumer
go build .
./consumer

export CONSUMER_KAFKA_ADDRESS=localhost:9092
export CONSUMER_GROUP_ID=consumer1
export CONSUMER_TOPIC_NAME=animals
cd cmd/consumer
go build .
./consumer
```

##Create a topic with partitions
```sh
docker exec -it DOCKER_IMAGE_HASH bash
kafka-topics --bootstrap-server localhost:9092 --create --topic animals --partitions 2
```
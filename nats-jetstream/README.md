**Run NATS server**

`./nats-server -js`

**Run producer**

`cd cmd/producer`

`go build .`

`export PRODUCER_NATS_ADDRESS=localhost:4222`

`export PRODUCER_ANIMAL_LIST=eagle,worm,spider,raindeer`

`export PRODUCER_ACTION_LIST=run,jump,fly,crawl`

`./producer`

**Run push consumer**

`cd /cmd/consumer/push`

`go build .`

`export CONSUMER_NATS_ADDRESS=localhost:4222`

`export CONSUMER_ANIMAL_NAME=raindeer`

`./push`

**Run pull consumer**

`cd cmd/consumer/pull`

`go build .`

`export CONSUMER_NATS_ADDRESS=localhost:4222`

`export CONSUMER_ANIMAL_NAME=spider`

`./pull`

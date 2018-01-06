#!/bin/bash

# Run command in running container.
# Start the container with 'docker-compose up' first

if [ -n "$TERM" ];then
    EXEC_OPTS="-ti"
fi

docker exec $EXEC_OPTS bane_dev_1 bash -c "$@"


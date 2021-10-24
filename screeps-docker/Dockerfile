FROM ubuntu:latest

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y git make gcc g++ cmake nodejs npm && \
    git clone https://github.com/screeps/screeps.git && \
    cd screeps && \
    npm install && \
    npm install npx
EXPOSE 21025
VOLUME /screeps
CMD /bin/bash -c "while true; do sleep 100; done;"
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        g++ \
        make \
        libpqxx-dev \
        libboost-dev \
        libcpprest-dev && \
    rm -rf /var/lib/apt/lists/*

COPY . /usr/src/my-curriculum

WORKDIR /usr/src/my-curriculum

RUN make clean && make server

EXPOSE 80

USER root

CMD ["./server", "http://0.0.0.0", "80"]

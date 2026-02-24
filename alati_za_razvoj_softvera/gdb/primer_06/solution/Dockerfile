FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    && rm -rf /var/lib/apt/lists/*

COPY . /primer_06

WORKDIR /primer_06

RUN mkdir build

COPY test1.lines /primer_06/build

COPY test2.lines /primer_06/build

WORKDIR /primer_06/build

RUN cmake .. && make

CMD ["./lines"]
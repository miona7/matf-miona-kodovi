FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    && rm -rf /var/lib/apt/lists/*

COPY . /primer_04

WORKDIR /primer_04

RUN mkdir build

COPY testovi /primer_04/build/testovi

WORKDIR /primer_04/build

RUN cmake .. && make

ENTRYPOINT ["./program"]

CMD ["test"]
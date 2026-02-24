FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    && rm -rf /var/lib/apt/lists/*

COPY . /primer_07/

WORKDIR /primer_07

RUN mkdir build

WORKDIR /primer_07/build/

RUN cmake .. && make

ENTRYPOINT ["./text"]

CMD ["../test"]

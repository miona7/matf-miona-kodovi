FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# kreira dir ako ne postoji
COPY . /primer_08/

WORKDIR /primer_08

RUN mkdir build

# ocekuje da vec postoji build poddir inace nece da radi, zato ga pravimo ranije
COPY test.txt /primer_08/build/

WORKDIR /primer_08/build

RUN cmake ..

RUN make

CMD ["./k_means"]
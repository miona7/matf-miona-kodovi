FROM ubuntu:20.04

RUN apt-get update && \
    apt-get -y install curl && \
    apt-get install -y software-properties-common && \
    apt-get update && \
    apt-get -y install cmake && \
    apt-get -y install gcc && \
    apt-get -y install g++ && \
    apt-get -y upgrade

COPY . /usr/workdir

WORKDIR /usr/workdir

WORKDIR /usr/workdir/build

RUN cmake ..

RUN make

CMD /bin/bash -c "cp -r . ../result && ./program ../src/test.txt && ./test"


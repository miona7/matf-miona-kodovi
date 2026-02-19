FROM ubuntu:latest

RUN apt-get update -y && apt-get upgrade -y && apt-get install g++ -y

COPY main.cpp ./

RUN g++ main.cpp

CMD ["./a.out"]
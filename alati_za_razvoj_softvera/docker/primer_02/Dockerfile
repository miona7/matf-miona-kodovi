FROM gcc:latest

COPY . /src
# ceo trenutni direktorijum sa naseg racunara kopira u src unutar kontejnera

WORKDIR /src
# mkdir + cd src

RUN g++ main.cpp

ENTRYPOINT ["./a.out"]
# nepromenljiv deo

CMD ["5"] 
# promenjiv deo, podrazumevano 5 ali ako bilo sta unesemo pri pokretanju ceo CMD se pregazi
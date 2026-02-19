FROM python:latest

COPY requirements.txt .

RUN pip install -r requirements.txt

COPY server.py /primer04/src/
# kopiramo samo server jer zelimo samo njega da dokerizujemo

WORKDIR /primer04/src/

EXPOSE 5000
# kazemo da ce aplikacija slusati na portu 5000
# port racunara -> port kontejnera 12345:5000

CMD ["python", "server.py"]


FROM python:3.9.16

COPY requirements.txt .
# prvo kopiramo samo requirements.txt (u podrzumevanu folder sliku) da bi iskoristili cache slojeve Docker-a
# tako da se ne ponavlja instalacija paketa svaki put kada se promeni kod u main.py

RUN pip install -r requirements.txt
# ce se izvrsi ponovo samo ako se promeni requirements.txt

COPY main.py /primer03/src/
# COPY . /primer03/src/ -> bespotrebno ponovo kopira requirements.txt u radni direktorijum slike

WORKDIR /primer03/src/

CMD ["python", "main.py"]
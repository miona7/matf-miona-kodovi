FROM python:3.9.16

WORKDIR /primer03/src/

COPY requirements.txt .

RUN pip install -r requirements.txt

CMD ["python", "main.py"]
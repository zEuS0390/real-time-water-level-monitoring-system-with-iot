FROM ubuntu:latest

WORKDIR /webapp

COPY . /webapp

RUN apt-get update -y
RUN apt-get install python3-pip -y
RUN python3 -m pip install --upgrade pip
RUN python3 -m pip install --no-cache-dir -r requirements.txt

EXPOSE 5000

ENV PYTHONUNBUFFERED=1

CMD ["gunicorn", "--worker-class", "eventlet", "--workers", "1", "--bind", "0.0.0.0:5000", "wsgi:app"]

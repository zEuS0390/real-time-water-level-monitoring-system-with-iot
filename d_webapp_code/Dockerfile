FROM ubuntu:latest

WORKDIR /webapp

COPY . /webapp

RUN apt-get update -y
RUN apt-get install python3-pip python3-venv -y
RUN python3 -m venv /venv
RUN /venv/bin/pip install --upgrade pip
RUN /venv/bin/pip install --no-cache-dir -r requirements.txt

EXPOSE 5000

ENV PYTHONUNBUFFERED=1

CMD ["/venv/bin/gunicorn", "--worker-class", "eventlet", "--workers", "1", "--bind", "0.0.0.0:5000", "wsgi:app"]

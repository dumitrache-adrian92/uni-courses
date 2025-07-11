FROM python:3.12

COPY requirements.txt /tmp
RUN pip install -U setuptools
RUN pip install -r /tmp/requirements.txt

COPY /src /app
WORKDIR /app

ENV PYTHONUNBUFFERED=1

CMD ["python", "-u", "main.py"]

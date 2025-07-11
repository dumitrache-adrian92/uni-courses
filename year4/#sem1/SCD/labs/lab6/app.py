import time

import redis
from flask import Flask
import socket
import os

app = Flask(__name__)
host = os.getenv('REDIS_HOST', 'redis')
port = os.getenv('REDIS_PORT', '6379')
password = os.getenv('REDIS_PASSWORD', 'asdf')
window = int(os.getenv('WINDOW_SIZE', '10'))
cache = redis.Redis(host=host, port=port, password=password)

def get_hit_count():
    retries = 5
    key = 'hits_window'
    while True:
        try:
            ts = time.time()
            print(ts)
            start_ts = ts - window
            print(start_ts)

            expiration = window + 10
            print(expiration)

            pipe = cache.pipeline()
            results = pipe.zadd(key, {ts: ts}).\
                zremrangebyscore(key, 0, start_ts).\
                    zcard(key).\
                        expire(key, expiration).execute()

            return int(results[2])

        except redis.exceptions.ConnectionError as exc:
            if retries == 0:
                raise exc
            retries -= 1
            time.sleep(0.5)


@app.route('/')
def hello():
    count = get_hit_count()
    return f'Hello World from {socket.gethostname()}! I have been seen {count} times.\n'


if __name__ == '__main__':
    app.run('0.0.0.0', port=8000, debug=True)

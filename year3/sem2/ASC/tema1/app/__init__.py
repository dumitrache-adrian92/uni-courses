""" Webserver entry point """
import logging
import time
from logging.handlers import RotatingFileHandler
from flask import Flask
from app.data_ingestor import DataIngestor
from app.task_runner import ThreadPool

# logger configuration
logging.basicConfig(filename='webserver.log', level=logging.INFO,
                    format='[%(levelname)s] %(asctime)s: %(message)s',
                    datefmt='%m/%d/%Y %I:%M:%S %p')
logger = logging.getLogger("webserver")
handler = RotatingFileHandler('webserver.log', maxBytes=15000, backupCount=25)
logger.addHandler(handler)
logging.Formatter.converter = time.gmtime

logging.info("Starting webserver")

webserver = Flask(__name__)
webserver.tasks_runner = ThreadPool()
webserver.data_ingestor = DataIngestor("./nutrition_activity_obesity_usa_subset.csv")

webserver.tasks_runner.start()

webserver.job_counter = 1

from app import routes # necessary placement to avoid circular imports

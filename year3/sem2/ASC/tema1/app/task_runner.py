""" Module containing the ThreadPool and TaskRunner classes used for REST task execution """

import os
from queue import Queue
from threading import Thread, Event, RLock, Semaphore
import logging

class ThreadPool:
    """ Thread pool that holds a number of threads and
        a queue of tasks that need to be executed by the threads"""
    def __init__(self):
        # Determine the number of threads to use
        if "TP_NUM_OF_THREADS" in os.environ:
            self.num_threads = int(os.environ["TP_NUM_OF_THREADS"])
        else:
            self.num_threads = os.cpu_count()

        # job id counter
        self.__last_finished_job_id = 0
        self.__job_id = 1
        self.__job_id_lock = RLock()

        # Will store closures of tasks
        self.__task_queue = Queue() # thread-safe
        self.__task_count = Semaphore(0)

        # Event to notify threads to shutdown
        self.graceful_shutdown_event = Event()

        # The threads that will execute the tasks
        self.__task_runners = [TaskRunner(self, self.__task_queue, self.__task_count,
                                        self.graceful_shutdown_event)
                            for _ in range(self.num_threads)]

        if not os.path.exists("results"):
            os.makedirs("results")

    def add_task(self, task):
        """ Add a task to the task queue """
        self.__task_queue.put(task)
        self.__task_count.release()

    def graceful_shutdown(self):
        """ Graceful shutdown of the ThreadPool, allows all threads to finish their current task
            before shutting down """
        self.graceful_shutdown_event.set()
        for _ in range(self.num_threads):
            self.__task_count.release()

        for task_runner in self.__task_runners:
            task_runner.join()

        # stop webserver
        os._exit(0)

    def start(self):
        """ Start the ThreadPool """
        for task_runner in self.__task_runners:
            task_runner.start()

    def get_job_id(self):
        """ Return a unique job id """
        new_job_id = None

        with self.__job_id_lock:
            new_job_id = self.__job_id
            self.__job_id += 1

        return new_job_id

    def get_last_job_id(self):
        """ Return the last job id """
        result = 0
        with self.__job_id_lock:
            result = self.__job_id - 1

        return result

    def get_last_finished_job_id(self):
        """ Return the last finished job id """
        result = 0
        with self.__job_id_lock:
            result = self.__last_finished_job_id

        return result

    def update_last_finished_job_id(self):
        """ Update the last finished job id """
        with self.__job_id_lock:
            self.__last_finished_job_id += 1

    def get_remaining_job_count(self):
        """ Return the remaining job count """
        result = 0
        with self.__job_id_lock:
            result = self.get_last_job_id() - self.get_last_finished_job_id()

        return result


class TaskRunner(Thread):
    """ Thread that endlessly waits for tasks to be added to the queue
        and executes them """
    def __init__(self, thread_pool, queue, task_count, graceful_shutdown):
        super().__init__()
        self.thread_pool = thread_pool
        self.queue = queue
        self.task_count = task_count
        self.graceful_shutdown = graceful_shutdown

    def run(self):
        while True:
            # Wait for a task to be added to the queue
            self.task_count.acquire()

            # If we've been notified to that there's a task, but the queue is empty,
            # we're in the process of shutting down
            if self.queue.empty() and self.graceful_shutdown.is_set():
                break

            # Get a task from the queue (thread-safe operation)
            task = self.queue.get()
            # Execute the task
            job_id, result = task()

            # Store the result in a file
            with open(f"results/Temp_{self.name}", "a+", encoding="UTF-8", ) as file:
                file.write(str(result))

            os.rename(f"results/Temp_{self.name}", f"results/{job_id}")

            self.thread_pool.update_last_finished_job_id()

            logging.info("Job %s completed. Result: %s", job_id, result)

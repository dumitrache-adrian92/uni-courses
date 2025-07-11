from threading import enumerate, Event, Thread, Condition

class Master(Thread):
    def __init__(self, max_work, cond):
        Thread.__init__(self, name = "Master")
        self.max_work = max_work
        self.cond = cond
        self.work = 0
        self.worker = None

    def set_worker(self, worker):
        self.worker = worker

    def run(self):
        for i in range(self.max_work):
            # generate work
            self.work = i
            # notify worker
            with self.cond:
                self.cond.notify()
                self.cond.wait()
            # get result
            if self.get_work() + 1 != self.worker.get_result():
                print ("oops")
            print ("%d -> %d" % (self.work, self.worker.get_result()))

    def get_work(self):
        return self.work

class Worker(Thread):
    def __init__(self, terminate, cond):
        Thread.__init__(self, name = "Worker")
        self.terminate = terminate
        self.cond = cond
        self.result = 0

    def set_master(self, master):
        self.master = master

    def run(self):
        while True:
            # wait work
            with self.cond:
                self.cond.wait()

            if self.terminate.is_set(): break
            # generate result
            self.result = self.master.get_work() + 1
            # notify master
            with self.cond:
                self.cond.notify()

    def get_result(self):
        return self.result

if __name__ ==  "__main__":
    # create shared objects
    terminate = Event()
    cond = Condition()

    # start worker and master
    w = Worker(terminate, cond)
    m = Master(10, cond)
    w.set_master(m)
    m.set_worker(w)
    w.start()
    m.start()

    # wait for master
    m.join()

    # wait for worker
    terminate.set()
    with cond:
        cond.notify()
    w.join()

    # print running threads for verification
    print(enumerate())

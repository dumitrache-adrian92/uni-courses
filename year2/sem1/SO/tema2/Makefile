CC = gcc
CFLAGS = -fPIC -Wall
LDLIBS = -lpthread

build: libscheduler.so

libscheduler.so: so_scheduler.o
	$(CC) $(LDLIBS) -shared -o $@ $^

so_scheduler.o: so_scheduler.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-rm -f so_scheduler.o libscheduler.so
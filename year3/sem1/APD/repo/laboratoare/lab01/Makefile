build: example add_serial add_parallel example_4

example: example.c
	gcc example.c -o example -lpthread

add_serial: add_serial.c
	gcc add_serial.c -o add_serial

add_parallel: add_parallel.c
	gcc add_parallel.c -o add_parallel -lpthread

example_4: example_4.c
	gcc example_4.c -o example_4 -lpthread

.PHONY: clean
clean:
	rm -f example add_serial add_parallel example_4
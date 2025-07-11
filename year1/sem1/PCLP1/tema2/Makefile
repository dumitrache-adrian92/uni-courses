build: task1 task2 task3 task4
task1: task1.c biju.c biju.h
	gcc -Wall -g -o task1 task1.c biju.c -std=gnu11
task2: task2.c biju.c biju.h
	gcc -Wall -g -o task2 task2.c biju.c -std=gnu11
task3: task3.c biju.c biju.h
	gcc -Wall -g -o task3 task3.c biju.c -std=gnu11
task4: task4.c biju.c biju.h
	gcc -Wall -g -o task4 task4.c biju.c -std=gnu11
browser: browser.c biju.c biju.h
	gcc -Wall -g -o browser browser.c biju.c -lncurses -lmenu -std=gnu11
clean:
	rm task[1,2,3,4] browser
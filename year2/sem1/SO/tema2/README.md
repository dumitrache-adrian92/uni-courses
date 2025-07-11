A simulation of thread scheduling on a unicore CPU with limited functionality,
basically only has a few simple operations which are all worth 1 time unit (as
opposed to actually counting time). These operations allow you to start the
scheduler, create new threads with different priorities, waste time on the
CPU, stop the scheduler etc. (they're offered as a library)

Threads created by the library were supposed to be scheduled according to the
round robin algorithm, which I didn't get quite right. They're ordered, just
not well :(
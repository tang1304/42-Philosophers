# Philosophers
This project is about solving the dining philosophers problem (https://en.wikipedia.org/wiki/Dining_philosophers_problem) and familiarizing with threads and mutexes, in C.

## Mandatory part:
One or more philosophers sit around a table. There are as many forks as philosophers, placed between them, and a bowl of spaghetti. Each philosopher has a time to eat, time to sleep and time to die. Each philosopher must be a thread.

### Rules:
- Time to die (ms):  If a philosopher didn’t start eating x milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

- Time to eat (ms): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks, the one from its left and the one from its right. The forks state should be protected with mutex.

- Time to sleep (ms): The time a philosopher will spend sleeping.

- The philosophers alternatively eat, think, or sleep.
	- While they are eating, they are not thinking nor sleeping;
	- while thinking, they are not eating nor sleeping;
	- while sleeping, they are not eating nor thinking.

- To eat, a philosopher needs two forks, one in each hand.

- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.

- Philosophers don’t speak with each other (Threads of philosophers can't communicate between each others).

- Philosophers don’t know if another philosopher is about to die.

- Each philosopher has a number ranging from 1 to number_of_philosophers. Philosopher x is sat between x-1 and x+1.

### Expectations:
The program should take the following arguments:
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep,
(number_of_times_each_philosopher_must_eat (optional))
```
./philo nbr ttdie tteat ttsleep (meal_nbr)
```
During the simulation, we will print the logs of the philosophers' state change like this:
- *timestamp_in_ms X has taken a fork*
- *timestamp_in_ms X is eating*
- *timestamp_in_ms X is sleeping*
- *timestamp_in_ms X is thinking*
- *timestamp_in_ms X died*
**timestamp_in_ms** being the current timestamp from the begining of the simulation, and **X** being the number of the philosopher.

A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher. No more messages will be printed after a dying message.

## Bonus part (not done):
The rules stay the same for the binus program, except these specific rules:
- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a process. But the main process should not be a
philosopher.

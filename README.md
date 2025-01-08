**Dining Philosophers Problem**
This repository contains a C implementation of the Dining Philosophers Problem. This problem is a classic concurrency challenge in computer science that demonstrates how to manage shared resources (in this case, forks) between multiple processes (philosophers) without causing deadlock or resource contention.


![Alt text](file:///home/lade-kon/Pictures/philo_problem)


Program Overview
The project consists of:

A mandatory program (philo) that meets the basic requirements.
An optional bonus program if additional features are implemented.
Both versions follow the rules below:

Rules & Specifications
No Global Variables: All data, including philosopher states and forks, is encapsulated within structures.
Arguments:
number_of_philosophers: Number of philosophers and forks (1 per philosopher).
time_to_die: Maximum time in milliseconds a philosopher can go without eating before dying.
time_to_eat: Time in milliseconds each philosopher spends eating.
time_to_sleep: Time in milliseconds each philosopher spends sleeping.
[number_of_times_each_philosopher_must_eat] (optional): If provided, the simulation stops after each philosopher has eaten this number of times. If omitted, the simulation only stops upon a philosopher’s death.
Behavior
Philosopher Lifecycle: Each philosopher is represented by a thread that goes through the states of thinking, eating, and sleeping in cycles.
Forks: Philosophers pick up two forks (mutexes) to eat, with one fork between each pair of philosophers.
Logging: The program logs state changes for each philosopher in the format:
csharp

timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
timestamp_in_ms: Time in milliseconds since the start of the simulation.
X: Philosopher number (1 through number_of_philosophers).

No Message Mixing: Each message is displayed separately to avoid mixing.
Timeliness: A philosopher's death message is displayed within 10 ms of their actual death.
Threading & Synchronization
Each philosopher is a thread, and each fork is protected by a mutex.
The solution ensures no data races and synchronizes state updates to prevent simultaneous message output.

Compilation and Execution
Makefile Targets:
all: Compiles the program.
clean: Removes object files.
fclean: Removes all compiled files.
re: Recompiles the program.
Example Usage
bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
Example:

bash
./philo 5 800 200 200
This command runs a simulation with 5 philosophers, where each has 800 ms to eat before dying, spends 200 ms eating, and 200 ms sleeping. The program stops when a philosopher dies, as no specific meal count is given.

External Functions
The following external functions are allowed:

memset, printf, malloc, free, write, usleep, gettimeofday
pthread_create, pthread_detach, pthread_join, pthread_mutex_init
pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
Important Notes
Libft is not allowed.
Concurrency & Deadlock Prevention: Philosophers should avoid deadlocks and prevent starvation by managing fork access properly.

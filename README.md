*This project was created as part of the 42 curriculum by chgomez.*

# Philosophers

## Overview

`philosophers` is a concurrency project written in C.

The project is based on the classic Dining Philosophers problem, where several philosophers share forks around a table. Each philosopher alternates between thinking, eating and sleeping, while the program must prevent race conditions, avoid deadlocks and correctly manage shared resources.

The goal of the project is to understand how threads, mutexes and synchronization work in a Unix-like environment.

## Description

In this simulation, each philosopher is represented by an independent thread.

Each fork is represented by a mutex. A philosopher must lock two forks before eating and release them after finishing. The program must coordinate all philosophers so that shared resources are accessed safely.

The simulation stops when:

- A philosopher does not eat within the allowed `time_to_die`.
- All philosophers have eaten the required number of meals, if the optional argument is provided.

The project focuses on:

- Thread creation and synchronization.
- Mutex-based resource protection.
- Shared state management.
- Time measurement in milliseconds.
- Race condition prevention.
- Deadlock prevention.
- Clean memory and thread management.

## Program Arguments

The program receives 4 mandatory arguments and 1 optional argument:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
| --- | --- |
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Maximum time in milliseconds a philosopher can go without starting to eat |
| `time_to_eat` | Time in milliseconds spent eating |
| `time_to_sleep` | Time in milliseconds spent sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional argument. If provided, the simulation stops when every philosopher has eaten at least this number of times |

## Features

- Creates one thread per philosopher.
- Uses mutexes to protect shared forks.
- Uses a monitor routine to detect when the simulation must stop.
- Prints philosopher actions with timestamps.
- Handles the single philosopher case.
- Supports an optional meal limit.
- Protects shared simulation state with synchronization mechanisms.
- Cleans allocated memory and destroys mutexes before exiting.
- Compiles with a custom `Makefile`.

## Technologies

- C language
- POSIX threads
- Mutexes
- Concurrent programming
- Synchronization
- Time management
- Memory management
- Makefile
- Compilation with `cc`
- Flags: `-Wall -Wextra -Werror`

## Project Structure

```text
.
├── README.md
├── es.subject.pdf
└── philo/
    ├── Makefile
    ├── README.md
    ├── clean.c
    ├── init.c
    ├── init_philos.c
    ├── main.c
    ├── monitor.c
    ├── parse.c
    ├── philo.h
    ├── print.c
    ├── routine.c
    ├── simulation.c
    └── time.c
```

## How to Compile

Go to the project source directory:

```bash
cd philo
```

Compile the project:

```bash
make
```

This generates the executable:

```text
philo
```

Remove object files:

```bash
make clean
```

Remove object files and the executable:

```bash
make fclean
```

Rebuild the project:

```bash
make re
```

## How to Run

General syntax:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

This runs the simulation with:

- 5 philosophers
- 800 ms before a philosopher runs out of time without eating
- 200 ms eating time
- 200 ms sleeping time

Example with a meal limit:

```bash
./philo 5 800 200 200 7
```

This runs the simulation until every philosopher has eaten at least 7 times, unless the simulation stops earlier.

## Output Format

Each action is printed using the following format:

```text
timestamp_in_ms philosopher_id action
```

Possible actions:

```text
has taken a fork
is eating
is sleeping
is thinking
died
```

Example output:

```text
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

The timestamp represents the elapsed time in milliseconds since the beginning of the simulation.

## Testing Examples

Basic case:

```bash
./philo 5 800 200 200
```

Simulation with a meal limit:

```bash
./philo 5 800 200 200 7
```

Single philosopher case:

```bash
./philo 1 800 200 200
```

Tighter timing case:

```bash
./philo 4 410 200 200
```

Check for memory leaks:

```bash
valgrind --leak-check=full ./philo 5 800 200 200 3
```

Check for thread-related issues:

```bash
valgrind --tool=helgrind ./philo 5 800 200 200 3
```

## Implementation Highlights

- `main.c` validates the execution flow and launches the simulation.
- `parse.c` checks and converts program arguments.
- `init.c` initializes the main simulation data.
- `init_philos.c` initializes philosopher structures.
- `simulation.c` creates and joins philosopher threads.
- `routine.c` defines the behavior of each philosopher.
- `monitor.c` checks whether a philosopher has exceeded the allowed time without eating or whether all philosophers have completed the required meals.
- `print.c` prints synchronized output to avoid mixed messages between threads.
- `time.c` manages timestamps and sleep timing.
- `clean.c` releases allocated resources and destroys mutexes.

## Synchronization Strategy

The project uses mutexes to protect shared resources and shared state.

Each fork is protected by its own mutex. Shared simulation values, such as the stop condition or meal counters, must be accessed in a synchronized way to avoid race conditions.

The program also needs to avoid deadlocks. To do this, philosophers must not all block forever while waiting for forks. The implementation coordinates fork access and monitoring so the simulation can continue safely or stop correctly.

## What I Learned

- How to create and manage threads with `pthread_create()` and `pthread_join()`.
- How to protect shared resources with mutexes.
- How race conditions appear in concurrent programs.
- How deadlocks can happen when multiple threads compete for shared resources.
- How to design a monitor routine for a concurrent simulation.
- How to measure time accurately in milliseconds.
- How to synchronize terminal output between multiple threads.
- How to clean resources correctly in a multithreaded C program.

## Resources

- `man pthread_create`
- `man pthread_join`
- `man pthread_mutex_init`
- `man pthread_mutex_lock`
- `man pthread_mutex_unlock`
- `man gettimeofday`
- 42 Philosophers subject
- POSIX threads documentation

## Notes

This project follows the constraints and style expected in the 42 curriculum.  
The implementation is intentionally written in C and focuses on concurrency, synchronization, mutexes, timing and shared resource management.

## Author

Christian Gómez  
Junior Software Developer in training at 42 Barcelona  
GitHub: [github.com/chgomez04](https://github.com/chgomez04)

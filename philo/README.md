*This project was created as part of the 42 curriculum by chgomez.*

# Philosophers

## Description

`philo` is a C implementation of the classic Dining Philosophers problem.

The goal of this project is to understand and practice concurrency concepts such as threads, mutexes, synchronization, shared resources, race conditions, and deadlock prevention.

In the simulation, each philosopher is represented by an independent thread. Philosophers sit around a table, and there is one fork between each pair of philosophers. To eat, a philosopher must take two forks: the one on the left and the one on the right.

Each fork is protected by a mutex, ensuring that two philosophers cannot use the same fork at the same time.

The simulation ends when:

- A philosopher dies because they did not eat within `time_to_die`.
- All philosophers have eaten at least the required number of meals, if the optional argument is provided.

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate the executable:

```bash
./philo
```

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To recompile the project from scratch:

```bash
make re
```

### Usage

The program receives 4 mandatory arguments and 1 optional argument:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers and forks. |
| `time_to_die` | Maximum time in milliseconds a philosopher can go without starting to eat. |
| `time_to_eat` | Time in milliseconds a philosopher spends eating. |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping. |
| `number_of_times_each_philosopher_must_eat` | Optional argument. If provided, the simulation stops when every philosopher has eaten at least this number of times. |

### Examples

```bash
./philo 5 800 200 200
```

Runs the simulation with 5 philosophers.

```bash
./philo 5 800 200 200 7
```

Runs the simulation until every philosopher has eaten at least 7 times, unless a philosopher dies first.

```bash
./philo 1 800 200 200
```

Runs the simulation with only one philosopher. Since there is only one fork, the philosopher cannot eat and will eventually die.

## Output Format

Each state change is printed using the following format:

```text
timestamp_in_ms philosopher_id action
```

Possible actions are:

```text
has taken a fork
is eating
is sleeping
is thinking
died
```

Example:

```text
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

The timestamp represents the elapsed time in milliseconds since the start of the simulation.

## Main Rules

The project follows the requirements of the 42 Philosophers subject:

- One thread is created for each philosopher.
- One mutex is used for each fork.
- Shared data is protected with mutexes.
- Output messages are protected to avoid mixed or corrupted prints.
- The simulation stops when a philosopher dies or when all philosophers have eaten enough times.
- Dynamic memory is freed before the program exits.
- No global variables are used.

## Technical Decisions

### Fork Protection

Each fork is represented by a mutex. A philosopher must lock two fork mutexes before eating and unlock them after finishing the meal.

### Shared State Protection

Shared information such as the simulation status, meal counters, and last meal times is protected with mutexes to avoid data races.

### Death Monitoring

The program continuously checks whether any philosopher has exceeded `time_to_die` without eating. If this happens, the simulation ends and the death message is printed.

### Optional Meal Limit

When the optional argument `number_of_times_each_philosopher_must_eat` is provided, the simulation also checks whether all philosophers have eaten at least that number of times.

## Recommended Tests

### Basic execution

```bash
./philo 5 800 200 200
```

Expected behavior: no philosopher should die under normal conditions.

### Meal limit

```bash
./philo 5 800 200 200 7
```

Expected behavior: the simulation should stop once every philosopher has eaten at least 7 times.

### One philosopher

```bash
./philo 1 800 200 200
```

Expected behavior: the philosopher takes one fork and eventually dies.

### Death case

```bash
./philo 4 310 200 200
```

Expected behavior: at least one philosopher may die because the timing is too tight.

### Memory check

```bash
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200 3
```

This command can be used to check for memory leaks.

### Data race check

```bash
valgrind --tool=helgrind ./philo 5 800 200 200 2
```

This command can be used to detect possible data races or incorrect mutex usage.

### Norminette

```bash
norminette
```

This command checks whether the project follows the 42 coding standard.

## Resources

The following resources were useful for understanding the concepts used in this project:

- 42 Philosophers official subject.
- POSIX Threads documentation.
- `pthread_create` manual.
- `pthread_join` manual.
- `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, and `pthread_mutex_destroy` manuals.
- `gettimeofday` manual.
- `usleep` manual.
- Valgrind documentation.
- Helgrind documentation.
- Classical explanations of the Dining Philosophers problem.

## Use of AI

Artificial Intelligence was used as a learning and support tool during the development of this project.

AI was used for the following purposes:

- Understanding theoretical concepts related to threads, mutexes, synchronization, and shared resources.
- Reviewing possible edge cases for testing.
- Preparing explanations about the Dining Philosophers problem.
- Identifying potential weak points related to synchronization and race conditions.
- Improving the structure and clarity of this README file.

AI was not used to replace the implementation work. The code was written, reviewed, tested, and adapted manually according to the requirements of the 42 subject.

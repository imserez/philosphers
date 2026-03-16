# Philosophers: Thread Synchronization & Resource Sharing

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![System](https://img.shields.io/badge/System-Unix%2FLinux-lightgrey.svg)
![Topic](https://img.shields.io/badge/Topic-Concurrency_%26_Threads-orange.svg)

## Overview

**Philosophers** is a simulation of the classic "Dining Philosophers" problem, a foundational concept in computer science used to illustrate synchronization issues in concurrent algorithm design.

This project is a practical implementation of **Multithreading** and **Mutual Exclusion (Mutex)**. The challenge is to manage a group of threads (philosophers) competing for a limited set of shared resources (forks), ensuring that:

1.  **No Deadlocks:** The system never reaches a state where processes wait indefinitely for each other.
2.  **No Starvation:** Every thread gets a chance to access the critical section (eat).
3.  **Data Integrity:** Simultaneous access to shared memory does not result in race conditions.

## Technical Concepts

This project relies on the `pthread` library to manipulate the kernel's thread scheduling and synchronization primitives:

* **Multithreading (`pthread_create`):** Creating lightweight execution units that share the same memory space (heap) but maintain their own stack frames.
* **Mutual Exclusion (`pthread_mutex_t`):** Implementing locking mechanisms to protect **Critical Sections**. This ensures that actions like picking up a fork (modifying a shared variable) are atomic operations.
* **Race Conditions:** Rigorously identified and prevented. Since threads run asynchronously, reading/writing variable states (like `last_meal_time` or `is_dead`) without locks leads to undefined behavior.
* **Context Switching & Timing:** Managing high-precision timing (`gettimeofday`) to monitor process states in the microsecond range, dealing with the non-deterministic nature of the OS scheduler.

## Thread Architecture

The simulation operates on a cyclical state machine for each thread:

1.  **Thinking:** The thread is idle, waiting for resources.
2.  **Hungry (Acquisition):** The thread attempts to lock two specific mutexes (Left Fork & Right Fork).
    * *Constraint:* To eat, a philosopher *must* hold both locks simultaneously.
3.  **Eating (Critical Section):**
    * Modifies shared state (`last_meal`).
    * Holds the resource for `time_to_eat`.
4.  **Sleeping (Release):** The thread unlocks both mutexes, making resources available for neighbors, and sleeps for `time_to_sleep`.
5.  **Monitoring (The Reaper):** A separate observer loop checks if any thread has exceeded `time_to_die` without entering the eating state.

## Usage

### Prototype
The program requires specific timing arguments (in milliseconds):

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_to_eat]
```

* `number_of_philosophers`: The number of philosophers and also the number of forks.
* `time_to_die`: Time (ms) a philosopher can survive without eating.
* `time_to_eat`: Time (ms) it takes to eat (hold two forks).
* `time_to_sleep`: Time (ms) spent sleeping.
* `[number_of_times_to_eat]`: (Optional) The simulation stops if all philosophers eat at least this many times.

### 1. Compilation
The project includes a Makefile with `-pthread` linking.

```bash
make
```

### 2. Execution Examples

**Example 1: Infinite Simulation**
5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep.
*Result: Should run indefinitely without anyone dying.*

```bash
./philo 5 800 200 200
```

**Example 2: Forced Death**
4 philosophers, 310ms to die, 200ms to eat, 100ms to sleep.
*Result: A philosopher should die because `time_to_die` < `eat` + `sleep` + context_switch.*

```bash
./philo 4 310 200 100
```

## Error Handling & Edge Cases

The implementation accounts for system instability and logical pitfalls:
* **Single Philosopher:** Handled as a special case. With only one fork available, the thread cannot eat and will die after `time_to_die` (simulating deadlock on resource dependency).
* **Input Validation:** Rigorous parsing of arguments to reject non-numeric or negative values.
* **Resource Cleanup:** Ensures all mutexes are destroyed and heap memory freed upon termination to prevent memory leaks.

## Author

**Sergi Juarez**

- **GitHub:** [imserez](https://github.com/imserez)
- **LinkedIn:** [sergijuarez](https://www.linkedin.com/in/sergijuarez)

---
*This project is part of the 42 Barcelona curriculum.*

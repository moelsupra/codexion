# Copilot / AI Agent Instructions for codexion

This file contains concise, actionable guidance to help an AI coding agent be productive in this repository.

**Project Overview**:
- **Binary:** `codexion` built from `srcs/*.c` via the top-level `Makefile`.
- **Purpose:** A multithreaded simulation where `coders` compete for `dongles` (mutex-protected resources). Concurrency resembles the classic dining-philosophers problem with ordered locking to avoid deadlocks.

**Build & Run**:
- **Build:** `make` (uses `cc` with `-pthread` flags; see `Makefile`).
- **Run:** `./codexion <args>` (CLI expects 8 arguments; see "CLI / Runtime" below).

**Important files**:
- `Makefile` : central build; update `SRCS` when adding/removing source files.
- `includes/codexion.h` : public types and function prototypes (primary contract).
- `srcs/init/sim.c` : (here `srcs/sim.c`) allocation and initialization of `t_sim`, `t_dongle`, `t_coder`.
- `srcs/threads.c` : thread lifecycle (`start_coders`, `join_coders`, `coder_routine`).
- `srcs/dongles.c` : locking strategy (`lock_two`) and `take_dongles`/`put_dongles`.
- `srcs/loggin.c` : logging helper and timestamping; uses `sim->start_time` and `sim->log_lock`.

**CLI / Runtime Arguments (order matters)**
The program expects exactly 8 arguments (so `argc == 9`):
1. `number_of_coders` (int, 1..INT_MAX)
2. `time_to_burnout` (ms, positive integer)
3. `time_to_compile` (ms)
4. `time_to_debug` (ms)
5. `time_to_refactor` (ms)
6. `number_of_compiles_required` (int)
7. `dongle_cooldown` (ms)
8. `scheduler` (`fifo` or `edf`)

Example run:
```
make
./codexion 5 800 200 100 150 3 50 fifo
```

**Concurrency & Safety Patterns**
- Each `t_dongle` has its own `pthread_mutex_t lock` (see `includes/codexion.h`).
- `lock_two(a,b)` acquires both mutexes in deterministic order by `id` to avoid deadlocks. Prefer reusing `lock_two` when acquiring two dongles.
- All logging is serialized with `sim->log_lock` using `log_state()`; use it for any console output from threads.
- `init_sim()` allocates `sim->dongles` and `sim->coders` and initializes per-dongle mutexes; `free_sim()` destroys those mutexes and frees memory. Do not change ownership semantics without updating both functions.

**Coding conventions & style notes (discoverable)**
- Files live under `srcs/` and include header via `#include "codexion.h"` with the `-I includes` compiler flag.
- Types use `t_` prefix (e.g., `t_sim`, `t_coder`). Functions are lower_snake_case (e.g., `start_coders`).
- The author follows 42-school file header style; keep similar formatting for added files.

**When editing or adding code**
- Add new `.c` files to the `srcs/` directory and then add the filename to `SRCS` in the `Makefile`.
- Preserve public function signatures declared in `includes/codexion.h` unless you also update all callers.
- If adding thread behavior, follow existing patterns: initialize mutexes in `init_sim`, use `log_state()` for output, and clean up in `free_sim`.

**Common pitfalls observed / checks to make**
- Ensure `sim->start_time` is set before threads call `get_elapsed_ms()` (logging reads `sim->start_time`). If you add early logging, initialize `gettimeofday(&sim->start_time, NULL)` during `init_sim` or before `start_coders()`.
- Always check `pthread_create` return values (current code does this in `start_coders`) and clear resources on failure.
- Respect the circular assignment of `left` and `right` dongles in `init_sim` to maintain the expected topology.

**No tests / CI present**
- There are no test harnesses or CI config files in the repository. Use manual runs and standard tools (valgrind, gdb) when debugging concurrency.

If anything important is missing or if you want repository-specific linting/formatting rules added, tell me what to add and I will update this file.

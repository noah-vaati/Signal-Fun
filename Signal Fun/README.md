Compiling & Running
====================
The programs can be compiled with the included Makefile by running the command `make`.

The program `part1` can be run with usage `part1 (program) {arguments}`.
`kill -signal (pID)` will send that signal to the prgram. Supports usr1, usr2, alrm

The program `part2` can be run with usage `part2 1` or `part2 2`.
The program sends a signal from parent process to child, then later the parent interupts that signal with a second signal.
`part2 1` will run the program so that the second signal sent to the child process is `SIGUSR1`.
`part2 2` will run the program so that the second signal sent to the child process is `SIGUSR2`.

`make clean` will remove the compiled executables.

Part 2: Report
====================

When a process recieves a signal for `SIGUSR1` while already handling `SIGUSR1`, the process waits to finish handling the first `SIGUSR1` signal, then starts the next `SIGUSR1` signal.
This corresponds to the signal man page, which states that Linux uses some BSD semantics where further instances of the same signal are blocked while the signal handler is running.

When a process recieves a signal for `SIGUSR2` while busy handling `SIGUSR1`, the process halts the `SIGUSR1` signal, and immediately begins the `SIGUSR2` signal.
`SIGUSR1` does not start again until `SIGUSR2 is finished.`
This corresponds to the signal man page, which states that Linux uses some System V semantics where rapid signal deliveries could result in recursive invocations of the handler.

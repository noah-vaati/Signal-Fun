# About

`part 1` prints out whatever the user enters. However, the I/O is hijacked by a process that is capable of switching the word "cat" to "dog" and vice versa using signals.

`part 2` sends a signal from parent process to child, then later the parent interupts that signal with a second signal.

# Compiling & Running

The programs can be compiled with the included Makefile by running the command `make`.

The program `part1` can be run with usage `part1 (program) {arguments}`.
`kill -signal (pID)` will send that signal to the prgram. Supports usr1, usr2, alrm
SIGUSR1 switches "dog" to "cat", SIGUSR2 switches "cat" to "dog", and SIGALRM disables the switching.

The program `part2` can be run with usage `part2 1` or `part2 2`.
The program sends a signal from parent process to child, then later the parent interupts that signal with a second signal.
`part2 1` will run the program so that the second signal sent to the child process is `SIGUSR1`.
`part2 2` will run the program so that the second signal sent to the child process is `SIGUSR2`.

`make clean` will remove the compiled executables.

all: part1 part2

part1: part1.c
	clang -lrt -lpthread -Wall -Wpedantic -Wextra -Werror -o part1 part1.c

part2: part2.c
	clang -lrt -Wall -Wpedantic -Wextra -Werror -o part2 part2.c

clean:
	rm -f part1 part2
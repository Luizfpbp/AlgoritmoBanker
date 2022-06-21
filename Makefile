#Flags
CC = gcc

make: banker.c
	$(CC) $< -o banker

.PHONY: clean remove

clean:
	rm banker

remove:
	rm result.txt
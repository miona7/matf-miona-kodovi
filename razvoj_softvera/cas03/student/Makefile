CC = g++
CFLAGS = -Wall -Wextra

a.out: main.o student.o master.o
	$(CC) $(CFLAGS) -o $@ $^

master.o: masterStudent.cpp masterStudent.hpp
	$(CC) $(CFLAGS) -c $< -o $@

student.o: student.cpp student.hpp
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean: rm -f *.o 
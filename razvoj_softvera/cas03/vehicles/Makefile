CC = g++
CFLAGS = -Wall -Wextra

a.out: main.o vehicles.o vehiclesWithWindows.o car.o truck.o bike.o vehiclePark.o
	$(CC) $(CFLAGS) $^ -o $@

vehiclePark.o: vehiclePark.cpp vehiclePark.hpp
	$(CC) $(CFLAGS) -c $< -o $@

bike.o: bike.cpp bike.hpp 
	$(CC) $(CFLAGS) -c $< -o $@

truck.o: truck.cpp truck.hpp 
	$(CC) $(CFLAGS) -c $< -o $@

car.o: car.cpp car.hpp 
	$(CC) $(CFLAGS) -c $< -o $@

vehiclesWithWindows.o: vehiclesWithWindows.cpp vehiclesWithWindows.hpp 
	$(CC) $(CFLAGS) -c $< -o $@

vehicles.o: vehicles.cpp vehicles.hpp
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $< -o $@
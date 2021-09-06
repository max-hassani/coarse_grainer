# make file for suvendu's code, calculating 
#-------------------------------------
CC = g++
CFLAGS = -Wall -g 
#-------------------------------------
strain_map.X: trajectory.o snapshot.o box.o input.o p_vec_ten.o atom.o main.o 
	${CC} ${CFLAGS} trajectory.o snapshot.o input.o box.o p_vec_ten.o atom.o main.o -o strain_map.X

p_vec_ten.o: p_vec_ten.cc p_vec_ten.hh
	${CC} ${CFLAGS} -c p_vec_ten.cc

input.o: input.cpp input.hh
	${CC} ${CFLAGS} -c input.cpp
	
box.o: box.cpp box.hh
	${CC} ${CFLAGS} -c box.cpp
	
atom.o: atom.cpp atom.hh
	${CC} ${CFLAGS} -c atom.cpp
	
trajectory.o: trajectory.cpp trajectory.hh
	${CC} ${CFLAGS} -c trajectory.cpp
	
snapshot.o: snapshot.cpp snapshot.hh box.cpp box.hh atom.cpp atom.hh
	${CC} ${CFLAGS} -c snapshot.cpp

main.o: main.cpp p_vec_ten.hh input.hh box.hh snapshot.hh atom.hh trajectory.hh
	${CC} ${CFLAGS} -c main.cpp

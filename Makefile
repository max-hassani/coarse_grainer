# make file for suvendu's code, calculating 
#-------------------------------------
CC = g++
CFLAGS = -Wall -g 
#-------------------------------------
strain_map.X: snapshot.o box.o input.o p_vec_ten.o atom.o main.o 
	${CC} ${CFLAGS} snapshot.o input.o box.o p_vec_ten.o atom.o main.o -o strain_map.X

p_vec_ten.o: p_vec_ten.cc p_vec_ten.hh
	${CC} ${CFLAGS} -c p_vec_ten.cc

input.o: input.cpp input.hh
	${CC} ${CFLAGS} -c input.cpp
	
box.o: box.cpp box.hh
	${CC} ${CFLAGS} -c box.cpp
	
atom.o: atom.cpp atom.hh
	${CC} ${CFLAGS} -c atom.cpp
	
snapshot.o: snapshot.cpp snapshot.hh box.cpp box.hh atom.cpp atom.hh
	${CC} ${CFLAGS} -c snapshot.cpp

main.o: main.cpp p_vec_ten.hh p_vec_ten.cc input.hh input.cpp box.hh box.cpp snapshot.cpp snapshot.hh atom.cpp atom.hh
	${CC} ${CFLAGS} -c main.cpp

	
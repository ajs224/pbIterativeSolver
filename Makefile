# MFA Makefile
# A. J. Smith (ajs224@cam.ac.uk)
#
FLAGS = -g -I./include #-fast
COMPILER = g++
#COMPILER = /opt/intel/Compiler/11.0/083/bin/intel64/icc
TARGET= pbIterativeSolver
SRC=./source

${TARGET}: ${TARGET}.o mfa_params.o n_in.o kernel.o parse_args.o Cell.o #moments.o Particle.o #theta.o
	${COMPILER} -o ${TARGET} ${FLAGS} ${TARGET}.o mfa_params.o n_in.o kernel.o parse_args.o Cell.o

${TARGET}.o: ${SRC}/${TARGET}.c++
	${COMPILER} -c ${FLAGS} ${SRC}/${TARGET}.c++

mfa_params.o: ${SRC}/mfa_params.c++
	${COMPILER} -c ${FLAGS} ${SRC}/mfa_params.c++

n_in.o: ${SRC}/n_in.c++
	${COMPILER} -c ${FLAGS} ${SRC}/n_in.c++

kernel.o: ${SRC}/kernel.c++
	${COMPILER} -c ${FLAGS} ${SRC}/kernel.c++

parse_args.o: ${SRC}/parse_args.c++
	${COMPILER} -c ${FLAGS} ${SRC}/parse_args.c++

moments.o: ${SRC}/moments.c++
	${COMPILER} -c ${FLAGS} ${SRC}/moments.c++

theta.o: ${SRC}/theta.c++
	${COMPILER} -c ${FLAGS} ${SRC}/theta.c++

Particle.o: ${SRC}/Particle.c++
	${COMPILER} -c ${FLAGS} ${SRC}/Particle.c++

Cell.o:	${SRC}/Cell.c++
	${COMPILER} -c ${FLAGS} ${SRC}/Cell.c++	

clean:
	rm ${TARGET} *.o

clean-data:
	rm data/*.txt

backup:
	tar -czvf ${TARGET}_src.tar.gz * --exclude *.gz #*.f *.h Makefile start

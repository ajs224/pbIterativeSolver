# pbIterativeSolver Makefile
# A. J. Smith (ajs224@cam.ac.uk)
#
DEBUG = -g #-lefence #-g
#PROFILE = -pg
#OPTS = O3
#OPTS = -Ofast -flto -fwhole-program -mtune=native # satsuma
#OPTS = -O3 -ffast-math # banksy
OPTS = -Ofast -flto -fwhole-program -mtune=native # new cluster

FLAGS = -I./include ${OPTS} ${PROFILE} ${DEBUG}
COMPILER = g++
#COMPILER = /opt/intel/Compiler/11.0/083/bin/intel64/icc
TARGET= pbIterativeSolver
SRC=./source

${TARGET}: ${TARGET}.o blurb.o mfa_params.o n_in.o Cell.o Solver.o #parse_args.o #moments.o Particle.o #theta.o kernel.o
	${COMPILER} -o ${TARGET} ${FLAGS} ${TARGET}.o blurb.o mfa_params.o n_in.o Cell.o Solver.o # parse_args.o kernel.o

${TARGET}.o: ${SRC}/${TARGET}.c++
	${COMPILER} -c ${FLAGS} ${SRC}/${TARGET}.c++

blurb.o: ${SRC}/blurb.c++
	${COMPILER} -c ${FLAGS} ${SRC}/blurb.c++

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

Solver.o: ${SRC}/Solver.c++
	${COMPILER} -c ${FLAGS} ${SRC}/Solver.c++

clean:
	rm ${TARGET} *.o

clean-data:
	rm data/*.txt

backup:
	tar -czvf ${TARGET}_src.tar.gz * --exclude *.gz #*.f *.h Makefile start

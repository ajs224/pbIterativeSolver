# MFA Makefile
# A. J. Smith (ajs224@cam.ac.uk)
#
FLAGS = -g -I./include #-fast
COMPILER = g++
#COMPILER = /opt/intel/Compiler/11.0/083/bin/intel64/icc
TARGET= pbIterativeSolver
SRC=./source

${TARGET}: ${TARGET}.o  moments.o Particle.o #kernel.o theta.o
	${COMPILER} -o ${TARGET} ${FLAGS} ${TARGET}.o  moments.o Particle.o #kernel.o theta.o

${TARGET}.o: ${SRC}/${TARGET}.c++
	${COMPILER} -c ${FLAGS} ${SRC}/${TARGET}.c++

kernel.o: ${SRC}/kernel.c++
	${COMPILER} -c ${FLAGS} ${SRC}/kernel.c++

moments.o: ${SRC}/moments.c++
	${COMPILER} -c ${FLAGS} ${SRC}/moments.c++

theta.o: ${SRC}/theta.c++
	${COMPILER} -c ${FLAGS} ${SRC}/theta.c++

Particle.o: ${SRC}/Particle.c++
	${COMPILER} -c ${FLAGS} ${SRC}/Particle.c++

clean:
	rm ${TARGET} *.o

clean-data:
	rm data/*.txt

backup:
	tar -czvf ${TARGET}_src.tar.gz * --exclude *.gz #*.f *.h Makefile start

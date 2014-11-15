CC="g++"
CC_FLAGS=../heap.cpp 
all: test1 test2
	

test1: forestNode.cpp
	${CC} -o test forestNode.cpp ${CC_FLAGS}
	./test > output
	diff output forestNode.out
	rm test output

test2: binomialHeap.cpp
	${CC} -o test binomialHeap.cpp ${CC_FLAGS}
	./test > output
	diff output binomialHeap.out
	rm test output


clean:
	rm test output *~

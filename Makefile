CC=g++ -O3 -Wall -std=c++17

# List of source files for the framework itself
FRAMEWORK_SOURCES=assert_funcs.cpp macros.cpp TestRig.cpp

# Command to compile an app
CMD=${CC} -o $@ $^ -ldl

test: test.cpp ${FRAMEWORK_SOURCES}
	${CMD} -pthread

clean:
	rm -f test

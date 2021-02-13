CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = sorcery
FILES := $(wildcard *.cc)
OBJECTS_CC = $(FILES)
OBJECTS = ${OBJECTS_CC:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}



${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

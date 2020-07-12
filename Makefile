CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = posn.o piece.o rook.o knight.o pawn.o king.o bishop.o queen.o grid.o textdisplay.o main.o graphicsdisplay.o window.o ai2.o ai3.o ai4.o history.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


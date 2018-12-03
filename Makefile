TESTFILES=$(wildcard tests/*.dat)
OUTPUTS=$(TESTFILES:.dat=.out)
SRC=$(wildcard *.cpp)
EXEC=coudert-exec
CXX=g++

all: $(EXEC)

tests: $(OUTPUTS)

$(EXEC): $(SRC)
	$(CXX) $(SRC) -o $(EXEC) -Wall -lgmpxx -lgmp

%.out: %.dat $(EXEC)
	./$(EXEC) -b $< > $@

clean:
	rm tests/*.out $(EXEC)
CPP = /usr/bin/c++
CXXFLAGS = -c -Wall -Wpedantic -std=c++11
RM = /bin/rm
SOURCES = main.cpp util.cpp bridge.cpp lancontroller.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = myprogram

all: $(EXECUTABLE)

debug: CFLAGS += -g -DDEBUG

debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CPP) $(OBJECTS) -o $@

%.o: %.c %.h
	$(CPP) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

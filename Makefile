# working dirs

SRCDIR = ./src
BUILDDIR = ./obj

CC=g++

CFLAGS=-std=c++11 -I ./include/ -c -Wall -Wno-reorder

LDFLAGS=

#SOURCES = main.cpp FileLoader.cpp Context.cpp FileSorter.cpp Sequence.cpp SortResult.cpp SortStrategy.cpp HeapSortStrategy.cpp InsertionSortStrategy.cpp MergeSortStrategy.cpp QuickSortStrategy.cpp ShellSortStrategy.cpp SelectionSortStrategy.cpp
EXECUTABLE=kmeans
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,${SOURCES})

all: $(EXECUTABLE)
  
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

debug: ${SOURCES}
	$(CC) -g -gdwarf-2 -std=c++11 ${SOURCES} -o kmeans

clean:
	@rm -f $(EXECUTABLE) ${OBJECTS}


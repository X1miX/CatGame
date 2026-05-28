TARGET = $(BUILDDIR)/CatGame

CXX = g++

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
BUILDDIR = build


SOURCES = $(wildcard $(SRCDIR)/*.cpp)

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))


all: $(BUILDDIR) $(TARGET)


$(BUILDDIR):
	mkdir -p $@


$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)


$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@


run: all
	./$(TARGET)


clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean run
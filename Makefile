TARGET = $(BUILDDIR)/CatGame

CXX = g++

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
BUILDDIR = build


SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
CXX_FILES = $(wildcard $(SRCDIR)/*cpp $(SRCDIR)/*.h)

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

format:
	clang-format -i $(CXX_FILES)

update:
	sudo apt-get update 
	sudo apt-get install -y clang-format

.PHONY: all clean format update

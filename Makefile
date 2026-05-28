TARGET = $(BUILDDIR)/CatGame

CXX = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
BUILDDIR = build

SOURCES = $(SRCDIR)/movement.cpp $(SRCDIR)/objects.cpp $(SRCDIR)/func.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

CXX_FILES = $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*.h)

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $@

$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) -c $< -o $@

format:
	@clang-format -i $(CXX_FILES)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

update:
	sudo apt-get update 
	sudo apt-get install -y clang-format

.PHONY: all clean format update
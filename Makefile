TARGET = $(BUILDDIR)/CatGame

CXX = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
BUILDDIR = build

SOURCES = $(SRCDIR)/movement.cpp $(SRCDIR)/objects.cpp $(SRCDIR)/func.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $@

$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
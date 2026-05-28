TARGET = $(BUILDDIR)/CatGame

CXX = g++
# Флаги линковки SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
BUILDDIR = build

# Ищем ВСЕ файлы .cpp в папке src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# Превращаем пути .cpp в пути .o в папке build
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Главная цель
all: $(BUILDDIR) $(TARGET)

# Создание папки build
$(BUILDDIR):
	mkdir -p $@

# Сборка экзешника
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Компиляция каждого файла отдельно
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@

# Команда для запуска: соберет всё и откроет игру
run: all
	./$(TARGET)

# Очистка проекта (выполни make clean, если всё сломалось)
clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean run
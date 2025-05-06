# Компилятор (используем gcc, но для C++ это нестандартно)
CC := gcc

# Флаги компиляции для C++ (явно указываем язык и библиотеки)
CFLAGS := -Wall -Wextra -std=c++17 -O2 -lstdc++

# Имя исполняемого файла
TARGET := result

# Исходные файлы (.cpp)
SRCS := clock.cpp main.cpp inputEvent.cpp

# Объектные файлы (.o)
OBJS := $(SRCS:.cpp=.o)

# Основная цель сборки
all: $(TARGET)

# Сборка исполняемого файла из объектных
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Правило для компиляции .cpp в .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Заголовочные зависимости
clock.o: clock.hpp
inputEvent.o: inputEvent.hpp
main.o: computer.hpp  # Если main.cpp использует computer.hpp

# Очистка
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

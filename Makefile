# Компилятор
CXX := g++

# Флаги компиляции
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# Имя исполняемого файла
TARGET := result

# Исходные файлы (.cpp)
SRCS := clock.cpp main.cpp inputEvent.cpp computer.cpp

# Объектные файлы (.o)
OBJS := $(SRCS:.cpp=.o)

# Основная цель сборки
all: $(TARGET)

# Сборка исполняемого файла из объектных
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lstdc++

# Правило для компиляции .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Заголовочные зависимости
clock.o: clock.hpp
inputEvent.o: inputEvent.hpp computer.hpp
computer.o: computer.hpp
main.o: inputEvent.hpp clock.hpp computer.hpp

# Очистка
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

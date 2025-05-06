# Компилятор и флаги
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2
LDFLAGS := -lstdc++

# Целевые файлы
TARGET := result
SRCS := clock.cpp main.cpp inputEvent.cpp computer.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := clock.hpp inputEvent.hpp computer.hpp

# Основные цели
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Шаблонное правило для объектных файлов
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Явные зависимости (для более точного контроля)
clock.o: clock.hpp
inputEvent.o: inputEvent.hpp computer.hpp
computer.o: computer.hpp
main.o: $(DEPS)

# Тест запуска (дополнительная цель)
test: $(TARGET)
	@echo "Запуск с тестовым файлом..."
	@./$(TARGET) test_data.txt

# Очистка
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean test

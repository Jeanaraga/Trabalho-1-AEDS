# Compilador e flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Pastas
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/objects
APP := $(BUILD_DIR)/app

# Arquivos fonte
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(SRCS:.cpp=.o)
OBJS := $(patsubst %.o,$(OBJ_DIR)/%.o,$(notdir $(OBJS)))

# Regra principal
all: $(APP)

# Compila o app
$(APP): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compila cada .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(BUILD_DIR)

# Rodar o app
run: all
	./$(APP)

.PHONY: all clean run

# 编译器与路径设置
CC = gcc
CFLAGS = -Wall -Iinclude -MMD -g
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
LIB_DIR = lib
LIB_NAME = libmake.a

# 自动收集源文件与目标文件
# filter-out：排除 main.c，因为我们不希望它也被打包进 .a 中
SRC = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
 # patsubst：将 src/foo.c 变成 build/foo.o
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
# DEP：将 build/foo.o 转成 build/foo.d，是自动生成的依赖文件
DEP = $(OBJ:.o=.d)

# 主程序与静态库路径
BIN = $(BIN_DIR)/main
LIB = $(LIB_DIR)/$(LIB_NAME)

# 默认目标：构建可执行程序
all: $(BIN)

# 生成最终程序：main.c + lmake.a
$(BIN): $(LIB) $(OBJ_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o -L$(LIB_DIR) -lmake -o $@

# 打包静态库
$(LIB): $(OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

# 编译所有模块为 .o（排除 main.c）
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 编译 main.c
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 自动包含头文件依赖
-include $(DEP)

# 清理构建产物
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)
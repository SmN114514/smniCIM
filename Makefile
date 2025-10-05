CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
LIBS = -lncurses

# 源文件列表
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
HEADERS = $(wildcard include/*.h)

# 最终目标
smnicim: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

# 编译规则
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -Iinclude -c -o $@ $<

# 清理
clean:
	rm -f src/*.o smnicim

# 安装到系统
install: smnicim
	cp smnicim /usr/local/bin/

# 运行测试
run: smnicim
	./smnicim

# 指定編譯器，可視情況改成 clang++ 等
CC = g++
CFLAGS = -Wall -std=c++17 -g

# 包含標頭檔路徑
INCLUDES = -I include

# 找到所有 .cpp 檔案
SRC = $(wildcard src/*.cpp)

# 將 .cpp 對應為同名的 .o 檔
OBJ = $(SRC:.cpp=.o)

# 要生成的可執行檔名稱
EXEC = legalizer

# 透過 "make" 或 "make all" 都會執行這個目標
all: $(EXEC)

# 連結階段：將所有 .o 檔連結起來生成執行檔
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# 編譯階段：每個 .cpp 對應產生 .o 檔
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 清除編譯產物
clean:
	rm -rf $(OBJ) $(EXEC) gmon.out

default: 
	./legalizer 1000 0.6 ./testcase/case1.def output.def

# 新增專門用來支援 gprof 的目標
profile: clean
	$(MAKE) CFLAGS="$(CFLAGS) -pg"

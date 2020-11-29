# 请务必使用 g++ >= 8.0.0 或 clang++ >= 6.0.0
# 否则无法编译 c++17 <filesystem>，并且不保证 RVO、NRVO（返回值优化）
CXX=g++-8

# 代码使用纯 c++17 编写。
# 要开 -O2 
CFLAGS= -std=c++17 -O2 -march=native -I. -lstdc++fs -fprofile-use=./profile

all: *.cpp */*.cpp
	$(CXX)  $^ -o algo_lab1 $(CFLAGS)
profile: *.cpp */*.cpp
	$(CXX) -fprofile-generate=./profile $^ -o ./algo_lab1 $(CFLAGS)

run: all
	./algo_lab1 ../input ../output

check:
	diff ../output/count_sort/result_18.txt ../output/heap_sort/result_18.txt
	diff ../output/count_sort/result_18.txt ../output/insertion_sort/result_18.txt
	diff ../output/count_sort/result_18.txt ../output/quick_sort/result_18.txt
	diff ../output/count_sort/result_18.txt ../output/merge_sort/result_18.txt


/**
 * @file main.cpp
 * @author Yuantian Ding (dnailzb@outlook.com)
 * @brief The main program to test the time cost of each algorithm.
 * @version 0.1
 * @date 2020-11-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "simple_metrics/metrics.hpp"
#include "sort/sort.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <functional>
#include <valarray>

namespace fs = std::filesystem;

/**
 * @brief read the input file to std::vector.
 * 
 * @tparam T 
 * @param p 
 * @return std::vector<T> 
 */
template<typename T>
std::vector<T> read_to_vector(const fs::path& p) {
    std::ifstream ifs(p);

    std::vector<T> arr;
    arr.reserve(262144);

    T temp;
    while(ifs >> temp) {
        arr.push_back(temp);
    }
    return arr;
}

/**
 * @brief Save the elements between iterator begin and end to file at p.
 * 
 * @tparam IterT Iterator Type.
 * @param begin 
 * @param end 
 * @param p 
 */
template<typename IterT>
void save_to_file(IterT begin, IterT end, const fs::path& p) {
    std::ofstream ofs(p);

    for(auto it = begin; it != end; it++) {
        ofs << *it << " ";
    }

    ofs << std::endl;

    if(!fs::exists(p)) {
        throw std::runtime_error("save to file failed");
    }
}


/**
 * @brief Sort the vector and save the result to <output_path>/<sort_method_name>/<result_file_name>.
 * 
 * @tparam F sort function type for sort_func.
 * @tparam T sort element type. (e.g. int, uint32_t)
 * @param sort_func sort function (e.g. count_sort::count_sort<IteratorType>, std::sort<IteratorType>)
 * @param copied_vec input vector (copied to avoid changing the original input).
 * @param size size of input
 * @param output_path path of the folder 'output/'
 * @param sort_method_name name of the sort method (e.g. count_sort)
 * @param result_file_name name of the result file (e.g. result_n.txt)
 */
template<typename F, typename T>
inline void sort_and_save(
    F sort_func,
    std::vector<T> copied_vec,
    std::size_t size,
    const fs::path& output_path,
    const std::string& sort_method_name,
    const std::string& result_file_name
) {
    // check path of <output_path>/<sort_method_name>
    if(!fs::is_directory(output_path/sort_method_name)) {
        fs::create_directories(output_path/sort_method_name);
    }

    std::cout << "method = " << sort_method_name << std::endl;

    auto begin = copied_vec.begin();

    // run sort function and measuring time.
    {
        METRICS_FUNC_TIME(sort_method_name)  // measuring the time and save to 'time.txt'
        sort_func(begin, begin + size);
    }

    if(size <= 8) {
        std::cout << "\tsort result = ";
        for(auto it = begin; it != begin + size; it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    save_to_file(begin, begin + size, output_path / sort_method_name / result_file_name);
}


int main(int argc, char ** argv) {
    using namespace std::string_literals;

    if(argc == 3) {
        fs::path input_path = argv[1];
        fs::path output_path = argv[2];

        auto&& input_vec = read_to_vector<uint16_t>(input_path / "input.txt");

        METRICS.enableAt(output_path);

        if(fs::exists(output_path)) {
            fs::remove_all(output_path);
        }

        // input size from 2^3 to 2^18
        for(auto i = 3; i <= 18; i++) {

            std::cout << "input_size = " << (1 << i) << std::endl;
            
            // specify the iterator used by all sort algorithm.
            using IterT = std::vector<uint16_t>::iterator;

            // get the name of result file.
            auto result_file_name = "result_"s + std::to_string(i) + ".txt";

            sort_and_save(           heap_sort::heap_sort<IterT>, input_vec, 1 << i, output_path, "heap_sort", result_file_name);
            sort_and_save( insertion_sort::insertion_sort<IterT>, input_vec, 1 << i, output_path, "insertion_sort", result_file_name);
            sort_and_save(         merge_sort::merge_sort<IterT>, input_vec, 1 << i, output_path, "merge_sort", result_file_name);
            sort_and_save(         quick_sort::quick_sort<IterT>, input_vec, 1 << i, output_path, "quick_sort", result_file_name);
            sort_and_save(         count_sort::count_sort<IterT>, input_vec, 1 << i, output_path, "count_sort", result_file_name);
            sort_and_save(                      std::sort<IterT>, input_vec, 1 << i, output_path, "std::sort", result_file_name);
        }

        return 0;
    } else {
        std::cerr << "algolab1 <input> <output>" << std::endl;
        return 1;
    }
}

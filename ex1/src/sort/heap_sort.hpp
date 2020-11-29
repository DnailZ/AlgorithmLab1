#pragma once

#include "simple_metrics/metrics.hpp"
#include <valarray>
#include <iostream>
namespace heap_sort{
    

    using size_t = std::size_t;

    inline int left_of(std::size_t i) { return 2 * (i + 1) - 1; }
    inline int right_of(std::size_t i) { return 2 * (i + 1); }

    template<typename RandomIt>
    void max_heapify(RandomIt begin, RandomIt it, RandomIt end) {
        auto l = begin + left_of(it - begin);
        auto r = begin + right_of(it - begin);

        RandomIt largest;
        
        if(l < end && *l > *it) {
            largest = l;
        } else {
            largest = it;
        }

        if(r < end && *r > *largest) {
            largest = r;
        }

        if(largest != it) {
            std::swap(*largest, *it);
            max_heapify(begin, largest, end);
        }
    }

    template<typename RandomIt>
    inline void build_max_heap(RandomIt begin, RandomIt end) {
        auto it = begin + (end - begin)/2;
        for(; it >= begin; it--) {
            max_heapify(begin, it, end);
        }
        max_heapify(begin, begin, end);
    }

    /**
     * @brief Heap sort at a Random iterator.
     * 
     * @tparam RandomIt A type of LegacyRandomAccessIterator.
     * @param begin 
     * @param end 
     */
    template<typename RandomIt>
    void heap_sort(RandomIt begin, RandomIt end) {
        build_max_heap(begin, end);
        for(auto it = end - 1; it > begin; it--) {
            std::swap(*begin, *it);
            end--;
            max_heapify(begin, begin, end);
        }
    }

} // namespace heap_sort


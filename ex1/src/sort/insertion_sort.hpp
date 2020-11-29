#pragma once

/**
 * @file insertion_sort.hpp
 * @author Yuantian Ding (you@domain.com)
 * @brief insert sort implementation.
 * @version 0.1
 * @date 2020-11-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "simple_metrics/metrics.hpp"
#include <valarray>

namespace insertion_sort {

    /**
     * @brief Insertion sort at a Random iterator.
     * 
     * @tparam RandomIt A type of LegacyRandomAccessIterator.
     * @param begin 
     * @param end 
     */
    template<typename RandomIt>
    void insertion_sort(RandomIt begin, RandomIt end) {
        for(auto q = begin + 1; q != end; q++) {
            auto key = *q;
            auto p = q - 1;
            while(p >= begin && *p > key) {
                *(p+1) = *p;
                --p;
            }
            *(p+1) = key;
        }
    }

} // namespace insert_sort


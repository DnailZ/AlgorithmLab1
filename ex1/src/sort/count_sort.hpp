#pragma once

#include "simple_metrics/metrics.hpp"
#include <valarray>
#include <iostream>

namespace count_sort {
    const std::size_t kValueMax = 32767;

    template<typename RandomIt, typename ItemT>
    std::valarray<ItemT> sorted(RandomIt begin, RandomIt end, ItemT value_max = 32767) { 
        std::valarray<ItemT> ret(end - begin);
        std::valarray<ItemT> C((int)0, value_max + 1);

        for(auto it = begin; it < end; it++) {
            C[*it]++;
        }
        for(auto it = std::begin(C) + 1; it < std::end(C); it++) {
            *it += *(it - 1);
        }
        for(auto it = end - 1; it >= begin; it--) {
            ret[C[*it] - 1] = *it;
            C[*it]--;
        }
        return ret;
    }

    /**
     * @brief Count sort at a Random iterator. the input value should be in the range of [0, kValueMax]. 
     * 
     * @tparam RandomIt A type of LegacyRandomAccessIterator.
     * @param begin 
     * @param end 
     */
    template<typename RandomIt>
    inline void count_sort(RandomIt begin, RandomIt end) {
        auto&& sorted_vec = sorted(begin, end, kValueMax);

        std::copy(std::begin(sorted_vec), std::end(sorted_vec), begin);
    }

} // namespace count_sort

#pragma once

#include "simple_metrics/metrics.hpp"
#include <valarray>

namespace quick_sort {
    
    template<typename RandomIt>
    RandomIt partition(RandomIt begin, RandomIt end) {
        using ItemT = decltype(*begin);

        auto x = *(end - 1);
        auto p = begin - 1;
        for(auto q = begin; q < end - 1; q++) {
            if(*q < x) {
                p++;
                std::swap(*p, *q);
            }
        }
        std::swap(*(p + 1), *(end - 1));
        return p + 1;
    }

    /**
     * @brief Quick sort at a Random iterator.
     * 
     * @tparam RandomIt A type of LegacyRandomAccessIterator.
     * @param begin 
     * @param end 
     */
    template<typename RandomIt>
    void quick_sort(RandomIt begin, RandomIt end) {
        if(end - begin > 1) {
            auto mid = partition(begin, end);
            quick_sort(begin, mid);
            quick_sort(mid + 1, end);
        }
    }

} // namespace quick_sort

#pragma once

#include "simple_metrics/metrics.hpp"
#include <valarray>
#include <limits>

namespace merge_sort{

    template<typename RandomIt>
    void merge(RandomIt begin, RandomIt mid, RandomIt end) {
        using ItemT = typename std::remove_reference<decltype(*begin)>::type;

        auto n1 = mid - begin;
        auto n2 = end - mid;
        
        std::valarray<ItemT> L(n1 + 1);
        std::valarray<ItemT> R(n2 + 1);

        std::copy(begin, mid, std::begin(L));
        L[n1] = std::numeric_limits<ItemT>::max();

        std::copy(mid, end, std::begin(R));
        R[n2] = std::numeric_limits<ItemT>::max();

        auto p = std::begin(L);
        auto q = std::begin(R);

        for(auto r = begin; r < end; r++) {
            if(*p <= *q) {
                *r = *p;
                p++;
            } else {
                *r = *q;
                q++;
            }
        }
    }

    /**
     * @brief Merge sort at a Random iterator.
     * 
     * @tparam RandomIt A type of LegacyRandomAccessIterator.
     * @param begin 
     * @param end 
     */
    template<typename RandomIt>
    void merge_sort(RandomIt begin, RandomIt end) {
        if(end - begin > 1){
            auto mid = begin + (end - begin)/2;
            merge_sort(begin, mid);
            merge_sort(mid, end);
            merge(begin, mid, end);
        }
    }


} // namespace merge_sor

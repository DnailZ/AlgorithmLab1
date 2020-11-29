#pragma once

/**
 * @file metrics.hpp
 * @author Yuantian Ding
 * @brief a simple global varible to metrics the time and count of your code.
 * @version 0.1
 * @date 2020-11-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <filesystem>
#include <fstream>
#include <mutex>
#include <chrono>

//! a simple metrics library for measuring time and distribution.
namespace simple_metrics {

    namespace fs = std::filesystem;
    namespace chrono = std::chrono;

    using lock_guard = std::lock_guard<std::mutex>;
    using high_resolution_clock = chrono::high_resolution_clock;
    using time_point = chrono::time_point<std::chrono::high_resolution_clock>;
    
    /**
     * @brief Timer class for `Metrcs::raiiTimer()`. Don't tell me you don't know RAII.
     * 
     */
    class RaiiTimer {
        std::ofstream file;
        std::mutex& mutex;
        time_point start_time;
        bool enable;

        public:
        RaiiTimer(std::mutex& _mutex);

        RaiiTimer(const fs::path& path, std::mutex& _mutex);

        ~RaiiTimer();
    };

    
    /**
     * @brief  Metrics class (for the global varible `graphwalker::metrics::metrics`)
     * 
     */
    class Metrics {
        
        // whether to enable this `Metrics` class
        bool enable;

        fs::path dirpath;

        // just lock the RaiiTimer
        std::mutex mutex;

        public:
        /**
        * @brief Construct a `Metrics` that does NOT do anything.
        * 
        */
        Metrics();

        /**
        * @brief Enable the Metrics at a directory.
        * 
        * @param dir 
        */
        void enableAt(fs::path dir);

        /**
        * @brief Disable the Metrics.
        * 
        */
        void disable();

        /**
        * @brief create an Timer uses c++ RAII
        * 
        * @param name the name of the timer. (the data will be saved in `$dir/$name`).
        * @return RaiiTimer 
        */
        RaiiTimer raiiTimer(const std::string& name);

        /**
         * @brief add an integer to the record file.
         * 
         * @param name file name
         * @param integer value
         */
        void recordInt(const std::string& name, uint64_t integer);

        /**
         * @brief output report to a ostream.
         * 
         * @param output 
         */
        void report(std::ostream & output);

    };

    //! global varible for metrics.
    extern Metrics metrics;

    inline RaiiTimer timer(const std::string& name);


} // namespace simple_metrics


/**
 * @brief Shortcut for global metrics object.
 * 
 */
#define METRICS simple_metrics::metrics

/**
 * @brief Count time for the whole function.
 * 
 */
#define METRICS_FUNC_TIME(label) auto&& __timer__ = simple_metrics::metrics.raiiTimer(label);
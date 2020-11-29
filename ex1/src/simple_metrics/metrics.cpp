
#include "simple_metrics/metrics.hpp"
#include <iostream>
namespace simple_metrics{

    RaiiTimer::RaiiTimer(std::mutex& _mutex) : mutex(_mutex), enable(false) {}
    RaiiTimer::RaiiTimer(const fs::path& path, std::mutex& _mutex) : file(path, std::ios_base::app), mutex(_mutex), enable(true) {
        start_time = high_resolution_clock::now();
    }
    RaiiTimer::~RaiiTimer() {
        if(enable) {
            auto end_time = high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
            lock_guard lock(mutex);
            file << duration << std::endl;
            std::cout << "\ttime cost(ns): " + std::to_string(duration) << std::endl;
        }
    }

    Metrics::Metrics(): enable(false) {}

    void Metrics::enableAt(fs::path dir) {
        lock_guard lock(mutex);
        dirpath = dir;
        enable = true;
        // if(fs::exists(dir)) {
        //     fs::remove_all(dir);
        // }
        fs::create_directory(dir);
    }
    void Metrics::disable() {
        lock_guard lock(mutex);
        enable = false;
    }

    RaiiTimer Metrics::raiiTimer(const std::string& name) {
        if(enable) {
            return RaiiTimer(dirpath / name / "time.txt", mutex);
        } else {
            return RaiiTimer(mutex);
        }
    }

    void Metrics::recordInt(const std::string& name, uint64_t integer) {
        std::ofstream(dirpath / name, std::ios::app) << integer << std::endl;
    }

    void Metrics::report(std::ostream & output) {
        for(const auto& entry: fs::directory_iterator(dirpath)) {
            if(entry.is_regular_file()) {
                auto&& input = std::ifstream(entry.path());
                uint64_t time;
                uint64_t max_time = 0;
                uint64_t min_time = INT64_MAX;
                uint64_t total_time = 0;
                uint64_t count = 0;

                while(input >> time) {
                    max_time = std::max(time, max_time);
                    min_time = std::min(time, min_time);
                    total_time += time;
                    count += 1;
                }

                output << entry.path().string() << " :" << std::endl
                    << "    averge = " << double(total_time)/count << " ns" << std::endl
                    << "    max    = " << max_time                 << " ns" << std::endl
                    << "    min    = " << min_time                 << " ns" << std::endl
                    << "    total  = " << total_time               << " ns" << std::endl
                    << "    count  = " << count                            << std::endl;
            } else {
                throw std::runtime_error("entry is not a regular file");
            }
        }
    }

    Metrics metrics;

    inline RaiiTimer timer(const std::string& name) {
        return metrics.raiiTimer(name);
    }

} // namespace simple_metrics


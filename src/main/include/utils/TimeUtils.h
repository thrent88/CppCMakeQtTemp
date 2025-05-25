//
// Created by Thrent on 2025/5/24.
//

#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <chrono>

namespace utils {
    class TimeUtils {
    public:

        using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

        /**
         * 获取当前格式化时间
         * @param format
         * @return
         */
        static std::string getCurrentTime(std::string format = "%Y%m%d-%H%M%S");

        /**
         * 时间比较
         * @param input 比较
         * @param target 目标时间
         * @return
         */
        static bool isBefore(TimePoint input, TimePoint target);
    };
}


#endif //TIMEUTILS_H

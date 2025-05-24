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
        /**
         * 获取当前格式化时间
         * @param format
         * @return
         */
        static std::string getCurrentTime(std::string format = "%Y%m%d-%H%M%S");
    };
}


#endif //TIMEUTILS_H

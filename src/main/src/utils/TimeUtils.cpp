//
// Created by Thrent on 2025/5/24.
//

#include "utils/TimeUtils.h"

#include <iomanip>
#include <sstream>

namespace utils {
    std::string TimeUtils::getCurrentTime(std::string format) {
        std::stringstream ss;
        std::chrono::system_clock::time_point a = std::chrono::system_clock::now(); //时间点可以做差
        time_t t1 = std::chrono::system_clock::to_time_t(a); //time_t可以格式化
        ss << std::put_time(localtime(&t1), format.c_str());
        std::string str1 = ss.str();
        return str1;
    }
}

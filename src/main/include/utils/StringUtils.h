//
// Created by Thrent on 2025/5/25.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>

namespace utils {
    class StringUtils {
    public:
        /**
         * 去除前后空格
         * @param str
         * @return
         */
        static std::string trim(std::string str);

        /**
         * 字符串比较
         * @param str1
         * @param str2
         * @param ignoreCase
         * @return
         */
        static bool equal(std::string str1, std::string str2, bool ignoreCase = false);

        /**
         * GBK转UTF8
         * @param strGBK
         * @return
         */
        static std::string GBK2UTF8(std::string strGBK);

        /**
         * UTF8转GBK
         * @param strUTF8
         * @return
         */
        static std::string UTF82GBK(std::string strUTF8);
    };
}


#endif //STRINGUTILS_H

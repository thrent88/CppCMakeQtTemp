//
// Created by Thrent on 2025/5/25.
//

#include "utils/StringUtils.h"

#include <algorithm>

#if defined(_WIN32) || defined(_MSC_VER) || defined(WIN64)
#include <Windows.h>
#elif defined(__linux__) || defined(__GNUC__)
#include <iconv.h>
#endif

namespace utils {
    std::string StringUtils::trim(std::string s) {
        size_t n = s.find_last_not_of(" \r\n\t");
        if (n != std::string::npos) {
            s.erase(n + 1, s.size() - n);
        }
        n = s.find_first_not_of(" \r\n\t");
        if (n != std::string::npos) {
            s.erase(0, n);
        }
        return s;
    }

    bool StringUtils::equal(std::string str1, std::string str2, bool ignoreCase) {
        if (ignoreCase) {
            std::transform(str1.begin(), str1.end(), str1.begin(), [](unsigned char c) { return std::tolower(c); });
            std::transform(str2.begin(), str2.end(), str2.begin(), [](unsigned char c) { return std::tolower(c); });
        }
        return str1 == str2;
    }

    std::string StringUtils::GBK2UTF8(std::string str) {
#if defined(_WIN32) || defined(_MSC_VER) || defined(WIN64)
        int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
        wchar_t *wstr = new wchar_t[len + 1ull];
        memset(wstr, 0, len + 1ull);
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
        len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
        char *cstr = new char[len + 1ull];
        memset(cstr, 0, len + 1ull);
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, cstr, len, NULL, NULL);
        std::string res(cstr);

        if (wstr) delete[] wstr;
        if (cstr) delete[] cstr;

        return res;
#elif defined(__linux__) || defined(__GNUC__)
        size_t len = str.size() * 2 + 1;
        char* temp = new char[len];
        if (EncodingConvert("gb2312", "utf-8", const_cast<char*>(str.c_str()), str.size(), temp, len)
            > = 0)
        {

            std::string res;
            res.append(temp);
            delete[] temp;
            return res;
        }
        else
        {

            delete[]temp;
            return str;
        }
#else
        std::cerr << "Unhandled operating system." << std::endl;
        return str;
#endif
    }

    std::string StringUtils::UTF82GBK(std::string str) {
#if defined(_WIN32) || defined(_MSC_VER) || defined(WIN64)
        // calculate length
        int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
        wchar_t *wsGbk = new wchar_t[len + 1ull];
        // set to '\0'
        memset(wsGbk, 0, len + 1ull);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wsGbk, len);
        len = WideCharToMultiByte(CP_ACP, 0, wsGbk, -1, NULL, 0, NULL, NULL);
        char *csGbk = new char[len + 1ull];
        memset(csGbk, 0, len + 1ull);
        WideCharToMultiByte(CP_ACP, 0, wsGbk, -1, csGbk, len, NULL, NULL);
        std::string res(csGbk);

        if (wsGbk) {
            delete[] wsGbk;
        }

        if (csGbk) {
            delete[] csGbk;
        }

        return res;
#elif defined(__linux__) || defined(__GNUC__)
        size_t len = str.size() * 2 + 1;
        char* temp = new char[len];
        if (EncodingConvert("utf-8", "gb2312", const_cast<char*>(str.c_str()),
            str.size(), temp, len) >= 0)
        {

            std::string res;
            res.append(temp);
            delete[] temp;
            return res;
        }
        else
        {

            delete[] temp;
            return str;
        }

#else
        std::cerr << "Unhandled operating system." << std::endl;
        return str;
#endif
    }
}

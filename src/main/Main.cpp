//
// Created by Thrent on 2025/5/24.
//

#ifdef _WIN32

#include <windows.h>
#include <dbghelp.h>
#include <tchar.h>
#include <iostream>

#pragma comment(lib, "dbghelp.lib")

void WriteMiniDump(EXCEPTION_POINTERS* pExceptionPointers) {
    SYSTEMTIME stLocalTime;
    GetLocalTime(&stLocalTime);

    CreateDirectoryA("crash", nullptr);

    TCHAR szFileName[MAX_PATH];
    _stprintf_s(szFileName, MAX_PATH, _T("crash/crash_%04d%02d%02d_%02d%02d%02d.dmp"),
        stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
        stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);

    HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile != INVALID_HANDLE_VALUE) {
        MINIDUMP_EXCEPTION_INFORMATION mdei;

        mdei.ThreadId = GetCurrentThreadId();
        mdei.ExceptionPointers = pExceptionPointers;
        mdei.ClientPointers = FALSE;

        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile,
                          MiniDumpNormal, &mdei, nullptr, nullptr);

        CloseHandle(hFile);
        std::cerr << "MiniDump written to: " << szFileName << std::endl;
    } else {
        std::cerr << "Failed to create dump file." << std::endl;
    }
}

LONG WINAPI MyUnhandledExceptionFilter(EXCEPTION_POINTERS* pExceptionPointers) {
    std::cerr << "Unhandled exception occurred. Writing dump..." << std::endl;
    WriteMiniDump(pExceptionPointers);
    return EXCEPTION_EXECUTE_HANDLER;
}

#endif

#include <QApplication>
#include <QFontDatabase>
#include "view/MainWindow.h"

#include "utils/ex/StackBack.h"
#include "utils/CLI11.hpp"

int main(int argc, char **argv) {
#ifdef _WIN32
    SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
#endif

    QApplication app(argc, argv);

    // 设置字体
    int fontId = QFontDatabase::addApplicationFont(":/font/HeiTi.ttf");
    QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(msyh);
    app.setFont(font);

    MainWindow w;
    w.show();

    CPPTRACE_TRY {
        THROW_EXCEPTION("An error occurred in the main function.");
    } CPPTRACE_CATCH (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << StringStackBack() << std::endl;
    }

    return app.exec();
}

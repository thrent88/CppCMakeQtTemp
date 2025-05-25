set(BIN_NAME ${PROJECT_NAME})

# 设置图标
set(APPICON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources/icon/favicon.ico)
set(RC_FILE ${CMAKE_BINARY_DIR}/app.rc)
configure_file(${PROJECT_SOURCE_DIR}/script/app.rc.in ${RC_FILE} @ONLY)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc
)

# 导入QT
set(QT_VERSION 5)
set(QT_COMPONENTS Core Gui Widgets Xml Svg)
set(QT_LIBS)
foreach (QT_COMPONENT ${QT_COMPONENTS})
    find_package(Qt${QT_VERSION} COMPONENTS ${QT_COMPONENT} REQUIRED)
    LIST(APPEND QT_LIBS Qt${QT_VERSION}::${QT_COMPONENT})
endforeach ()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
LIST(APPEND CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# 用Python生成库
find_package(Python REQUIRED)
# 生成对象ID
execute_process(COMMAND ${Python_EXECUTABLE}
        ${PROJECT_SOURCE_DIR}/script/py/GeneratorObjectID.py
        --path ${CMAKE_CURRENT_SOURCE_DIR}/src
        --out ${CMAKE_BINARY_DIR}/include/app/store
)

execute_process(COMMAND ${Python_EXECUTABLE}
        ${PROJECT_SOURCE_DIR}/script/py/GeneratorForm.py
        --path ${CMAKE_CURRENT_SOURCE_DIR}/form
        --out ${CMAKE_BINARY_DIR}/form
)

# 设置需要链接的库
set(LINK_LIBS
        cpptrace::cpptrace
        asio
        ${QT_LIBS}
        spdlog::spdlog
)

if (${PROJECT_NAME}_WINDOW_EXE)
    add_executable(${BIN_NAME} WIN32 Main.cpp ${SOURCE_FILES} ${RC_FILE})
else ()
    add_executable(${BIN_NAME} Main.cpp ${SOURCE_FILES})
endif ()

target_include_directories(${BIN_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${BIN_NAME} PUBLIC ${LINK_LIBS})
if (MSVC)
    target_compile_options(${BIN_NAME} PRIVATE /Zi PUBLIC /utf-8)
    target_link_options(${BIN_NAME} PRIVATE /DEBUG)
endif ()

# 添加测试
if (${PROJECT_NAME}_TEST)
    add_library(lib${PROJECT_NAME} ${SOURCE_FILES})
    target_link_libraries(lib${PROJECT_NAME} ${LINK_LIBS})
    target_include_directories(lib${BIN_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    if (MSVC)
        target_compile_options(lib${BIN_NAME} PRIVATE /Zi PUBLIC /utf-8)
        target_link_options(lib${BIN_NAME} PRIVATE /DEBUG)
    endif ()
endif ()

# 添加版本打印
add_executable(${BIN_NAME}_version MainVersion.cpp)
target_include_directories(${BIN_NAME}_version PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


set(BIN_NAME ${PROJECT_NAME}_TEST)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL ${PROJECT_SOURCE_DIR}/3rd/googletest-1.17.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
if (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

file(GLOB SOURCE
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(${BIN_NAME} ${SOURCE})
target_link_libraries(${BIN_NAME} gtest gmock lib${PROJECT_NAME})

gtest_discover_tests(${BIN_NAME})

//
// Created by Thrent on 2025/5/24.
//

#include <gtest/gtest.h>
#include <utils/TimeUtils.h>

TEST(Test1, TEST1) {
    std::cout << utils::TimeUtils::getCurrentTime() << '\n';
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


#include "tst_t1.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    InitGoogleMock (&__argc, __argv);
    return RUN_ALL_TESTS();
}

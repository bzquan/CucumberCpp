#include "gtest/gtest.h"
#include "gmock/gmock.h"

int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);

    // Ensures that the tests pass no matter what value of
    // --gmock_catch_leaked_mocks and --gmock_verbose the user specifies.
    testing::GMOCK_FLAG(catch_leaked_mocks) = true;
    testing::GMOCK_FLAG(verbose) = "warning";

    //  TestCatchesLeakedMocksInAdHocTests();
    return RUN_ALL_TESTS();
}


#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MinimalistPrinter.h"

int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);

    // Ensures that the tests pass no matter what value of
    // --gmock_catch_leaked_mocks and --gmock_verbose the user specifies.
    testing::GMOCK_FLAG(catch_leaked_mocks) = true;
    testing::GMOCK_FLAG(verbose) = "warning";

    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    // delete original google test outputter
//    delete listeners.Release(listeners.default_result_printer());

    // Adds a listener to the end.  Google Test takes the ownership.
//    listeners.Append(new MinimalistPrinter);


    //  TestCatchesLeakedMocksInAdHocTests();
    return RUN_ALL_TESTS();
}


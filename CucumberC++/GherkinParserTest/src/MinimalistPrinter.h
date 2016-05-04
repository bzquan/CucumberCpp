#pragma once

#include "gtest/gtest.h"
#include <string>

class MinimalistPrinter : public ::testing::EmptyTestEventListener {
    // Called before a test starts.
    virtual void OnTestStart(const ::testing::TestInfo& test_info) {
        printf("[ RUN      ] %s.%s starting.\n",
//        printf("*** Test %s.%s starting.\n",
                test_info.test_case_name(), test_info.name());
    }

    // Called after a failed assertion or a SUCCEED() invocation.
    virtual void OnTestPartResult(
        const ::testing::TestPartResult& test_part_result) {
        printf("%s in %s:%d\n%s\n",
            test_part_result.failed() ? "*** Failure" : "Success",
            test_part_result.file_name(),
            test_part_result.line_number(),
            test_part_result.summary());
    }

    // Called after a test ends.
    virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
        if (test_info.result()->Failed())
        {
            printf("[  FAILED  ] %s.%s ending.\n",
                //        printf("*** Test %s.%s ending.\n",
                test_info.test_case_name(), test_info.name());
        }
        else
        {
            printf("[       OK ] %s.%s ending.\n", test_info.test_case_name(), test_info.name());
        }
    }
};

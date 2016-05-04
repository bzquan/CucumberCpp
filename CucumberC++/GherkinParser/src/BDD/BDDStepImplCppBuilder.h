#pragma once

#include <string>

namespace CucumberCpp
{
    class BDDStepImplCppBuilder
    {
    public:
        static std::wstring BuildStepImplCpp();

    private:
        static std::wstring BuildStepImps();
        static std::wstring MakeStepComments(BDDStepBuilder& stepBuilder);
    };
}

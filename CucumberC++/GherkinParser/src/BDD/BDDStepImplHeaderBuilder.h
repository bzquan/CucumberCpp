#pragma once

#include <string>

namespace CucumberCpp
{
    class BDDStepImplHeaderBuilder
    {
    public:
        static std::wstring BuildStepImplHeader();

    private:
        static std::wstring BuildIncludes();
        static std::wstring BuildClassBeginning();
        static std::wstring BuildStepDefs();
        static std::wstring BuildRegisterSteps();
        static std::wstring BuildStepBindings();
        static std::wstring BuildClassEnding();
    };
}

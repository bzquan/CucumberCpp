#pragma once

#include <string>

namespace CucumberCpp
{
    class BDDStepModelTemplateBuilder
    {
    public:
        static std::wstring BuildTestModelHeader();
        static std::wstring BuildTestModelImplementation();
    };
}

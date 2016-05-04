#pragma once

#include <string>

namespace CucumberCpp
{
    enum class BDDStepArgType { TableArg, DocStringArg, FloatArg, StringArg, TableColumnArg };

    class BDDStepArg
    {
    public:
        static const std::wstring TableArg;// = L"$table$";
        static const std::wstring DocStringArg;// = L"$doc$";

        BDDStepArg(std::wstring arg);

        int ArgIndex;
        std::wstring& RegexPattern() { return m_RegexPattern; }
        BDDStepArgType ArgType() { return m_ArgType; }
        std::wstring& ArgText() { return m_ArgText; }

        std::wstring StepParam();
        std::wstring StepParamTypeName();

        std::wstring StepFunctionPlaceHolder();

    private:
        void DecideArgType(std::wstring arg);

    private:
        std::wstring m_RegexPattern;
        BDDStepArgType m_ArgType;
        std::wstring m_ArgText;
    };
}

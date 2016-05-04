#include "BDDUtil.h"
#include "StrUtility.h"
#include "BDDStepArg.h"

using namespace std;
using namespace CucumberCpp;

const std::wstring BDDStepArg::TableArg{ L"$table$" };
const std::wstring BDDStepArg::DocStringArg{ L"$doc$" };

BDDStepArg::BDDStepArg(wstring arg)
{
    m_RegexPattern = BDDUtil::StringRegex; // default is a string argument
    m_ArgText = arg;
    DecideArgType(arg);
}

wstring BDDStepArg::StepParam()
{
    switch (m_ArgType)
    {
    case BDDStepArgType::TableArg:
        return L"GherkinTable& table";
    case BDDStepArgType::TableColumnArg:
        return L"GherkinRow& row";
    case BDDStepArgType::DocStringArg:
        return L"std::wstring docStr";
    case BDDStepArgType::FloatArg:
        return wstring(L"double num") + std::to_wstring(ArgIndex);
    case BDDStepArgType::StringArg:
        return wstring(L"std::wstring str") + std::to_wstring(ArgIndex);
    default:
        return wstring(L"std::wstring str") + std::to_wstring(ArgIndex);
    }
}

wstring BDDStepArg::StepParamTypeName()
{
    switch (m_ArgType)
    {
    case BDDStepArgType::TableArg:
        return L"GherkinTable&";
    case BDDStepArgType::TableColumnArg:
        return L"GherkinRow&";
    case BDDStepArgType::DocStringArg:
        return L"std::wstring";
    case BDDStepArgType::FloatArg:
        return L"double";
    case BDDStepArgType::StringArg:
        return L"std::wstring";
    default:
        return L"std::wstring";
    }
}

wstring BDDStepArg::StepFunctionPlaceHolder()
{
    wstring tableColumnName;
    switch (m_ArgType)
    {
    case BDDStepArgType::TableArg:
        return L"_T_";
    case BDDStepArgType::TableColumnArg:
        tableColumnName = m_ArgText.substr(1, m_ArgText.length() - 2);
        return BDDUtil::MakeIdentifier(tableColumnName);
    case BDDStepArgType::DocStringArg:
        return L"_S_";
    case BDDStepArgType::FloatArg:
        return L"_D_";
    case BDDStepArgType::StringArg:
        return L"_S_";
    default:
        return L"";
    }
}

void BDDStepArg::DecideArgType(wstring arg)
{
    if (arg == TableArg)
    {
        m_ArgType = BDDStepArgType::TableArg;
    }
    else if (arg == DocStringArg)
    {
        m_ArgType = BDDStepArgType::DocStringArg;
    }
    else if ((arg.length() == 0) || (arg[0] == L'\"'))
    {
        m_ArgType = BDDStepArgType::StringArg;
        m_RegexPattern = BDDUtil::StringRegex;
    }
    else if ((arg[0] == L'<') && (arg[arg.length() - 1] == L'>'))
    {
        m_ArgType = BDDStepArgType::TableColumnArg;
        m_RegexPattern = arg;
    }
    else
    {
        m_ArgType = BDDStepArgType::FloatArg;
        m_RegexPattern = BDDUtil::FloatRegex;
    }

    StrUtility::ReplaceAll(m_RegexPattern, LR"(\)", LR"(\\)");
    StrUtility::ReplaceAll(m_RegexPattern, LR"(")", LR"(\")");
}

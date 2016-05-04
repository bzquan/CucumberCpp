#pragma once

#include <vector>
#include <string>
#include <stdexcept>

constexpr auto TAG_LINE_REGEX{ LR"(^\s*(@.+)+$)" };
constexpr auto NEWLINE{ L"\n" };

namespace GherkinAst
{
    enum class StepKind {
        GIVEN_STEP,
        WHEN_STEP,
        THEN_STEP,
        AND_STEP,
        BUT_STEP
    };

    class Location;
    class Language;
    class Step;
    class Tag;
    class StepArgument;
    class Example;
    class IHasDescription;
    class ScenarioDefinition;
    class Comment;
}

struct TableParam;

struct GherkinErrorInfo
{
    GherkinErrorInfo(int lineNo = 1, std::wstring errMsg = L"Error") :
        LineNo(lineNo),
        ErrorMsg(errMsg) {}

    int LineNo;
    std::wstring ErrorMsg;
};

class GherkinError : public std::domain_error
{
public:
    GherkinError() :
        domain_error("Error")
    {
    }

    GherkinError(int lineNo, std::wstring errMsg) :
        domain_error("Error")
    {
        append(lineNo, errMsg);
    }

    void append(int lineNo, std::wstring errMsg)
    {
        m_Errors.push_back(GherkinErrorInfo(lineNo, errMsg));
    }
    std::vector<GherkinErrorInfo>& AllErrors() { return m_Errors; }

private:
    std::vector<GherkinErrorInfo> m_Errors;
};

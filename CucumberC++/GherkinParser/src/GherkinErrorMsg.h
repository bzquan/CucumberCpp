#pragma once

#include <string>

class GherkinErrorMsg
{
public:
    GherkinErrorMsg(int lineNo, std::wstring error) :
        m_LineNo(lineNo), m_ErrorMsg(error) {}

    int lineNo() { return m_LineNo; }
    std::wstring errorMsg() { return m_ErrorMsg; }

private:
    int m_LineNo;
    std::wstring m_ErrorMsg;
};

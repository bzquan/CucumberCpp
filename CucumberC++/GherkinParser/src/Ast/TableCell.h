#pragma once

#include <string>

namespace GherkinAst
{
    class TableCell
    {
    public:
        TableCell(std::wstring value) :
            m_Value(value)
        {
            TrimValue();
        }

        std::wstring& Value() { return m_Value; }
        std::wstring& TrimmedValue() { return m_TrimmedValue; }

    private:
        void TrimValue()
        {
            m_TrimmedValue = m_Value;//value.Replace("\"", string.Empty);
        }

    private:
        std::wstring m_Value;
        std::wstring m_TrimmedValue;
    };
}
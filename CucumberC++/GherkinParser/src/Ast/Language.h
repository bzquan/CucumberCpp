#pragma once

#include <string>
#include "IVisit.h"

namespace GherkinAst
{
    class Language : public IVisit
    {
    public:
        Language(){}
        Language(std::wstring& language) { m_Value = language; }

        bool IsValid() { return (m_Value.size() == 2); }
        std::wstring& Value() { return m_Value; }
        bool Is(std::wstring lang)
        {
            return lang == m_Value;
        }

        void Visit(IVisitable& visitable) override
        {
            visitable.Accept(*this);
        }

    private:
        std::wstring m_Value;
    };
}

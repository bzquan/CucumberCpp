#pragma once

#include <string>

namespace GherkinAst
{
    class IHasDescription
    {
    public:
        IHasDescription(){}
        IHasDescription(std::wstring keyword, std::wstring* pTitle, std::wstring* pDesc) : 
            m_Keyword(keyword)
        {
            if (pTitle != nullptr) m_Title = *pTitle;
            if (pDesc != nullptr) m_Description = *pDesc;

            delete pTitle;
            delete pDesc;
        }
        virtual ~IHasDescription() {}

        virtual std::wstring& Keyword() { return m_Keyword; }
        virtual std::wstring& Title() { return m_Title; }
        virtual std::wstring& Description() { return m_Description; }

    private:
        std::wstring  m_Keyword;
        std::wstring  m_Title;
        std::wstring  m_Description;
    };
}
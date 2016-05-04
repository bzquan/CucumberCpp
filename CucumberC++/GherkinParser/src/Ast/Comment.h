#pragma once

#include <string>
#include "IHasLocation.h"

namespace GherkinAst
{
    class Comment : public IHasLocation
    {
    public:
        Comment(){}
        Comment(int lineNo, std::wstring text) :
            IHasLocation(lineNo), m_Text(text){}

        std::wstring& Text() { return m_Text; }

    private:
        std::wstring m_Text;
    };
}

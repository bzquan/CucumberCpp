#pragma once

#include <string>
#include "StepArgument.h"
#include "IHasLocation.h"

namespace GherkinAst
{
    class DocString : public StepArgument, public IHasLocation
    {
    public:
        DocString(int lineNo, std::wstring contentType, std::wstring content) :
            IHasLocation(lineNo),
            m_ContentType(contentType),
            m_Content(content)
        {
        }

        StepArgument* copy() const override
        {
            return new DocString(*this);
        }

        std::wstring& ContentType() { return m_ContentType; }
        std::wstring& Content() { return m_Content; }

        void Visit(IVisitable& visitable) override
        {
            visitable.Accept(*this);
        }

    private:
        std::wstring m_ContentType;
        std::wstring m_Content;
    };
}
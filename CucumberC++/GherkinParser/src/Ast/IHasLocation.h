#pragma once

#include "Location.h"

namespace GherkinAst
{
    class IHasLocation
    {
    public:
        IHasLocation(int lineNo = 1) : m_Location(lineNo){}
        virtual ~IHasLocation() {}
        virtual GherkinAst::Location& Location() { return m_Location; }
        void Location(int lineNo) { m_Location = GherkinAst::Location(lineNo); }

    private:
        GherkinAst::Location m_Location;
    };
}
#pragma once

#include <string>
#include "Location.h"
#include "IHasLocation.h"
#include "IVisit.h"

namespace GherkinAst
{
    class Tag : public IHasLocation
    {
    public:
        Tag() {}
        Tag(GherkinAst::Location location, std::wstring name) :
            m_Location(location), m_Name(name)
        {
        }

        GherkinAst::Location& Location() override { return m_Location; }
        std::wstring& Name() { return m_Name; }

        bool IsGUID();
        static Tag CreateNextGUIDTag(GherkinAst::Location location);

    private:
        GherkinAst::Location m_Location;
        std::wstring m_Name;
    };
}
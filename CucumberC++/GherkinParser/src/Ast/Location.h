#pragma once

namespace GherkinAst
{
    class Location
    {
    public:
        Location(int line = 1) : m_LineNo(line){}

        int Line() { return m_LineNo; }

    private:
        int m_LineNo;
    };
}
#pragma once

#include <string>
#include "TableCell.h"
#include "Location.h"

class PrettyTableCell
{
public:
    PrettyTableCell(GherkinAst::TableCell& cell) : m_Cell(cell)
    {
        m_TrimmedValueWidth = GetCellWidth(cell.TrimmedValue());
        m_OriginalValueWidth = GetCellWidth(cell.Value());
    }

    std::wstring TrimmedValue(int preferedWidth);
    int TrimmedValueWidth() { return m_TrimmedValueWidth; }

    std::wstring OriginalValue(int preferedWidth);
    int OriginalValueWidth() { return m_OriginalValueWidth; }

private:
    static int GetCellWidth(std::wstring& value);

private:
    GherkinAst::TableCell& m_Cell;
    int m_TrimmedValueWidth  = 0;
    int m_OriginalValueWidth = 0;
};


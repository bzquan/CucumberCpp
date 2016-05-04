#pragma once

#include <vector>
#include "TableCell.h"
#include "IHasLocation.h"

namespace GherkinAst
{
    class TableRow : public IHasLocation
    {
    public:
        TableRow(int lineNo, std::vector<TableCell> cells) :
            IHasLocation(lineNo),
            m_Cells(cells)
        {
        }

        std::vector<TableCell>& Cells() { return m_Cells; }
        TableCell& operator[](std::size_t idx) { return m_Cells[idx]; }

        std::wstring OriginalFormattedText;
        std::wstring TrimmedFormattedText;

    private:
        std::vector<TableCell> m_Cells;
    };
}

#pragma once

#include <vector>
#include "TableRow.h"

namespace GherkinAst
{
    class IHasRows
    {
    public:
        IHasRows(std::vector<TableRow> rows) : m_Rows(rows){}
        std::vector<TableRow>& Rows() { return m_Rows; }
        TableRow& operator[](std::size_t idx) { return m_Rows[idx]; }

    private:
        std::vector<TableRow> m_Rows;
    };
}
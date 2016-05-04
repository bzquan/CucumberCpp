#pragma once

#include <string>
#include "DataTable.h"

namespace GherkinAst
{
    class TableRow;
}

namespace CucumberCpp
{
    class BDDGherkinTableBuilder
    {
    public:
        std::wstring Build(GherkinAst::DataTable& dataTable, int tableSeqNo = -1, std::wstring indent = L"");

    private:
        void AppendGherkinTableDefinition();
        void AppendGherkinTableBody(GherkinAst::DataTable& dataTable);
        void AppendTableVariable();
        void AppendGherkinTableHeader(GherkinAst::TableRow& row);
        void AppendGherkinTableRows(GherkinAst::DataTable& dataTable);
        std::wstring EndingOfRow(bool is_last_row);

    private:
        std::wstring m_tableBuilder;
        std::wstring m_tableSeqNo;
        std::wstring m_indent;
    };
}

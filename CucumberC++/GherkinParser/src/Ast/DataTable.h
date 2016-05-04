#pragma once

#include <vector>
#include "StepArgument.h"
#include "IHasRows.h"
#include "IVisitable.h"

namespace GherkinAst
{
    class DataTable : public StepArgument, public IHasRows
    {
    public:
        DataTable(std::vector<TableRow> rows) : IHasRows(rows)
        {
        }

        StepArgument* copy() const override
        {
            return new DataTable(*this);
        }

        void Visit(IVisitable& visitable) override
        {
            visitable.Accept(*this);
        }
    };
}
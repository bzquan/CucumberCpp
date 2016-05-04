#pragma once

#include <string>
#include "AstBuilder.h"
#include "gherkin.tab.hpp"

class ParsingState
{
public:
    ParsingState() = default;

    static ParsingState* Start();
    ParsingState* tokenScanned(yytokentype lastToken)
    {
        ParsingState* pState = nextState(lastToken);
        pState->m_LastToken = lastToken;
        return pState;
    }
    virtual std::wstring expectation() = 0;

protected:
    virtual ~ParsingState() {}
    virtual ParsingState* nextState(yytokentype lastToken) = 0;
    inline yytokentype LastToken() { return m_LastToken; }

private:
    yytokentype m_LastToken = INITIAL;
};


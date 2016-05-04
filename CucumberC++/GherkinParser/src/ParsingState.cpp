#include "ParsingState.h"

class Initial : public ParsingState
{
public:
    ParsingState* nextState(yytokentype lastToken) override;
    std::wstring expectation() override
    {
        switch (LastToken())
        {
        case INITIAL:
        case LANGUAGE:
            return L"Expect language, tags or feature.";
        default:
            return L"Expect feature.";
        }
    }
};

class FeatureParsed : public ParsingState
{
public:
    ParsingState* nextState(yytokentype lastToken) override;
    std::wstring expectation() override
    {
        switch (LastToken())
        {
        case TAG_LINE:
            return L"Expect scenario or scenario outline.";
        case DECRIPTION:
            return L"Expect background, scenario or scenario outline.";
        default:
            return L"Expect feature description, background, scenario or scenario outline.";
            break;
        }
    }
};

class ParsingBackground : public ParsingState
{
public:
    ParsingState* nextState(yytokentype lastToken) override;
    std::wstring expectation() override
    {
        switch (LastToken())
        {
        case DECRIPTION:
            return L"Expect background steps.";
        default:
            return L"Expect steps, scenario or scenario outline.";
        }
    }
};

class ParsingScenario : public ParsingState
{
public:
    ParsingState* nextState(yytokentype lastToken) override;
    std::wstring expectation() override
    {
        switch (LastToken())
        {
        case DECRIPTION:
            return L"Expect scenario steps.";
        case EXAMPLE_LINE:
        case TABLE_ROW:
            return L"Examples should only be used for scenario outline.";
        default:
            return L"Expect scenario description or steps.";
        }
    }
};

class ParsingScenarioOutline : public ParsingState
{
public:
    ParsingState* nextState(yytokentype lastToken) override;
    std::wstring expectation() override
    {
        switch (LastToken())
        {
        case DECRIPTION:
            return L"Expect scenario outline steps.";
        case EXAMPLE_LINE:
            return L"Expect example table.";
        case TABLE_ROW:
            return L"Expect new examples or scenario.";
        default:
            return L"Expect scenario outline description or steps.";
        }
    }
};

class ParsingExamples : public ParsingState
{
public:
    ParsingState* nextState(yytokentype lastToken) override;
    std::wstring expectation() override
    {
        switch (LastToken())
        {
        case TABLE_ROW:
            return L"Expect new examples or scenario.";
        default:
            return L"Expect example table.";
        }
    }
};

namespace
{
    Initial g_Initial;
    FeatureParsed g_FeatureParsed;
    ParsingBackground g_ParsingBackground;
    ParsingScenario g_ParsingScenario;
    ParsingScenarioOutline g_ParsingScenarioOutline;
    ParsingExamples g_ParsingExamples;
}

ParsingState* ParsingState::Start()
{
    return &g_Initial;
}

ParsingState* Initial::nextState(yytokentype lastToken)
{
    if (lastToken == FEATURE_LINE)
    {
        return &g_FeatureParsed;
    }
    return this;
}

ParsingState* FeatureParsed::nextState(yytokentype lastToken)
{
    switch (lastToken)
    {
    case BACKGROUND_LINE:
        return &g_ParsingBackground;
    case SCENARIO_LINE:
        return &g_ParsingScenario;
    case SCENARIO_OUTLINE_LINE:
        return &g_ParsingScenarioOutline;
    default:
        return this;
    }
}

ParsingState* ParsingBackground::nextState(yytokentype lastToken)
{
    switch (lastToken)
    {
    case SCENARIO_LINE:
        return &g_ParsingScenario;
    case SCENARIO_OUTLINE_LINE:
        return &g_ParsingScenarioOutline;
    default:
        return this;
    }
}

ParsingState* ParsingScenario::nextState(yytokentype lastToken)
{
    switch (lastToken)
    {
    case SCENARIO_OUTLINE_LINE:
        return &g_ParsingScenarioOutline;
    default:
        return this;
    }
}

ParsingState* ParsingScenarioOutline::nextState(yytokentype lastToken)
{
    switch (lastToken)
    {
    case SCENARIO_LINE:
        return &g_ParsingScenario;
    case EXAMPLE_LINE:
        return &g_ParsingExamples;
    default:
        return this;
    }
}

ParsingState* ParsingExamples::nextState(yytokentype lastToken)
{
    switch (lastToken)
    {
    case SCENARIO_LINE:
        return &g_ParsingScenario;
    case SCENARIO_OUTLINE_LINE:
        return &g_ParsingScenarioOutline;
    default:
        return this;
    }
}

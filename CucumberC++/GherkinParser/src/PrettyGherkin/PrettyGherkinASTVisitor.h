#pragma once

#include "Definitions.h"
#include "IVisitable.h"

class PrettyGherkin;

class PrettyGherkinASTVisitor : public GherkinAst::IVisitable
{
public:
    PrettyGherkinASTVisitor(PrettyGherkin& prettyGherkin);

    void Format();
    void Accept(GherkinAst::Language& language) override;
    void Accept(std::vector<GherkinAst::Tag>& tags) override;
    void Accept(GherkinAst::Feature& feature) override;
    void Accept(GherkinAst::Background& background) override;
    void AcceptSenarioTags(std::vector<GherkinAst::Tag>& tags) override;
    void Accept(GherkinAst::Scenario& scenario) override;
    void Accept(GherkinAst::ScenarioOutline& scenarioOutline) override;
    void Accept(GherkinAst::Step& step) override;
    void Accept(GherkinAst::DocString& docString) override;
    void Accept(GherkinAst::Example& example) override;
    void Accept(GherkinAst::DataTable& dataTable) override;

private:
    void FormatKeywordWithDescription(GherkinAst::IHasDescription& hasDescription, GherkinAst::Location& location);
    void MakePretty(GherkinAst::ScenarioDefinition& scenarioDefinition);

private:
    PrettyGherkin&       m_pPrettyGherkin;
    GherkinAst::Feature* m_pFeature;
};

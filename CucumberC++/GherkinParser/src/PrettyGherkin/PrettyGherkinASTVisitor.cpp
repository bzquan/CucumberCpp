#include "Feature.h"
#include "IHasDescription.h"
#include "IHasLocation.h"
#include "Scenario.h"
#include "ScenarioOutline.h"
#include "DocString.h"
#include "StrUtility.h"
#include "Example.h"
#include "PrettyDataTable.h"
#include "PrettyGherkin.h"
#include "PrettyGherkinDef.h"
#include "PrettyGherkinASTVisitor.h"

using namespace std;
using namespace GherkinAst;

PrettyGherkinASTVisitor::PrettyGherkinASTVisitor(PrettyGherkin& prettyGherkin) :
    m_pPrettyGherkin(prettyGherkin),
    m_pFeature(prettyGherkin.GetFeature())
{
}

void PrettyGherkinASTVisitor::Format()
{
    m_pFeature->Visit(*this);
}

void PrettyGherkinASTVisitor::Accept(Language& language)
{
    m_pPrettyGherkin.AppendOriginalComment(m_pFeature->Location().Line());
    m_pPrettyGherkin
        .append(LANGUAGE_KEYWORD)
        .append(SPACE)
        .append(language.Value())
        .appendLine();
}

void PrettyGherkinASTVisitor::Accept(vector<Tag>& tags)
{
    if (tags.size() == 0) return;

    for (size_t i = 0; i < tags.size(); i++)
    {
        Tag& tag = tags[i];
        const bool is_first_tag = (i == 0);
        if (is_first_tag)
        {
            m_pPrettyGherkin.AppendOriginalComment(tag.Location().Line());
        }

        if (!is_first_tag && tag.IsGUID())
        {
            m_pPrettyGherkin.appendLine();
        }
        else
        {
            // append a space between tags
            const size_t last = tags.size() - 1;
            const bool have_next_non_guid_tag = ((i < tags.size() - 1) && !tags[i + 1].IsGUID());
            const bool is_last_tag = (i == last);
            if (!is_first_tag && (have_next_non_guid_tag || is_last_tag))
            {
                m_pPrettyGherkin.append(SPACE);
            }
        }
        m_pPrettyGherkin.append(tag.Name());
    }
    m_pPrettyGherkin.appendLine();
}

void PrettyGherkinASTVisitor::Accept(Feature& feature)
{
    FormatKeywordWithDescription(feature, feature.Location());
}

void PrettyGherkinASTVisitor::FormatKeywordWithDescription(IHasDescription& hasDescription, Location& location)
{
    m_pPrettyGherkin.AppendOriginalComment(location.Line());

    wstring spaceORempty;
    if (hasDescription.Title().length() > 0) spaceORempty.append(SPACE);

    m_pPrettyGherkin
        .append(hasDescription.Keyword())
        .append(COLON)
        .append(spaceORempty)
        .append(hasDescription.Title())
        .appendLine();
    if (hasDescription.Description().length() > 0)
    {
        m_pPrettyGherkin
            .append(hasDescription.Description())
            .appendLine();
    }
}

void PrettyGherkinASTVisitor::AcceptSenarioTags(vector<Tag>& tags)
{
    m_pPrettyGherkin.appendLine();
    Accept(tags);
}

void PrettyGherkinASTVisitor::Accept(Background& background)
{
    m_pPrettyGherkin.AppendOriginalComment(background.Location().Line());
    m_pPrettyGherkin.appendLine();
    FormatKeywordWithDescription(background, background.Location());
    m_pPrettyGherkin.appendLine();
}

void PrettyGherkinASTVisitor::Accept(Scenario& scenario)
{
    MakePretty((ScenarioDefinition&)scenario);
}

void PrettyGherkinASTVisitor::Accept(ScenarioOutline& scenarioOutline)
{
    MakePretty((ScenarioDefinition&)scenarioOutline);
}

void PrettyGherkinASTVisitor::MakePretty(ScenarioDefinition& scenarioDefinition)
{
    m_pPrettyGherkin.AppendOriginalComment(scenarioDefinition.Location().Line());
    FormatKeywordWithDescription(scenarioDefinition, scenarioDefinition.Location());
    m_pPrettyGherkin.appendLine();
}

void PrettyGherkinASTVisitor::Accept(Step& step)
{
    m_pPrettyGherkin.AppendOriginalComment(step.Location().Line());

    m_pPrettyGherkin
        .append(INDENT)
        .append(step.Keyword())
        .append(SPACE)
        .append(step.Text())
        .appendLine();
}

void PrettyGherkinASTVisitor::Accept(DocString& docString)
{
    m_pPrettyGherkin.AppendOriginalComment(docString.Location().Line());
    m_pPrettyGherkin
        .append(STEPARG_INDENT)
        .append(DOCSTRING_SEPARATOR);
    if (docString.ContentType().length() > 0)
        m_pPrettyGherkin.append(docString.ContentType());
    m_pPrettyGherkin.appendLine();

    vector<wstring> lines = StrUtility::Split(docString.Content(), L'\n');
    for (wstring& line : lines)
    {
        m_pPrettyGherkin
            .append(STEPARG_INDENT)
            .append(line)
            .appendLine();
    }

    m_pPrettyGherkin
        .append(STEPARG_INDENT)
        .append(DOCSTRING_SEPARATOR)
        .appendLine();
}

void PrettyGherkinASTVisitor::Accept(Example& example)
{
    m_pPrettyGherkin.AppendOriginalComment(example.Location().Line());

    m_pPrettyGherkin
        .appendLine()
        .append(INDENT);
    FormatKeywordWithDescription(example, example.Location());
    example.ExampleTable().Visit(*this);
}

void PrettyGherkinASTVisitor::Accept(DataTable& dataTable)
{
    PrettyDataTable prettyDataTable(dataTable);
    prettyDataTable.Format(m_pPrettyGherkin);
}

#include "IVisitable.h"
#include "StrUtility.h"
#include "ScenarioDefinition.h"

using namespace GherkinAst;

ScenarioDefinition::ScenarioDefinition(
    std::vector<GherkinAst::Tag>* pTags,
    int lineNo,
    std::wstring keyword, std::wstring* title, std::wstring* description,
    std::vector<GherkinAst::Step>* pStepSeq) :
    IHasTags(pTags),
    IHasLocation(lineNo),
    IHasDescription(keyword, title, description),
    IHasSteps(pStepSeq)
{
    AppendGUIDTag();
}


void ScenarioDefinition::Visit(IVisitable& visitable)
{
    visitable.AcceptSenarioTags(Tags());
    AcceptVisitable(visitable);

    for (Step& step : Steps())
    {
        step.Visit(visitable);
    }
}

bool ScenarioDefinition::HasGUIDTag()
{
    for (Tag& tag : IHasTags::Tags())
    {
        if (tag.IsGUID()) return true;
    }

    return false;
}

void ScenarioDefinition::AppendGUIDTag()
{
    std::vector<Tag>& tags = IHasTags::Tags();
    int index = -1;
    for (size_t i = 0; i < tags.size(); i++)
    {
        if (tags[i].IsGUID())
        {
            index = i;
            break;
        }
    }

    if (index >= 0)
    {
        // move GUID tag to the end of the list
        Tag guidTag = tags[index];
        tags.erase(tags.begin() + index);
        tags.push_back(guidTag);
    }
    else
    {
        tags.push_back(Tag::CreateNextGUIDTag(Location()));
    }
}

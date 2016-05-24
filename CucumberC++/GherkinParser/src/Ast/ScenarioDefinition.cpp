/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Bingzhe Quan
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

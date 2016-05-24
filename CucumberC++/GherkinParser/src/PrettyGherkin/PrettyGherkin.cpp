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

#include "Feature.h"
#include "Comment.h"
#include "PrettyGherkinDef.h"
#include "PrettyGherkin.h"

using namespace std;
using namespace GherkinAst;

PrettyGherkin::PrettyGherkin(Feature* pFeature) :
    m_pFeature(pFeature),
    m_Comments(pFeature->comments())
{
}

wstring PrettyGherkin::Format()
{
    m_GherkinASTVisitor.Format();
    return m_FormattedFeature;
}

PrettyGherkin& PrettyGherkin::append(const wchar_t* str)
{
    m_FormattedFeature.append(str);
    return *this;
}

PrettyGherkin& PrettyGherkin::append(std::wstring str)
{
    m_FormattedFeature.append(str);
    return *this;
}

PrettyGherkin& PrettyGherkin::appendLine()
{
    m_FormattedFeature.append(NEWLINE);
    return *this;
}

void PrettyGherkin::AppendOriginalComment(int currentLineNo)
{
    Comment* pComment = GetComment(m_noOfNextCommentToAppend);
    while ((pComment != nullptr) && (pComment->Location().Line() < currentLineNo))
    {
        m_FormattedFeature
            .append(pComment->Text())
            .append(NEWLINE);
        m_noOfNextCommentToAppend++;
        pComment = GetComment(m_noOfNextCommentToAppend);
    }
}

Comment* PrettyGherkin::GetComment(int index)
{
    return (index < (int)m_Comments.size()) ? &m_Comments[index] : nullptr;
}

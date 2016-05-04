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

#pragma once

#include <string>
#include "PrettyGherkinASTVisitor.h"

class PrettyGherkin
{
public:
    PrettyGherkin(GherkinAst::Feature* pFeature);
    GherkinAst::Feature* GetFeature() { return m_pFeature; }
    std::wstring Format();
    void AppendOriginalComment(int currentLineNo);

    // string related methods
    PrettyGherkin& append(const wchar_t* str);
    PrettyGherkin& append(std::wstring str);
    PrettyGherkin& appendLine();

private:
    GherkinAst::Comment* GetComment(int index);

private:
    GherkinAst::Feature*    m_pFeature          = nullptr;
    PrettyGherkinASTVisitor m_GherkinASTVisitor{*this};
    std::wstring            m_FormattedFeature;

    // for original comment management
    std::vector<GherkinAst::Comment>& m_Comments;
    int m_noOfNextCommentToAppend = 0;
};


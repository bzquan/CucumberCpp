#pragma once

#include <string>
#include <vector>
#include "Tag.h"
#include "Feature.h"
#include "YYTableParam.h"

//class GherkinAst::Comment;
//class GherkinAst::DocString;
//class GherkinAst::DataTable;

class AstBuilder
{
public:
    AstBuilder() = default;
    ~AstBuilder()
    {
        delete m_pFeature;
    }

    void BuildFeature(int lineNo, std::wstring* pLang, std::vector<GherkinAst::Tag>* pTags, std::wstring* pTitle, std::wstring* pDesc);

    GherkinAst::Feature* Feature() { return m_pFeature; }
    std::vector<GherkinAst::Tag>* createTags(const std::wstring& tag_line, int lineNo);
    void appendTags(const std::wstring& tag_line, int lineNo, std::vector<GherkinAst::Tag>* tags);
    void addComment(GherkinAst::Comment comment);
    std::vector<GherkinAst::Comment>& Comments() { return m_Comments; }

    GherkinAst::DocString* BuildStepDocString(int lineNo, DocStringParam* pDocStringParam);
    GherkinAst::DataTable* BuildDataTable(TableParam* pTableParam);

private:
    GherkinAst::DataTable* BuildDataTable(std::vector<RowParam>& rows);
    void MoveComment2Feature();

private:
    GherkinAst::Feature* m_pFeature = nullptr;
    std::vector<GherkinAst::Comment> m_Comments;
};

#include <iostream>
#include "Definitions.h"
#include "StrUtility.h"

#include "Comment.h"
#include "DocString.h"
#include "DataTable.h"
#include "AstBuilder.h"

using namespace GherkinAst;

void AstBuilder::BuildFeature(int lineNo, std::wstring* pLang, std::vector<GherkinAst::Tag>* pTags, std::wstring* pTitle, std::wstring* pDesc)
{
    m_pFeature = new GherkinAst::Feature(lineNo, pLang, pTags, pTitle, pDesc);
    MoveComment2Feature();
}

vector<GherkinAst::Tag>* AstBuilder::createTags(const wstring& tag_line, int lineNo)
{
    vector<GherkinAst::Tag>* pTags = new vector<GherkinAst::Tag>();

    vector<wstring> tags = StrUtility::Split(tag_line, L'@');
    for (wstring tag : tags)
    {
        if (tag.length() > 0)
        {
            wstring trimmedTag(L"@");
            trimmedTag.append(StrUtility::Trim(tag));
            pTags->push_back(GherkinAst::Tag(GherkinAst::Location(lineNo), trimmedTag));
        }
    }

    return pTags;
}

void AstBuilder::appendTags(const std::wstring& tag_line, int lineNo, std::vector<GherkinAst::Tag>* pTags)
{
    if (pTags == nullptr) return;

    vector<GherkinAst::Tag>* pNewTags = createTags(tag_line, lineNo);
    pTags->insert(pTags->end(), pNewTags->begin(), pNewTags->end());
    delete pNewTags;
}

void AstBuilder::addComment(GherkinAst::Comment comment)
{
    if (m_pFeature != nullptr)
    {
        m_pFeature->addComment(comment);
    }
    else
    {
        m_Comments.push_back(comment);
    }
}

void AstBuilder::MoveComment2Feature()
{
    if (m_pFeature == nullptr) return;
    for (Comment& comment : m_Comments)
    {
        m_pFeature->addComment(comment);
    }

    m_Comments.clear();
}


GherkinAst::DocString* AstBuilder::BuildStepDocString(int lineNo, DocStringParam* pDocStringParam)
{
    if (pDocStringParam == nullptr) return nullptr;

    GherkinAst::DocString* pDocString = new DocString(lineNo, pDocStringParam->contentType, pDocStringParam->content);
    delete pDocStringParam;

    return pDocString;
}

GherkinAst::DataTable* AstBuilder::BuildDataTable(TableParam* pTableParam)
{
    if (pTableParam == nullptr) return nullptr;

    GherkinAst::DataTable* pArg = nullptr;

    try {
        pArg = BuildDataTable(pTableParam->rowParams);
        delete pTableParam;
    }
    catch (GherkinError&)
    {
        delete pTableParam;
        throw;
    }

    return pArg;
}

GherkinAst::DataTable* AstBuilder::BuildDataTable(std::vector<RowParam>& rows)
{
    std::vector<TableRow> tableRows;
    int columnCount = -1;
    for (RowParam& row : rows)
    {
        vector<wstring> cellsText = StrUtility::Split(row.text, L'|');
        cellsText.erase(cellsText.begin()); // the 1st text, which is empty, is not part of table. e.g. for "|1|2|"
        if (columnCount < 0)
        {
            columnCount = cellsText.size();
        }
        if ((int)cellsText.size() != columnCount) {
            std::wstring msg = (int)cellsText.size() > columnCount ? L"Too many columns!" : L"Too few columns!";
            throw GherkinError(row.lineNo, msg);
        }
        std::vector<TableCell> tableCells;
        for (wstring& str : cellsText)
        {
            tableCells.push_back(TableCell(StrUtility::Trim(str)));
        }
        TableRow astTableRow(row.lineNo, tableCells);
        astTableRow.OriginalFormattedText = row.text;   // set original row text
        astTableRow.TrimmedFormattedText = row.text;    // set row text without pretty formatting
        tableRows.push_back(astTableRow);
    }

    return new DataTable(tableRows);
}


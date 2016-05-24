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

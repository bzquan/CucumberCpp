#pragma once

#include <string>
#include <vector>

struct RowParam
{
    RowParam() : lineNo(1) {}
    RowParam(int line, std::wstring* str) :
        lineNo(line), text(*str)
    {
        delete str;
    }

    int lineNo;
    std::wstring text;
};

struct TableParam
{
    void addParam(int lineNo, std::wstring* str)
    {
        rowParams.push_back(RowParam(lineNo, str));
    }
    std::vector<RowParam> rowParams;
};

struct DocStringParam
{
    DocStringParam(const std::wstring& str, const std::wstring& type) :
        content(str), contentType(type){}
    std::wstring content;
    std::wstring contentType;
};
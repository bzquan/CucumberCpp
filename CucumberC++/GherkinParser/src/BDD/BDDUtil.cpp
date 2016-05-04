#include <regex>
#include <fstream>
#include <locale>
#ifdef WIN32
#include <codecvt>
#endif
#include <exception>
#include <algorithm>
#include "StrUtility.h"
#include "BDDUtil.h"

//#define QT
//#ifdef QT
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
//#endif

using namespace std;
using namespace CucumberCpp;

wstring BDDUtil::INDENT = L"    ";
wstring BDDUtil::INDENT_DOUBLE = INDENT + INDENT;
wstring BDDUtil::INDENT_DOUBLE_PLUS = INDENT + INDENT + L"  ";
wstring BDDUtil::INDENT_TRIPLE = INDENT_DOUBLE + INDENT;
wstring BDDUtil::INDENT_TABLE_HEADER = L"//      ";
wstring BDDUtil::ParameterClassName = L"GherkinRow";
wstring BDDUtil::NEW_LINE = L"\n";
wchar_t BDDUtil::NEW_LINE_CHAR = L'\n';
wstring BDDUtil::TEST_METHOD_BODY =
                    NEW_LINE +
                    INDENT + L"// Given" + NEW_LINE +
                    NEW_LINE +
                    INDENT + L"// When" + NEW_LINE +
                    NEW_LINE +
                    INDENT + L"// Then" + NEW_LINE +
                    NEW_LINE +
                    INDENT + L"FAIL();" + NEW_LINE +
                    L"}" + NEW_LINE;

wstring BDDUtil::FloatRegex = LR"(([-+]?\d[\d,]*\.?\d*))";
wstring BDDUtil::StringRegex = LR"(("[^"]*"))";
wstring BDDUtil::RowParamRegex = LR"((<[^>]+>))";

wstring BDDUtil::StepPattern{ StringRegex + L"|" + FloatRegex + L"|" + RowParamRegex };

bool BDDUtil::s_supportUnicode = false;

wstring BDDUtil::ReplaceWhiteSpaceWithUnderBar(const wstring& str)
{
    wregex reg(L"\\s+");
    return regex_replace(str, reg, L"_");
}

wstring BDDUtil::RemoveAllWhiteSpaces(const wstring& str)
{
    wregex reg(L"\\s+");
    return regex_replace(str, reg, L"");
}

wstring BDDUtil::TrimWhiteSpaces(const wstring& str)
{
    return StrUtility::Trim(str);
}

wstring BDDUtil::MakeIdentifier(const std::wstring& str)
{
    wstring ident;
    std::locale loc("");

    for (wchar_t ch : str)
    {
        if ((ch == L' ') || (ch == L'\t'))
            ident.append(1, L'_');
        else if (isalnum(ch, loc) || (ch == L'_'))
            ident.append(1, ch);
    }

    return ident;
}

wstring BDDUtil::ToTitleCase(const std::wstring& str)
{
    wstring ident;

    for (size_t i = 0; i < str.length(); i++)
    {
        wchar_t ch = str[i];
        bool is_previous_char_white_space = (i == 0) || (str[i - 1] == L' ') || (str[i - 1] == L'\t');
        if (iswalpha(ch) && is_previous_char_white_space)
            ident.append(1, towupper(ch));
        else
            ident.append(1, ch);
    }

    return MakeIdentifier(ident);
}

wstring BDDUtil::ToLowerCaseWithUnderBar(const std::wstring& str)
{
    wstring ident(str);
    auto easytolower = [](wchar_t ch) { return (ch >= L'A' && ch <= L'Z') ? ch - (L'Z' - L'z') : ch; };
    std::transform(ident.begin(), ident.end(), ident.begin(), easytolower);
    return MakeIdentifier(ident);
}

wstring BDDUtil::ToCPPwstringLiteral(const std::wstring& str)
{
    if (str.length() == 0) return L"L\"\"";

    wstring text(str);
    // take out beginning double quotation(" or L")
    if (text[0] == L'"')
        text.erase(0, (size_t)1);
    else if ((text.length() >= 2) && (text[0] == L'L') && (text[1] == L'"'))
        text.erase(0, (size_t)2);

    // take out ending double quotation(")
    if ((text.length() > 0) && (text[text.length() - 1] == L'"'))
        text.erase(text.length() - 1, (size_t)1); // erase last double quotation

    // replace all double quotation to \"\"
    StrUtility::ReplaceAll(text, L"\"", L"\"\"");

    // compose C++ wstring literal
    wstring str_literal(L"L\"");
    str_literal
        .append(text)
        .append(1, L'"');

    return str_literal;
}

// exception : BadFileException if failure
void BDDUtil::WriteFileAsUTF8WithBOM(std::wstring filepath, std::wstring contents)
{
#ifdef WIN32
    WriteFileAsUTF8WithBOMWin32(filepath, contents);
#else    // Qt
    WriteFileAsUTF8WithBOMQt(filepath, contents);
#endif
}

void BDDUtil::WriteFileAsUTF8WithBOMWin32(std::wstring filepath, std::wstring contents)
{
    // 1 BOM : Open file in ANSI mode and add BOM to the start of a file
    std::ofstream fs;
    fs.open(filepath, std::ios::out | std::ios::binary);
    if (fs.bad()) {
        throw BadFileException(filepath);
    }

    const size_t SZIE_OF_BOM = 3;
    unsigned char smarker[SZIE_OF_BOM]{ 0xEF, 0xBB, 0xBF };
    fs.write((char*)smarker, SZIE_OF_BOM);
    fs.close();

    // 2 append contents
    std::wofstream file;
    file.open(filepath, std::ios::out | std::ios::app);
    if (file.bad()) {
        throw BadFileException(filepath);
    }
    file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    file << contents;
    file.close();
}

void BDDUtil::WriteFileAsUTF8WithBOMQt(std::wstring filepath, std::wstring contents)
{
    QString q_filepath = QString::fromStdWString(filepath);
    QFile file(q_filepath);
    bool success = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!success) {
        throw BadFileException(filepath);
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out.setGenerateByteOrderMark(true);
    QString text = QString::fromStdWString(contents);
    out << text;
    file.close();
}

wstring BDDUtil::to_wstring(wchar_t ch)
{
    wstring str;
    if (ch < 128)
    {
        str.push_back((char)ch);
    }
    else
    {
        str.push_back(L'u');
        str.append(std::to_wstring((long)ch));
        str.append(L"uu");
    }
    return str;
}

wstring BDDUtil::to_ident(wstring name)
{
    if (s_supportUnicode) return name;

    // change wide character to unicode if unicode is not supported
    wstring ident;
    for (wchar_t ch : name)
    {
        ident.append(to_wstring(ch));
    }

    return ident;
}

wstring BDDUtil::to_symbol(wstring ident)
{
    wstring name;
    wregex exp{L"(u[\\d]{3,}uu)"};
    std::wsmatch match;
    wstring text{ident};
    bool have_unicode_text = false;
    while (std::regex_search (text, match, exp))
    {
        have_unicode_text = true;
        wstring pre = match.prefix().str();
        wstring unicode_text = match[0];
        name.append(pre);
        StrUtility::ReplaceAll(unicode_text, L"u", L"");
        long value = std::stol(unicode_text);
        name.push_back((wchar_t)value);
        text = match.suffix().str();
    }

    if (have_unicode_text)
    {
        wstring symbol_text = name + text;  // note: "text" is last suffix text
        return symbol_text;
    }
    else
    {
        // return original ident if no unicode texted included
        return ident;
    }
}

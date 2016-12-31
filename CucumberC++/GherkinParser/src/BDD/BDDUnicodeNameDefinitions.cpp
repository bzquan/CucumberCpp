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

#include <algorithm>
#include "BDDUtil.h"
#include "BDDUnicodeNameDefinitions.h"

using namespace CucumberCpp;

BDDUnicodeName::BDDUnicodeName(std::wstring name, std::wstring unicodedName):
    m_Name(name),
    m_UnicodedName(unicodedName)
{
}

std::wstring BDDUnicodeName::NameDefine()
{
    std::wstring str;
    str.append(L"#define ")
       .append(m_Name)
       .append(L" ")
       .append(m_UnicodedName);

    return str;
}

void BDDUnicodeNameDefinitions::Clear()
{
    m_NameDefinitions.clear();
}

void BDDUnicodeNameDefinitions::Append(std::wstring name)
{
    if (!IsNewName(name)) return;

    std::wstring unicodedName = BDDUtil::to_ident(name);
    if (name != unicodedName)
    {
        m_NameDefinitions.push_back(BDDUnicodeName(name, unicodedName));
    }
}

bool BDDUnicodeNameDefinitions::IsNewName(std::wstring name)
{
    auto iter = std::find_if(m_NameDefinitions.begin(), m_NameDefinitions.end(), [&name](BDDUnicodeName& x){ return x.IsSame(name); });
    return (iter == m_NameDefinitions.end());
}

std::wstring BDDUnicodeNameDefinitions::GetDefines()
{
    if (m_NameDefinitions.size() == 0) return L"";

    std::wstring defines{BDDUtil::NEW_LINE};
    for (BDDUnicodeName& name : m_NameDefinitions)
    {
        defines
           .append(name.NameDefine())
           .append(BDDUtil::NEW_LINE);
    }

    defines.append(BDDUtil::NEW_LINE);

    return defines;
}

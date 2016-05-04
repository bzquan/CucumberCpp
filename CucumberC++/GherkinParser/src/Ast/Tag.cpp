#include <string>
#include "StrUtility.h"
#include "Tag.h"

using namespace std;
using namespace GherkinAst;

namespace
{
    const wstring GUID_TAG_PREFIX{ L"@guid-" };
}

bool Tag::IsGUID()
{
    return m_Name.find(GUID_TAG_PREFIX) == 0;
}

Tag Tag::CreateNextGUIDTag(GherkinAst::Location location)
{
    wstring guid(GUID_TAG_PREFIX);
    guid.append(StrUtility::NewGuid());
    // Guid guidValue = Guid.NewGuid();
    // Location of GUID is the same as scenario
    return Tag(location, guid);
}

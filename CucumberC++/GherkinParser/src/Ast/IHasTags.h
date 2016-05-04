#pragma once

#include <vector>
#include "Tag.h"

namespace GherkinAst
{
    class IHasTags
    {
    public:
        IHasTags(std::vector<Tag>* pTags = nullptr)
        {
            Tags(pTags);
        }
        virtual ~IHasTags() {}

        void Tags(std::vector<Tag>* pTags)
        {
            if (pTags == nullptr) return;

            m_Tags = *pTags;
            delete pTags;
        }

        virtual std::vector<Tag>& Tags() { return m_Tags; }

    private:
        std::vector<Tag> m_Tags;
    };
}
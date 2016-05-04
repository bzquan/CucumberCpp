#pragma once

#include <vector>

namespace GherkinAst
{
    class Language;
    class Tag;
    class Feature;
    class Background;
    class Scenario;
    class ScenarioOutline;
    class Step;
    class Example;
    class DocString;
    class DataTable;

    class IVisitable
    {
    public:
        virtual ~IVisitable() {}
        virtual void Accept(Language& /*language*/) {}
        virtual void Accept(std::vector<Tag>& /*tags*/) {}
        virtual void Accept(Feature& /*feature*/) {}
        virtual void Accept(Background& /*background*/) {}
        virtual void AcceptSenarioTags(std::vector<Tag>& /*tags*/) {}
        virtual void Accept(Scenario& /*scenario*/) {}
        virtual void Accept(ScenarioOutline& /*scenarioOutline*/) {}
        virtual void Accept(Step& /*step*/) {}
        virtual void Accept(Example& /*examples*/) {}
        virtual void Accept(DocString& /*docString*/) {}
        virtual void Accept(DataTable& /*dataTable*/) {}
    };
}

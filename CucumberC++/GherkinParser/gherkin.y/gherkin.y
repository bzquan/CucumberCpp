%{
#include <iostream>
#include <string>
#include <vector>

#include "Definitions.h"
#include "Language.h"
#include "Tag.h"
#include "Step.h"
#include "DocString.h"
#include "DataTable.h"
#include "Example.h"
#include "AstBuilder.h"
#include "GherkinParser.h"
#include "YYTableParam.h"

using namespace std;
using namespace GherkinAst;

int yylex(void);
void yyerror(char const*);

// g_pAstBuilder is provided by GherkinParser
extern GherkinParser* g_pParser;
extern AstBuilder* g_pAstBuilder;

Feature* CurrentFeature() { return g_pAstBuilder->Feature(); }

%}

%token INITIAL
%token <pwstr> LANGUAGE
%token <pwstr> TAG_LINE
%token <pwstr> FEATURE_LINE
%token <pwstr> BACKGROUND_LINE
%token <pwstr> SCENARIO_LINE
%token <pwstr> SCENARIO_OUTLINE_LINE
%token <pwstr> EXAMPLE_LINE
%token <pwstr> DECRIPTION
%token <pwstr> GIVEN_STEP
%token <pwstr> WHEN_STEP
%token <pwstr> THEN_STEP
%token <pwstr> AND_STEP
%token <pwstr> BUT_STEP
%token <pDocStringParam> DOC_STRING
%token <pwstr> TABLE_ROW
%token YYEOF_TOKEN

%type <pTags> Tags
%type <pwstr> LanguageTag
%type <pwstr> Description
%type <pStep> Step
%type <pStepSeq> StepSeq
%type <pStepArgument> StepParam
%type <pTableParam> TableRows
%type <pExample> Example
%type <pExamples> ExampleList

// using GLR parser
//%glr-parser

//%expect 0		  // no shift/reduce
//%expect-rr 0  // no reduce/reduce

%destructor { delete $$; } <pwstr>
%destructor { delete $$; } <pLanguage>
%destructor { delete $$; } <pStep>
%destructor { delete $$; } <pStepSeq>
%destructor { delete $$; } <pTags>
%destructor { delete $$; } <pTableParam>
%destructor { delete $$; } <pDocStringParam>
%destructor { delete $$; } <pExample>
%destructor { delete $$; } <pStepArgument>
%destructor {
               for (GherkinAst::Example* example : *$$)
               { delete example; }
               delete $$;
            } <pExamples>

%union
{
  std::wstring*  pwstr;
  GherkinAst::Language* pLanguage;
  GherkinAst::Step* pStep;
  std::vector<GherkinAst::Step>* pStepSeq;
  std::vector<GherkinAst::Tag>* pTags;
  TableParam* pTableParam;
  GherkinAst::StepArgument* pStepArgument;
  std::vector<GherkinAst::Example*>* pExamples;
  GherkinAst::Example* pExample;
  DocStringParam* pDocStringParam;
};

%%
Feature : Feature_Header Background Scenario_Definition

Feature_Header : LanguageTag Tags FEATURE_LINE Description
       {
          g_pAstBuilder->BuildFeature(@3.first_line, $1, $2, $3, $4);
       }

LanguageTag : /*empty*/
       { $$ = nullptr; }
     | LANGUAGE
       { $$ = $1; }
     ;
Tags : /*empty*/
  		 {
         $$ = new vector<GherkinAst::Tag>();
       }
     | Tags TAG_LINE
		   {
         $$ = $1;
         g_pAstBuilder->appendTags(*$2, yylloc.first_line, $$);
         delete $2;
       }
     ;

Description : /*empty*/
       { $$ = nullptr; }
     | DECRIPTION
       { $$ = $1; }
     ;

Background : /*empty*/
     | BACKGROUND_LINE Description StepSeq
       {
          try {
            Feature* feature = CurrentFeature();
            feature->Background(@1.first_line, $1, $2, $3);
          }
          catch (GherkinError& ex) {
            for (GherkinErrorInfo& err : ex.AllErrors())
               g_pParser->addError(err.LineNo, err.ErrorMsg);
          }
       }
     ;

Scenario_Definition : Scenario_List
Scenario_List : Basic_Scenario
     | Scenario_List Basic_Scenario
     ;
Basic_Scenario : Scenario
     | ScenarioOutline
     ;

Scenario: Tags SCENARIO_LINE Description StepSeq
       {
          try {
            Feature* feature = CurrentFeature();
            feature->AddScenario($1, @2.first_line, $2, $3, $4);
          }
          catch (GherkinError& ex) {
            for (GherkinErrorInfo& err : ex.AllErrors())
               g_pParser->addError(err.LineNo, err.ErrorMsg);
          }
       }
     ;

StepSeq: Step
       {
          $$ = new vector<GherkinAst::Step>();
          $$->push_back(*$1);
          delete $1;
       }
     | StepSeq Step
       {
          $$ = $1;
          $$->push_back(*$2);
          delete $2;
       }
     ;

Step : GIVEN_STEP StepParam
       {
          $$ = new GherkinAst::Step(StepKind::GIVEN_STEP, @1.first_line, $1, $2);
       }
     | WHEN_STEP StepParam
       {
          $$ = new GherkinAst::Step(StepKind::WHEN_STEP, @1.first_line, $1, $2);
       }
     | THEN_STEP StepParam
       {
          $$ = new GherkinAst::Step(StepKind::THEN_STEP, @1.first_line, $1, $2);
       }
     | AND_STEP StepParam
       {
          $$ = new GherkinAst::Step(StepKind::AND_STEP, @1.first_line, $1, $2);
       }
     | BUT_STEP StepParam
       {
          $$ = new GherkinAst::Step(StepKind::BUT_STEP, @1.first_line, $1, $2);
       }
     ;

StepParam: /*empty*/
       { $$ = nullptr; }
     | DOC_STRING
       {
         $$ = g_pAstBuilder->BuildStepDocString(@1.first_line, $1);
       }
     | TableRows
       {
         try {
           $$ = g_pAstBuilder->BuildDataTable($1);
         }
         catch (GherkinError& ex) {
           $$ = nullptr;
           for (GherkinErrorInfo& err : ex.AllErrors())
              g_pParser->addError(err.LineNo, err.ErrorMsg);
         }
       }
     ;

TableRows: TABLE_ROW
       {
          $$ = new TableParam();
          $$->addParam(@1.first_line, $1);
       }
     | TableRows TABLE_ROW
       {
          $$ = $1;
          $$->addParam(@2.first_line, $2);
       }
     ;

ScenarioOutline: Tags SCENARIO_OUTLINE_LINE Description StepSeq ExampleList
       {
          Feature* feature = CurrentFeature();
          feature->AddScenarioOutline($1, @2.first_line, $2, $3, $4, $5);
       }
     ;

ExampleList: Example
       {
          $$ = new vector<GherkinAst::Example*>();
          $$->push_back($1);
       }
     | ExampleList Example
       {
         $$ = $1;
         $$->push_back($2);
       }
     ;

Example: EXAMPLE_LINE TableRows
       {
         GherkinAst::DataTable* pTable = nullptr;
         try {
           pTable = g_pAstBuilder->BuildDataTable($2);
         }
         catch (GherkinError& ex) {
           for (GherkinErrorInfo& err : ex.AllErrors())
              g_pParser->addError(err.LineNo, err.ErrorMsg);
         }

         $$ = new GherkinAst::Example(@1.first_line, $1, pTable);
       }
     ;

%%


void yyerror(char const* /*msg*/)
{
    g_pParser->addSyntaxError();
}

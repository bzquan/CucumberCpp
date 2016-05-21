Feature: Pretty Gherkin
正しい構文のGherkinの整形処理を行う。
備考：整形後のGherkin文の比較ではGUIDを除く。

@guid-09204ed5-1af8-472c-8f3f-3b564c2a3aae
Scenario: GUIDなしのGherkin
  GUIDなしのFeatureについては、整形処理で各Scenarioに
  GUIDが新規付与される。

  Given 下記Gherkin文がある
    """
    Feature : 機能概要
    Scenario : title
    Given 前提条件
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
Feature: 機能概要

Scenario: title

  Given 前提条件
    """

@guid-25558861-e8c0-46df-bca2-2b5c524791be
Scenario: GUIDありのGherkin
  GUIDありのGherkin文を整形する。既存GUIDを保持する。

  Given 下記Gherkin文がある
    """
    Feature : 機能概要
    @guid-25558861-e8c0-46df-bca2-2b5c524791be
    Scenario : title
    Given 前提条件
    """
  When Gherkin文を整形する
  Then 整形後のGherkin文は下記である
    """
Feature: 機能概要

@guid-25558861-e8c0-46df-bca2-2b5c524791be
Scenario: title

  Given 前提条件
    """

@guid-d4f6d044-762b-4714-9aa4-f12935cf8ced
Scenario: FeatureのTag
  FeatureのTagは整形後も維持する。

  Given 下記Gherkin文がある
    """
    @tag1
    @tag2
    Feature : 機能概要
    Scenario : title
    Given 前提条件
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
@tag1 @tag2
Feature: 機能概要

Scenario: title

  Given 前提条件
    """

@guid-4e299a51-b12c-412c-bf38-8f54c60207cb
Scenario: FeatureのBackground
  BackgroundありのFeatureを整形する。

  Given 下記Gherkin文がある
    """
    Feature : feature title

    Background: background title
    Description of background
    Given precondition

    @guid-xxxxx
    Scenario : title
    When action
    """
  When Gherkin文を整形する
  Then 整形後のGherkin文は下記である
    """
Feature: feature title

Background: background title
    Description of background

  Given precondition

@guid-xxxxx
Scenario: title

  When action
    """

@guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558
Scenario: ScenarioのTagは最後尾に
  ScenarioのTagは整形後、最後尾に移動される。

  Given 下記Gherkin文がある
    """
    Feature : 機能概要
    @guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558
    @tag1
    Scenario : title
    Given 前提条件
    """
  When Gherkin文を整形する
  Then 整形後のGherkin文は下記である
    """
Feature: 機能概要

@tag1
@guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558
Scenario: title

  Given 前提条件
    """

@guid-dd9cce71-75cb-4375-84db-abf98ee5d1b3
Scenario: 複数のScenario
  複数のScenarioを整形する。

  Given 下記Gherkin文がある
    """
    Feature : feature title
    Background: background title
    Given precondition
    Scenario : title1
    Given precondition
    Scenario : title2
    Description of scenario2
    Given precondition
    When action
    Then expectation
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
Feature: feature title

Background: background title

  Given precondition

Scenario: title1

  Given precondition

Scenario: title2
    Description of scenario2

  Given precondition
  When action
  Then expectation
    """

@guid-6bb754fa-1838-4c87-8716-390f441dc0a1
Scenario: DocString argument
  DocString引数ありのStepを整形する。

  Given 下記Gherkin文がある
    """
    Feature : feature title
    Scenario : title
    Given precondition
    ^"""
    line1
    line2
    ^"""
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
Feature: feature title

Scenario: title

  Given precondition
^    """
    line1
    line2
^    """
    """

@guid-d0908cd3-0ac3-44c0-af91-161b306ac151
Scenario: Table argument
  Table引数ありのStepを整形する。

  Given 下記Gherkin文がある
    """
    Feature : feature title
    Scenario : title
    Given precondition
    |col1|col2|
    |v11|v12|
    |v21|v22|
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
Feature: feature title

Scenario: title

  Given precondition
    |col1|col2|
    |v11 |v12 |
    |v21 |v22 |
    """

@guid-adbfcca8-6ca6-4f78-8511-6032fa9f7473
Scenario: 規則性なしのTable argument
  Cell長さがばらばらのTable引数を整形する。

  Given 下記Gherkin文がある
    """
    Feature : feature title
    Scenario : title
    Given precondition
    |col1|col2|
    |v11abc|v12|
    |v21|v22abc|
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
Feature: feature title

Scenario: title

  Given precondition
    |col1  |col2  |
    |v11abc|v12   |
    |v21   |v22abc|
    """

@guid-2f7ad31c-346e-4fde-bf8e-c14b1b449580
Scenario: CommentありのGherkin
  CommentありのGherkin文を整形する。

  Given 下記Gherkin文がある
    """
    Feature : feature title
    Description of feature
    # comment1
    Scenario : title
    // comment2
    Given precondition
    |col1|col2|
    |v11|v12|
    |v21|v22|
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
Feature: feature title
    Description of feature
    # comment1

Scenario: title

    // comment2
  Given precondition
    |col1|col2|
    |v11 |v12 |
    |v21 |v22 |
    """

@guid-ed3062ed-df5c-4bd5-8740-c1bd7eae7386
Scenario: scenario outline
  scenario outlineを整形する。

  Given 下記Gherkin文がある
    """
    Feature : feature title
    Scenario Outline: title
    Description of scenario outline
    Given precondition
    Examples:
    |col1|col2|
    |v11|v12|
    |v21|v22|
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
Feature: feature title

Scenario Outline: title
    Description of scenario outline

  Given precondition

  Examples:
    |col1|col2|
    |v11 |v12 |
    |v21 |v22 |
    """

@guid-28675d82-8d7a-4e50-b87b-54835112e155
Scenario: scenario outline with multi examples
  scenario outlineを整形する。

  Given 下記Gherkin文がある
    """
    Feature : feature title
    Scenario Outline: title
    Given precondition
    Examples: example1
    |col1|col2|
    |v11|v12|
    |v21|v22|
    Examples: example2
    |col1|col2|
    |b11|b12|
    |b21|b22|
    """
  When Gherkin文を整形する
  Then 整形後のScenarioにGUIDが追加されること
  And 整形後のGherkin文は下記である
    """
Feature: feature title

Scenario Outline: title

  Given precondition

  Examples: example1
    |col1|col2|
    |v11 |v12 |
    |v21 |v22 |

  Examples: example2
    |col1|col2|
    |b11 |b12 |
    |b21 |b22 |
    """

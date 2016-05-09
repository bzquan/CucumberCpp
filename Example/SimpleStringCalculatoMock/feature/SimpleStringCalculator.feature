Feature: String calculator
     Client can get sum of numbers by inputting a string.

@guid-0e91e40c-a065-74a9-2ba1-0c3598fd6a1a
Scenario Outline: A separator can be +, comma or semicolon.
     A separator could be either +, comma or semicolon. But it is not allowed to combinate different separators.

  Given Enter <Numbers> with separator
  When Sum all the numbers
  Then The result <Sum> shall be informed[[mock]]

  Examples:
    |Numbers  |Sum|
    |1 + 2 + 3|6  |
    |4, 5, 6  |15 |
    |7; 8; 9  |24 |
    |1, 2; 3  |-1 |

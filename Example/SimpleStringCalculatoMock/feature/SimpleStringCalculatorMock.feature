Feature: String calculator using mock object
     Client can get sum of numbers by inputting a string.

@guid-08173785-8ecc-3427-5807-f4d184e28ae8
Scenario Outline: A separator can be +, comma or semicolon.
     A separator could be either +, comma or semicolon. But it is not allowed to combinate different separators.

  When Input <Numbers>
  Then The result <Sum> shall be informed[[mock]]

  Examples:
    |Numbers  |Sum|
    |1 + 2 + 3|6  |
    |4, 5, 6  |15 |
    |7; 8; 9  |24 |
    |1, 2; 3  |0  |

Feature: String calculator
Client can get sum of numbers by inputting a string.

@guid-084139ff-dda8-440c-9941-f20a18464473
Scenario Outline: A separator can be +, comma or semicolon
Separator could be either +, comma or semicolon. But it is not
allowed to combinate different separators.

  Given Enter <Numbers> with separator
  When Sum all the numbers
  Then The result should be <Sum>

  Examples:
    |Numbers  |Sum|
    |1 + 2 + 3|6  |
    |4, 5, 6  |15 |
    |7; 8; 9  |24 |
    |1, 2; 3  |0  |

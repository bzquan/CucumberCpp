#include "String_calculator_Steps.h"

// Enter <Numbers> with separator
void String_calculator_Steps::Enter_Numbers_with_separator(GherkinRow& row)
{
    model.Input(row[L"Numbers"].strValue());
}

// Sum all the numbers
void String_calculator_Steps::Sum_all_the_numbers()
{
    model.CalculateSum();
}

// The result <Sum> shall be informed[[mock]]
void String_calculator_Steps::The_result_Sum_shall_be_informedmock(GherkinRow& row)
{
    model.ExpectedSum(row[L"Sum"].intValue());
}



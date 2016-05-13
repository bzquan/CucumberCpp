#include "String_calculator_using_mock_object_Steps.h"

// Input <Numbers>
void String_calculator_using_mock_object_Steps::Input_Numbers(GherkinRow& row)
{
    model.Input(row[L"Numbers"].strValue());
}

// The result <Sum> shall be informed[[mock]]
void String_calculator_using_mock_object_Steps::The_result_Sum_shall_be_informedmock(GherkinRow& row)
{
    model.ExpectedSum(row[L"Sum"].intValue());
}



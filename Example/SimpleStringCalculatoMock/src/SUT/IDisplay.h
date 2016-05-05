#pragma once

class IDisplay
{
public:
    ~IDisplay(){}
    virtual void Sum(int sum) = 0;
};

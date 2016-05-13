#pragma once

class IDisplay
{
public:
    virtual ~IDisplay(){}
    virtual void Sum(int sum) = 0;
};

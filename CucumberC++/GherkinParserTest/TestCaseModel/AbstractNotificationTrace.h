#pragma once

#include <string>
#include <chrono>

class AbstractNotificationTrace
{
    friend class ThreadModelFactory;
public:
	~AbstractNotificationTrace(){}
    virtual void Append(std::string /*notification_msg*/){}
    virtual void WaitNotification(std::string /*expected_msg*/, std::chrono::milliseconds /*wait_time*/){}

protected:
    AbstractNotificationTrace() {}
};

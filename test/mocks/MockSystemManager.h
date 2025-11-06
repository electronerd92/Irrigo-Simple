#ifndef MOCK_SYSTEM_MANAGER_H
#define MOCK_SYSTEM_MANAGER_H

#include <interfaces/ISystemManager.h>
#include <interfaces/IRtc.h>
#include <vector>
#include <string>

class MockSystemManager : public ISystemManager
{
public:
    struct Call
    {
        std::string name;
    };

private:
    std::vector<Call> calls;

public:
    void update() override
    {
        calls.push_back({"update"});
    }

    RtcDateTime getDateTime() override
    {
        calls.push_back({"getDateTime"});
        // Return dummy value
        return {2024, 1, 1, 0, 0, 0};
    }

    void incrementDay() override { calls.push_back({"incrementDay"}); }
    void decreaseDay() override { calls.push_back({"decreaseDay"}); }
    void incrementMonth() override { calls.push_back({"incrementMonth"}); }
    void decreaseMonth() override { calls.push_back({"decreaseMonth"}); }
    void incrementYear() override { calls.push_back({"incrementYear"}); }
    void decreaseYear() override { calls.push_back({"decreaseYear"}); }
    void incrementHour() override { calls.push_back({"incrementHour"}); }
    void decreaseHour() override { calls.push_back({"decreaseHour"}); }
    void incrementMinute() override { calls.push_back({"incrementMinute"}); }
    void decreaseMinute() override { calls.push_back({"decreaseMinute"}); }

    // Helper to verify interactions in tests
    bool wasCalled(const std::string &method) const
    {
        for (auto &c : calls)
        {
            if (c.name == method)
                return true;
        }
        return false;
    }

    int callCount(const std::string &method) const
    {
        int count = 0;
        for (auto &c : calls)
            if (c.name == method)
                count++;
        return count;
    }

    void clearCalls()
    {
        calls.clear();
    }
};

#endif // MOCK_SYSTEM_MANAGER_H

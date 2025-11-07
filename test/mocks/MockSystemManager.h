#pragma once
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

    // Helper methods for easier testing
    void assertOnlyMethodCalled(const std::string &expectedMethod, int expectedCount = 1) const
    {
        const std::vector<std::string> allMethods = {
            "incrementDay", "decreaseDay", "incrementMonth", "decreaseMonth",
            "incrementYear", "decreaseYear", "incrementHour", "decreaseHour",
            "incrementMinute", "decreaseMinute"};

        for (const auto &method : allMethods)
        {
            if (method == expectedMethod)
            {
                TEST_ASSERT_EQUAL_MESSAGE(expectedCount, callCount(method),
                                          ("Expected " + expectedMethod + " to be called " + std::to_string(expectedCount) + " times").c_str());
            }
            else
            {
                TEST_ASSERT_EQUAL_MESSAGE(0, callCount(method),
                                          ("Expected " + method + " NOT to be called").c_str());
            }
        }
    }

    void assertNoDateTimeMethods() const
    {
        assertOnlyMethodCalled("", 0); // Will check all methods are 0
    }
};
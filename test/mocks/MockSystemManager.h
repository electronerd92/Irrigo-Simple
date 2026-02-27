#pragma once
#include <interfaces/ISystemManager.h>
#include <interfaces/IRtc.h>
#include <interfaces/IMainSystem.h>
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
    uint8_t selectedValve;

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

    uint32_t getUnixTime() override
    {
        calls.push_back({"getUnixTime"});
        return 0; // Return dummy value
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

    uint8_t getSelectedValve() override
    {
        calls.push_back({"getSelectedValve"});
        return selectedValve;
    }
    void incrementSelectedValve() override
    {
        calls.push_back({"incrementSelectedValve"});
        selectedValve++;
    }
    void decreaseSelectedValve() override
    {
        calls.push_back({"decreaseSelectedValve"});
        if (selectedValve > 0)
            selectedValve--;
    }

    ValveMode getSelectedValveMode() override
    {
        calls.push_back({"getSelectedValveMode"});
        return ValveMode::OFF; // Return dummy value
    }
    void incrementSelectedValveMode() override { calls.push_back({"incrementSelectedValveMode"}); }
    void decreaseSelectedValveMode() override { calls.push_back({"decreaseSelectedValveMode"}); }

    uint32_t getSelectedValveFrequency() override
    {
        calls.push_back({"getSelectedValveFrequency"});
        return 0; // Return dummy value
    }
    void incrementSelectedValveFrequency() override { calls.push_back({"incrementSelectedValveFrequency"}); }
    void decreaseSelectedValveFrequency() override { calls.push_back({"decreaseSelectedValveFrequency"}); }

    uint32_t getSelectedValveDuration() override
    {
        calls.push_back({"getSelectedValveDuration"});
        return 0; // Return dummy value
    }
    void incrementSelectedValveDuration() override { calls.push_back({"incrementSelectedValveDuration"}); }
    void decreaseSelectedValveDuration() override { calls.push_back({"decreaseSelectedValveDuration"}); }

    uint32_t getSelectedValveStartTime() override
    {
        calls.push_back({"getSelectedValveStartTime"});
        return 0; // Return dummy value
    }
    uint8_t getSelectedValveStartHour() override
    {
        calls.push_back({"getSelectedValveStartHour"});
        return 0; // Return dummy value
    }
    uint8_t getSelectedValveStartMinute() override
    {
        calls.push_back({"getSelectedValveStartMinute"});
        return 0; // Return dummy value
    }
    void incrementSelectedValveStartHour() override { calls.push_back({"incrementSelectedValveStartHour"}); }
    void decreaseSelectedValveStartHour() override { calls.push_back({"decreaseSelectedValveStartHour"}); }
    void incrementSelectedValveStartMinute() override { calls.push_back({"incrementSelectedValveStartMinute"}); }
    void decreaseSelectedValveStartMinute() override { calls.push_back({"decreaseSelectedValveStartMinute"}); }

    SystemState getSystemState() override
    {
        calls.push_back({"getSystemState"});
        return SystemState::Normal; // Return dummy value
    }
    void setSystemState(SystemState sysState) override
    {
        calls.push_back({"setSystemState"});
        // No-op for testing
    }

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
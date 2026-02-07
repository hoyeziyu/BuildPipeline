#include <gtest/gtest.h>
#include <greeter/Greeter.h>

TEST(GreeterAPITests, GetGreetingReturnsCorrectString) {
    const std::string expected{
      "Hello from the modular Greeter library!"
    };

    EXPECT_EQ(get_greeting(), expected);
}

// A test fixture for Greeter tests 测试夹具（针对类） 
class GreeterTest : public testing::Test {
protected:
    Greeter my_greeter;
};

// Use the TEST_F macro to use the fixture
TEST_F(GreeterTest, GreetReturnsCorrectString) {
    EXPECT_EQ(
        my_greeter.greet(),
        "Hello from the Greeter class!"
    );
}
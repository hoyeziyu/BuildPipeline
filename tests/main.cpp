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

const char* getDanglingPointer() {
    char local_buffer[] = "This is temporary";

    // DANGER: returning pointer to local variable
    return local_buffer;
}

TEST(
    ASanRuntimeOptionTests,
    FailsToDetectUseAfterReturnByDefault
) {
    const char* dangling_ptr = getDanglingPointer();

    // The memory dangling_ptr points to is no longer valid.
    // Accessing it is undefined behavior.
    char first_char = dangling_ptr[0]; // <w>

    // This assertion might pass by chance if
    // the memory hasn't been overwritten.
    EXPECT_NE(first_char, '\0');
}
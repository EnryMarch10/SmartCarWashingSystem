#include <Arduino.h>
#include <unity.h>

#include "OrderedSet.h"

#define N 100
#define RANDOM_PORT A3
#define CYCLE_ITERATIONS 30
#define MIN_NUM 3
#define MAX_NUM 30

class Integer {

public:
    Integer(void) { }
    Integer(const int n)
    {
        this->n = n;
    }
    int get(void)
    {
        return n;
    }
    bool operator==(const Integer& rhs) const
    {
        return this == &rhs;
    }
    ~Integer(void) { }

private:
    int n;

};

static unsigned int func(Integer &value) {
    return value.get();
}

OrderedSet<Integer> *set;
char buf[20];

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}


void order(void)
{
    int min;
    if (set->length() > 0) {
        min = set->get(0).get();
    }
    for (unsigned char i = 0; i < set->length(); i++) {
        TEST_ASSERT_FALSE_MESSAGE(set->get(0).get() < min, "Order error");
    }
}

void deletions(void)
{
    while (set->length() > 0) {
        TEST_ASSERT_TRUE_MESSAGE(set->remove(set->get(0)), "Error in removing element");
    }
}

static void iterate(void) {
    static int i = 0;
    i++;
    Integer n(random(MIN_NUM, MAX_NUM) / 2);
    const int result = set->add(n);
    TEST_ASSERT_NOT_EQUAL_MESSAGE(BaseOrderedSet::getErrorIndex(), result, "Error in inserting element");
    if (i % 5 == 0) {
        TEST_ASSERT_EQUAL_MESSAGE(BaseOrderedSet::getErrorIndex(), set->add(set->get(result)), "Accepted two equal items in set");
    }
}

void setup()
{
    UNITY_BEGIN();   
    TEST_MESSAGE("START");
}

void loop()
{
    static unsigned i = 0;
    i++;

    randomSeed(analogRead(RANDOM_PORT));
    set = new OrderedSet<Integer>(func);

    for (int j = 0; j < CYCLE_ITERATIONS; j++) {
        RUN_TEST(iterate);
    }

    UNITY_PRINT_EOL();
    UnityPrint("/// START ");
    UnityPrintNumberUnsigned(i);
    UnityPrint(" ///");
    UNITY_PRINT_EOL();
    UnityPrint("length = ");
    UnityPrintNumber(set->length());
    UNITY_PRINT_EOL();
    UnityPrint("[");
    UnityPrintNumber(set->get(0).get());
    for (int i = 1; i < set->length(); i++) {
        UnityPrint(", ");
        UnityPrintNumber(set->get(i).get());
    }
    UnityPrint("]");
    UNITY_PRINT_EOL();

    RUN_TEST(order);
    RUN_TEST(deletions);

    delete set;

    if (i > N) {
        UNITY_PRINT_EOL();
        TEST_MESSAGE("END");
        UNITY_END();
    }
}

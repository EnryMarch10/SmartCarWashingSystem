#include <Arduino.h>
#include <unity.h>

#include "OrderedList.h"

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
    bool operator!=(const Integer& rhs) const
    {
        return !(*this == rhs);
    }
    ~Integer(void) { }

private:
    int n;

};

static unsigned int func(Integer &value) {
    return value.get();
}

OrderedList<Integer, unsigned> *list;
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
    int last;
    if (list->containsSomething()) {
        last = list->getFirst().get();
    }
    for (unsigned char i = 0; i < list->length(); i++) {
        const int value = list->get(i).get();
        TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(value, last, "Order error");
        if (last < value) {
            last = value;
        }
    }
}

void deletions(void)
{
    while (list->containsSomething()) {
        TEST_ASSERT_TRUE_MESSAGE(list->remove(list->get(0)), "Error in removing element");
    }
}

static void iterate(void) {
    static int i = 0;
    i++;
    Integer n(random(MIN_NUM, MAX_NUM) / 2);
    list->add(n);
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
    list = new OrderedList<Integer, unsigned>(func);

    for (int j = 0; j < CYCLE_ITERATIONS; j++) {
        iterate();
    }

    UNITY_PRINT_EOL();
    UnityPrint("/// START ");
    UnityPrintNumberUnsigned(i);
    UnityPrint(" ///");
    UNITY_PRINT_EOL();
    UnityPrint("length = ");
    UnityPrintNumber(list->length());
    UNITY_PRINT_EOL();
    UnityPrint("[");
    UnityPrintNumber(list->getFirst().get());
    for (int i = 1; i < list->length(); i++) {
        UnityPrint(", ");
        UnityPrintNumber(list->get(i).get());
    }
    UnityPrint("]");
    UNITY_PRINT_EOL();

    RUN_TEST(order);
    RUN_TEST(deletions);

    delete list;

    if (i > N) {
        UNITY_PRINT_EOL();
        TEST_MESSAGE("END");
        UNITY_END();
    }
}

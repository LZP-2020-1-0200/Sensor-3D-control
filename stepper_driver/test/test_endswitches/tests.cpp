#include "unity.h"
#include "endSwitch.h"
void setUp(void) {
  
}

void tearDown(void) {
  // clean stuff up here
}

void switchConstructorTest(void){
	uint8_t port = 0b00111100;
	uint8_t portpin = 4;
	uint8_t ddr = 0b11000100;
	uint8_t ddrpin = 7;
	uint8_t pin = 2;
	uint8_t pinpin = 0;
	EndSwitch sw(&port, portpin, &ddr, ddrpin, &pin, pinpin);
	TEST_ASSERT_EQUAL_MESSAGE(0b00101100, port, "port match");
	TEST_ASSERT_EQUAL_MESSAGE(0b01000100, ddr, "DDR match");
	TEST_ASSERT_EQUAL_MESSAGE(2, pin, "pin match");
}

void switchReadTest(void){
	uint8_t port = 0b00111100;
	uint8_t portpin = 4;
	uint8_t ddr = 0b11000100;
	uint8_t ddrpin = 7;
	uint8_t pin = 2;
	uint8_t pinpin = 0;
	EndSwitch sw(&port, portpin, &ddr, ddrpin, &pin, pinpin);
	sw.update();
	TEST_ASSERT_FALSE_MESSAGE(sw.getState(), "1st read");
	pin |= 1;
	sw.update();
	TEST_ASSERT_TRUE_MESSAGE(sw.getState(), "2nd read");
}

int runUnityTests(void) {
  UNITY_BEGIN();
  UNITY
  RUN_TEST(switchConstructorTest);
  RUN_TEST(switchReadTest);
  return UNITY_END();
}

/**
  * For Arduino framework
  */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}
void loop() {}

#include "unity.h"
#include "stepper.h"
void setUp(void) {
  
}

void tearDown(void) {
  // clean stuff up here
}

const uint8_t portSetup = 0b00111100;
const uint8_t ddrSetup = 0b11000100;
const uint8_t pin1 = 0, pin2 = 2, pin3 = 3, pin4 = 6;
const uint8_t pinMask = (1 << pin1) | (1 << pin2) | (1 << pin3) | (1 << pin4);

// tests if the pin setup is performed correctly
void stepperConstructorTest(void){
  uint8_t port = portSetup;
  uint8_t ddr = ddrSetup;
	Stepper sw(Stepper::motorData{&port, &ddr, pin1, pin2, pin3, pin4});
	TEST_ASSERT_EQUAL_MESSAGE(portSetup, port, "port match");
	TEST_ASSERT_EQUAL_MESSAGE(ddrSetup | pinMask, ddr, "DDR match");
}


void stepperStepTest(void){
  uint8_t port = portSetup;
  uint8_t ddr = ddrSetup;
  Stepper sw(Stepper::motorData{&port, &ddr, pin1, pin2, pin3, pin4});
  uint8_t states[16];
	for(unsigned int x = 0 ; x < 16 ; x++){
    sw.forward();
    states[x] = port;
  }
  for(unsigned int i = 0; i < 8; i++){
    TEST_ASSERT_EQUAL_MESSAGE(states[i], states[i+8], "forward cycle match");
    for(unsigned int i2 = i + 1; i2 < 8; i2++) {
      TEST_ASSERT_NOT_EQUAL_MESSAGE(states[i], states[i2], "forward cycle uniqueness");
    }
  }
  for(unsigned int x = 0 ; x < 16 ; x++){
    sw.backward();
    states[x] = port;
  }
  for(unsigned int i = 0; i < 8; i++){
    TEST_ASSERT_EQUAL_MESSAGE(states[i], states[i+8], "backward cycle match");
    for(unsigned int i2 = i + 1; i2 < 8; i2++) {
      TEST_ASSERT_NOT_EQUAL_MESSAGE(states[i], states[i2], "backward cycle uniqueness");
    }
  }
}

int runUnityTests(void) {
  UNITY_BEGIN();
  UNITY
  RUN_TEST(stepperConstructorTest);
  RUN_TEST(stepperStepTest);
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

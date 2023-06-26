#include "unity.h"
#include "tests.h"
#include <Arduino.h>

void setUp(void) {
  
}

void tearDown(void) {
  // clean stuff up here
}

int runUnityTests(void) {
  UNITY_BEGIN();
  UNITY
  RUN_TEST(constructor);
  RUN_TEST(vecPlusInt);
  RUN_TEST(intPlusVec);
  RUN_TEST(intTimesVec);
  RUN_TEST(vecTimesInt);
  RUN_TEST(vecPEint);
  RUN_TEST(vecTEint);
  RUN_TEST(vecDEint);
  RUN_TEST(vecDivInt);
  
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

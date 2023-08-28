#include "unity.h"
#include "tests.h"
void setUp(void) {
  
}

void tearDown(void) {
  // clean stuff up here
}


int runUnityTests(void) {
  UNITY_BEGIN();
  UNITY
  RUN_TEST(test_report);
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

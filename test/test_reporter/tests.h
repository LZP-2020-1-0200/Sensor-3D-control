#include "unity.h"
#include "reporter.h"

void test_report(void){
	reportError("gasket");
	TEST_ASSERT_EQUAL_CHAR_ARRAY("gasket", errorMsg, 7);
	TEST_ASSERT_TRUE(errorUnreported);
}

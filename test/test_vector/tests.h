#include "unity.h"
#include "vector.h"

void constructor(void) {
	Vector v(4,1,2);
	TEST_ASSERT_EQUAL(4, v.x);
	TEST_ASSERT_EQUAL(1, v.y);
	TEST_ASSERT_EQUAL(2, v.z);
}

void vecPlusInt(void){
	Vector v(1,-1,-15);
	v = v + 5;
  	TEST_ASSERT_EQUAL(6, v.x);
  	TEST_ASSERT_EQUAL(4, v.y);
  	TEST_ASSERT_EQUAL(-10, v.z);
}

void intPlusVec(void){
	Vector v(1,-1,-15);
	v = 5 + v;
  	TEST_ASSERT_EQUAL(6, v.x);
  	TEST_ASSERT_EQUAL(4, v.y);
  	TEST_ASSERT_EQUAL(-10, v.z);
}

void vecPEint(void){
	Vector v(2,3,1);
	v+=4;
  	TEST_ASSERT_EQUAL(6, v.x);
  	TEST_ASSERT_EQUAL(7, v.y);
  	TEST_ASSERT_EQUAL(5, v.z);
}

void intTimesVec(void){
	Vector v(1,-1,-15);
	v = 5 * v;
  	TEST_ASSERT_EQUAL(5, v.x);
  	TEST_ASSERT_EQUAL(-5, v.y);
  	TEST_ASSERT_EQUAL(-75, v.z);
}

void vecTimesInt(void){
	Vector v(1,-1,-15);
	v = v * 5;
  	TEST_ASSERT_EQUAL(5, v.x);
  	TEST_ASSERT_EQUAL(-5, v.y);
  	TEST_ASSERT_EQUAL(-75, v.z);
}

void vecTEint(void){
	Vector v(2,3,1);
	v*=4;
  	TEST_ASSERT_EQUAL(8, v.x);
  	TEST_ASSERT_EQUAL(12, v.y);
  	TEST_ASSERT_EQUAL(4, v.z);
}


void vecMinusInt(void){
	Vector v(1,-1,-15);
	v = v - 5;
  	TEST_ASSERT_EQUAL(1, v.x);
  	TEST_ASSERT_EQUAL(-6, v.y);
  	TEST_ASSERT_EQUAL(-20, v.z);
}

void vecMEint(void){
	Vector v(2,3,1);
	v-=4;
  	TEST_ASSERT_EQUAL(-2, v.x);
  	TEST_ASSERT_EQUAL(-1, v.y);
  	TEST_ASSERT_EQUAL(-3, v.z);
}

void vecDivInt(void){
	Vector v(1,-20,-16);
	v = v / 5;
  	TEST_ASSERT_EQUAL(0, v.x);
  	TEST_ASSERT_EQUAL(-4, v.y);
  	TEST_ASSERT_EQUAL(-3, v.z);
}

void vecDEint(void){
	Vector v(1,11,-16);
	v/=4;
  	TEST_ASSERT_EQUAL(0, v.x);
  	TEST_ASSERT_EQUAL(2, v.y);
  	TEST_ASSERT_EQUAL(-4, v.z);
}

void vecPvec(void){
	Vector v(5,-21,1);
	Vector v2(3,5,1);
	Vector v3 = v + v2;
  	TEST_ASSERT_EQUAL(8, v3.x);
  	TEST_ASSERT_EQUAL(-16, v3.y);
  	TEST_ASSERT_EQUAL(2, v3.z);
}

void vecMvec(void){
	Vector v(5,-21,1);
	Vector v2(3,5,1);
	Vector v3 = v - v2;
  	TEST_ASSERT_EQUAL(2, v3.x);
  	TEST_ASSERT_EQUAL(-26, v3.y);
  	TEST_ASSERT_EQUAL(0, v3.z);
}

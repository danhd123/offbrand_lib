
#include "../../include/offbrand.h"
#include "../../include/OBBigUInt.h"
#include "../../include/OBTest.h"

/* UINT32_MAX = 4294967295 */

int main (){

  /* various OBBigUInts needed for testing */
  OBBigUInt *two, *zero, *a, *b, *c, *add_result, *sub_result, *mult_result;
  OBBigUInt *div_result, *mod_result, *shift_result, *and_result, *or_result;
  OBBigUInt *xor_result, *not_result;

  uint32_t num1[3] = {1234567890, 987654321, 2910};
  uint32_t num2[3] = {2143658709, 5162738490, 982647};

  two = createBigUIntFromNum(2);
  zero = createBigUIntFromNum(0);
  if(!two || !zero){
    fprintf(stderr, "OBBigUInt_test: Could not allocate two or zero, TEST "
                    "FAILED\n");
    exit(1);
  }

  a = createBigUIntFromIntArray(num1, 3);
  b = createBigUIntFromIntArray(num2, 3);
  c = createBigUIntFromIntArray(num1, 3);
  if(!a || !b || !c){
    fprintf(stderr, "OBBigUInt_test: Could not allocate a or b, TEST FAILED\n");
    exit(1);
  }

  if(compareBigUInts(a, b) != OB_LESS_THAN){
    fprintf(stderr, "OBBigUInt_test: Less than comparision failed, "
                    "TEST FAILED\n");
    exit(1);
  }

  if(compareBigUInts(b, c) != OB_GREATER_THAN){
    fprintf(stderr, "OBBigUInt_test: Greater than comparision failed, "
                    "TEST FAILED\n");
    exit(1);
  }

  if(compareBigUInts(a,c) != OB_EQUAL_TO){
    fprintf(stderr, "OBBigUInt_test: Equal to comparision failed, "
                    "TEST FAILED\n");
    exit(1);
  }

  /* release uneeded object */
  release((obj *)c);

  add_result = addBigUInts(a, b);
  if(!add_result){
    fprintf(stderr, "OBBigUInt_test: Addition returns NULL, TEST FAILED\n");
    exit(1);
  }

  sub_result = subtractBigUInts(add_result, a);
  if(!sub_result){
    fprintf(stderr, "OBBigUInt_test: Subtraction returns NULL, TEST FAILED\n");
    exit(1);
  }

  if(compareBigUInts(b,sub_result) != OB_EQUAL_TO){
    fprintf(stderr, "OBBigUInt_test: addition and subtraction did not form "
                    "inverse operations\nTEST FAILED\n");
    exit(1);
  }

  mult_result = multiplyBigUInts(a,b);
  if(!mult_result){
    fprintf(stderr, "OBBigUInt_test: Multiply returns NULL, TEST FAILED\n");
    exit(1);
  }

  div_result = divideBigUInts(mult_result, b);
  if(!div_result){
    fprintf(stderr, "OBBigUInt_test: Divide returns NULL, TEST FAILED\n");
    exit(1);
  }

  if(compareBigUInts(a, div_result)){
    fprintf(stderr, "OBBigUInt_test: Divided and multiply are not inverse "
                    "operations, TEST FAILED\n");
    exit(1);
  }

  c = addBigUInts(mult_result, a);
  if(!c){
    fprintf(stderr, "OBBigUInt_test: Could not create secondary c, TEST "
                    "FAILED\n");
    exit(1);
  }

  mod_result = modBigUInts(c, b);
  if(!mod_result){
    fprintf(stderr, "OBBigUInt_test: Mod returns NULL, TEST FAILED\n");
    exit(1);
  }

  if(compareBigUInts(a, mod_result) != OB_EQUAL_TO){
    fprintf(stderr, "OBBigUInt_test: Mod operation did not return expected "
                    "value, TEST FAILED\n");
    exit(1);
  }
  

  printf("OBBigUInt_test: TESTS PASSED\n");
  return 0;
}

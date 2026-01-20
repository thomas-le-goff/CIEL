#include <stddef.h>
#include "tests.h"
#include "test-framework/unity.h"
#include "tp_functions.h"

extern int global_counter;

void setUp(void)
{
   // Nothing to setup
}

void tearDown(void)
{
   // Nothing to tearDown
}

void test_pass_by_value_does_not_change_original(void)
{
   int v = 10;
   int r = counter_val(v);
   TEST_ASSERT_EQUAL_INT(10, v);
   TEST_ASSERT_EQUAL_INT(11, r);
}

void test_pass_by_reference_changes_original(void)
{
   int v = 10;
   counter_ref(&v);
   TEST_ASSERT_EQUAL_INT(11, v);
}

void test_global_changes_global(void)
{
   TEST_ASSERT_EQUAL_INT(0, global_counter);

   counter_global();

   TEST_ASSERT_EQUAL_INT(1, global_counter);

   counter_global();
   TEST_ASSERT_EQUAL_INT(2, global_counter);
}

void test_function_return_value(void)
{
   TEST_ASSERT_EQUAL_INT(7, add(3, 4));
}

void test_struct_by_value_does_not_change_original(void)
{

   Point p = {2.0, 3.0};
   Point pb = scale_point_by_value(p, 10);

   TEST_ASSERT_EQUAL_INT(2.0, p.x);
   TEST_ASSERT_EQUAL_FLOAT(3.0, p.y);

   TEST_ASSERT_EQUAL_INT(20.0, pb.x);
   TEST_ASSERT_EQUAL_FLOAT(30.0, pb.y);
}

void test_struct_by_reference_changes_original(void)
{

   Point p = {2.0, 3.0};
   scale_point_by_ref(&p, 10);
   TEST_ASSERT_EQUAL_INT(20.0, p.x);
   TEST_ASSERT_EQUAL_FLOAT(30.0, p.y);
}

void test_out_parameter_writes_result(void)
{

   int a[] = {1, 2, 3, 4};
   int sum = 0;
   int max = sum_array_max_out(4, a, &sum);
   TEST_ASSERT_EQUAL_INT(4, max);
   TEST_ASSERT_EQUAL_INT(10, sum);
}

void test_out_parameter_writes_result_with_a_trap(void)
{

   int a[] = {1, 2, 3, 4};
   int sum = 50;
   int max = sum_array_max_out(4, a, &sum);
   TEST_ASSERT_EQUAL_INT(4, max);
   TEST_ASSERT_EQUAL_INT(10, sum);
}

// void test_array_parameter_decays_to_pointer(void)
// {

//    int a[10] = {0};

//    size_t s_param = sizeof_param_int_array(a);
//    size_t s_local = sizeof(a);

//    TEST_ASSERT_NOT_EQUAL(s_param, s_local);
//    TEST_ASSERT_EQUAL_size_t(sizeof(int *), s_param);
//    TEST_ASSERT_EQUAL_size_t(10 * sizeof(int), s_local);
// }

int main(void)
{
   UNITY_BEGIN();

   RUN_TEST(test_pass_by_value_does_not_change_original);
   RUN_TEST(test_pass_by_reference_changes_original);
   RUN_TEST(test_global_changes_global);
   RUN_TEST(test_function_return_value);
   RUN_TEST(test_struct_by_value_does_not_change_original);
   RUN_TEST(test_struct_by_reference_changes_original);
   RUN_TEST(test_out_parameter_writes_result);
   RUN_TEST(test_out_parameter_writes_result_with_a_trap);
   // RUN_TEST(test_array_parameter_decays_to_pointer);

   return UNITY_END();
}
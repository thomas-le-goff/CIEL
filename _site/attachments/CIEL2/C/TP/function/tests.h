void setUp(void);

void tearDown(void);

void test_pass_by_value_does_not_change_original(void);

void test_pass_by_reference_changes_original(void);

void test_global_changes_global(void);

void test_function_return_value(void);

void test_struct_by_value_does_not_change_original(void);

void test_struct_by_reference_changes_original(void);

void test_out_parameter_writes_result(void);

void test_out_parameter_writes_result_with_a_trap(void);

void test_array_parameter_decays_to_pointer(void);

int main(void);
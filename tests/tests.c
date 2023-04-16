#include <check.h>

#include "../src/my_matrix.h"

double M_3x3[9] = {7.0, 15.0, 2.0, 3.25, 4.5, 9.0, -7.2, 0.65, 0.0};
double M_3x3_inverse[9] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};
double M_3x3_math[9] = {8.0, 2.0, -3.0, 0.000002, 4.47, 5.0, 0.3, 1.0, -6.0};
double M_3x3_zero[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
double M_3x1[3] = {4.2, 6.1, -5.0};
double M_3x2[6] = {5.2, -9.0, 8.5, 4.5689631, 4.25, -3.687};
double M_3x2_for_eq[6] = {5.2, -9.0, 8.5, 4.5689638, 4.25, -3.687};
double M_1[1] = {5.0};

matrix_t test_matrix(double *values, int rows, int columns) {
  matrix_t matrix;
  my_create_matrix(rows, columns, &matrix);
  int counter = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix.matrix[i][j] = values[counter];
      counter++;
    }
  }
  return matrix;
}

START_TEST(test_create) {
  matrix_t A;
  int test = my_create_matrix(0, 0, &A);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  test = my_create_matrix(3, 0, &A);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  test = my_create_matrix(0, 2, &A);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  test = my_create_matrix(2, -1, &A);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  test = my_create_matrix(-4, 6, &A);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  test = my_create_matrix(2, 12, &A);
  ck_assert_int_eq(test, CORRECT);
  my_remove_matrix(&A);

  test = my_create_matrix(1, 1, &A);
  ck_assert_int_eq(test, CORRECT);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(test_equal) {
  matrix_t A;
  matrix_t B;

  my_create_matrix(0, 0, &A);
  my_create_matrix(0, 0, &B);
  int test = my_eq_matrix(&A, &B);
  ck_assert_int_eq(test, FAIL);

  my_create_matrix(2, 3, &A);
  my_create_matrix(3, 2, &B);
  test = my_eq_matrix(&A, &B);
  ck_assert_int_eq(test, FAIL);
  my_remove_matrix(&A);
  my_remove_matrix(&B);

  my_create_matrix(2, 3, &A);
  my_create_matrix(2, 3, &B);
  test = my_eq_matrix(&A, &B);
  ck_assert_int_eq(test, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);

  A = test_matrix(M_3x2, 3, 2);
  B = test_matrix(M_3x2_for_eq, 3, 2);
  test = my_eq_matrix(&A, &B);
  ck_assert_int_eq(test, FAIL);
  my_remove_matrix(&A);
  my_remove_matrix(&B);

  A = test_matrix(M_3x2, 3, 2);
  B = test_matrix(M_3x2, 3, 2);
  test = my_eq_matrix(&A, &B);
  ck_assert_int_eq(test, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_create_matrix_test) {
  matrix_t A;
  int res = my_create_matrix(1, 2, &A);
  ck_assert_int_eq(res, CORRECT);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(my_create_matrix_test_2) {
  matrix_t A = {0};
  int res = my_create_matrix(1, -2, &A);
  ck_assert_int_eq(res, UNCORRECT_MATRIX);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(my_create_matrix_test_3) {
  matrix_t A;
  int res = my_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 1;
  ck_assert_int_eq(res, CORRECT);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(my_create_matrix_test_4) {
  matrix_t A;
  int res = my_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 5;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 9;
  A.matrix[2][2] = 10;
  ck_assert_int_eq(res, CORRECT);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(my_eq_matrix_test) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(3, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  int result = my_eq_matrix(&A, &B);
  ck_assert_int_eq(result, 0);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_eq_matrix_test_2) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(1, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = 3;
  int result = my_eq_matrix(&A, &B);
  ck_assert_int_eq(result, 0);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_eq_matrix_test_3) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(3, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 3;
  B.matrix[2][1] = 3;
  B.matrix[2][2] = 3;
  int result = my_eq_matrix(&A, &B);
  ck_assert_int_eq(result, 1);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_eq_matrix_test_4) {
  matrix_t A;
  my_create_matrix(1, 1, &A);
  matrix_t B;
  my_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.515673;
  B.matrix[0][0] = 1.515673;
  int result = my_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_eq_matrix_test_5) {
  matrix_t A;
  my_create_matrix(1, 1, &A);
  matrix_t B;
  my_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.5156739;
  B.matrix[0][0] = 1.515673;
  int result = my_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAIL);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_eq_matrix_test_6) {
  matrix_t A;
  my_create_matrix(1, 1, &A);
  matrix_t B;
  my_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.515674;
  B.matrix[0][0] = 1.5156735;
  int result = my_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAIL);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_sum_and_sub_matrix_test) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(3, 3, &B);
  matrix_t C;
  my_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  C.matrix[0][0] = 4;
  C.matrix[0][1] = 4;
  C.matrix[0][2] = 4;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = 4;
  C.matrix[1][2] = 4;
  C.matrix[2][0] = 4;
  C.matrix[2][1] = 4;
  C.matrix[2][2] = 4;
  matrix_t my;
  my_sum_matrix(&A, &B, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, 1);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_sum_and_sub_matrix_test_2) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(1, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = 3;
  matrix_t my;
  int result = my_sum_matrix(&A, &B, &my);
  ck_assert_int_eq(result, CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_sum_and_sub_matrix_test_3) {
  matrix_t A;
  my_create_matrix(1, 3, &A);
  matrix_t B;
  my_create_matrix(1, 3, &B);
  matrix_t C;
  my_create_matrix(1, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 1;
  C.matrix[0][0] = 1;
  C.matrix[0][1] = 1;
  C.matrix[0][2] = 1;
  matrix_t my;
  my_sum_matrix(&A, &B, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, 0);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_sum_and_sub_matrix_test_4) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(3, 3, &B);
  matrix_t C;
  my_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  C.matrix[0][0] = 4;
  C.matrix[0][1] = 4;
  C.matrix[0][2] = 4;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = 4;
  C.matrix[1][2] = 4;
  C.matrix[2][0] = 4;
  C.matrix[2][1] = 4;
  C.matrix[2][2] = 4;
  matrix_t my;
  my_sub_matrix(&A, &B, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, 0);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_sum_and_sub_matrix_test_5) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(1, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = 3;
  matrix_t my;
  int result = my_sub_matrix(&A, &B, &my);
  ck_assert_int_eq(result, CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_mult_number_test) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t C;
  my_create_matrix(3, 3, &C);
  double x = 2.0;
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  C.matrix[0][0] = 4;
  C.matrix[0][1] = 4;
  C.matrix[0][2] = 4;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = 4;
  C.matrix[1][2] = 4;
  C.matrix[2][0] = 4;
  C.matrix[2][1] = 4;
  C.matrix[2][2] = 4;
  matrix_t my;
  my_mult_number(&A, x, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, 0);
  my_remove_matrix(&A);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_mult_number_test_2) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t C;
  my_create_matrix(3, 3, &C);
  double x = 0.0;
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  C.matrix[0][0] = 0;
  C.matrix[0][1] = 0;
  C.matrix[0][2] = 0;
  C.matrix[1][0] = 0;
  C.matrix[1][1] = 0;
  C.matrix[1][2] = 0;
  C.matrix[2][0] = 0;
  C.matrix[2][1] = 0;
  C.matrix[2][2] = 0;
  matrix_t my;
  my_mult_number(&A, x, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, 1);
  my_remove_matrix(&A);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_mult_matrix_test) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(3, 3, &B);
  matrix_t C;
  my_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 3;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  C.matrix[0][0] = 3;
  C.matrix[0][1] = 3;
  C.matrix[0][2] = 3;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = 4;
  C.matrix[1][2] = 4;
  C.matrix[2][0] = 3;
  C.matrix[2][1] = 3;
  C.matrix[2][2] = 32;
  matrix_t my;
  my_mult_matrix(&A, &B, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, 0);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_mult_matrix_test_2) {
  matrix_t A;
  my_create_matrix(1, 3, &A);
  matrix_t B;
  my_create_matrix(3, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  matrix_t my;
  int result = my_mult_matrix(&A, &B, &my);
  ck_assert_int_eq(result, 0);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_transpose_test) {
  matrix_t A;
  my_create_matrix(3, 2, &A);
  matrix_t C;
  my_create_matrix(2, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  C.matrix[0][0] = 1;
  C.matrix[0][1] = 4;
  C.matrix[0][2] = 2;
  C.matrix[1][0] = 3;
  C.matrix[1][1] = 5;
  C.matrix[1][2] = 6;
  matrix_t my;
  my_transpose(&A, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, 0);
  my_remove_matrix(&A);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_determinant_test) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  double det = 0;
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  my_determinant(&A, &det);
  ck_assert_uint_eq(det, 0);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(my_determinant_test_2) {
  matrix_t A;
  my_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  double result;
  my_determinant(&A, &result);
  ck_assert(result != result);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(my_calc_complements_test) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t C;
  my_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  C.matrix[0][0] = 0;
  C.matrix[0][1] = -10;
  C.matrix[0][2] = -20;
  C.matrix[1][0] = -4;
  C.matrix[1][1] = -14;
  C.matrix[1][2] = -8;
  C.matrix[2][0] = -8;
  C.matrix[2][1] = 2;
  C.matrix[2][2] = 4;
  matrix_t my;
  my_calc_complements(&A, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, FAIL);
  my_remove_matrix(&A);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_inverse_matrix_test) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t C;
  my_create_matrix(3, 3, &C);
  A.matrix[0][0] = -1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = -2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -1;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = 4;
  C.matrix[0][0] = 0.6;
  C.matrix[0][1] = -0.4;
  C.matrix[0][2] = 0.8;
  C.matrix[1][0] = 0.7;
  C.matrix[1][1] = 0.2;
  C.matrix[1][2] = 0.1;
  C.matrix[2][0] = -0.1;
  C.matrix[2][1] = 0.4;
  C.matrix[2][2] = -0.3;
  matrix_t my;
  my_inverse_matrix(&A, &my);
  int result = my_eq_matrix(&my, &C);
  ck_assert_int_eq(result, 1);
  my_remove_matrix(&A);
  my_remove_matrix(&C);
  my_remove_matrix(&my);
}
END_TEST

START_TEST(my_calc_complement_test) {
  matrix_t A;
  my_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  matrix_t res;
  ck_assert(my_calc_complements(&A, &res) == CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&res);
}
END_TEST

START_TEST(my_calc_complement_test_2) {
  matrix_t A;
  my_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1;
  matrix_t res;
  my_calc_complements(&A, &res);
  ck_assert_int_eq(my_eq_matrix(&A, &res), 1);
  my_remove_matrix(&A);
  my_remove_matrix(&res);
}
END_TEST

START_TEST(my_calc_complement_test_3) {
  matrix_t A;
  my_create_matrix(3, 3, &A);
  matrix_t B;
  my_create_matrix(3, 3, &B);
  matrix_t C;
  my_create_matrix(1, 1, &C);
  matrix_t D;
  my_create_matrix(1, 1, &D);

  D.matrix[0][0] = 1;
  C.matrix[0][0] = 5;

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  B.matrix[0][0] = 0;
  B.matrix[0][1] = 10;
  B.matrix[0][2] = -20;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = -14;
  B.matrix[1][2] = 8;
  B.matrix[2][0] = -8;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = 4;

  matrix_t RES;
  my_calc_complements(&A, &RES);
  ck_assert_msg(my_eq_matrix(&B, &RES), "TEST 1 FAIL");
  matrix_t RES1;
  my_calc_complements(&C, &RES1);
  ck_assert_msg(my_eq_matrix(&D, &RES1), "TEST 2 FAIL");
  my_remove_matrix(&RES);
  my_remove_matrix(&RES1);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  my_remove_matrix(&D);
}
END_TEST

START_TEST(test_sum) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C;

  int test = my_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  my_create_matrix(2, 3, &A);
  test = my_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);
  my_remove_matrix(&A);

  my_create_matrix(2, 3, &B);
  test = my_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);
  my_remove_matrix(&B);

  A = test_matrix(M_3x3, 3, 3);
  B = test_matrix(M_3x2, 3, 2);
  test = my_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(test, CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);

  A = test_matrix(M_3x3, 3, 3);
  B = test_matrix(M_3x3_math, 3, 3);
  test = my_sum_matrix(&A, &B, &C);
  double result[9] = {15.0, 17.0, -1.0, 3.250002, 8.97, 14.0, -6.9, 1.65, -6.0};
  matrix_t sum = test_matrix(result, 3, 3);
  int res = my_eq_matrix(&C, &sum);
  ck_assert_int_eq(test, CORRECT);
  ck_assert_int_eq(res, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  my_remove_matrix(&sum);
}
END_TEST

START_TEST(test_sub) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C;

  int test = my_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  my_create_matrix(2, 3, &A);
  test = my_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);
  my_remove_matrix(&A);

  my_create_matrix(2, 3, &B);
  test = my_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);
  my_remove_matrix(&B);

  A = test_matrix(M_3x3, 3, 3);
  B = test_matrix(M_3x2, 3, 2);
  test = my_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(test, CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);

  A = test_matrix(M_3x3, 3, 3);
  B = test_matrix(M_3x3_math, 3, 3);
  test = my_sub_matrix(&A, &B, &C);
  double result[9] = {-1.0, 13.0, 5.0, 3.249998, 0.03, 4.0, -7.5, -0.35, 6.0};
  matrix_t sub = test_matrix(result, 3, 3);
  int res = my_eq_matrix(&C, &sub);
  ck_assert_int_eq(test, CORRECT);
  ck_assert_int_eq(res, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  my_remove_matrix(&sub);
}
END_TEST

START_TEST(test_mult_number) {
  matrix_t A = {0};
  matrix_t B;

  int test = my_mult_number(&A, 3, &B);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  A = test_matrix(M_3x1, 3, 1);
  test = my_mult_number(&A, 5.0, &B);
  double result[3] = {21.0, 30.5, -25.0};
  matrix_t mul = test_matrix(result, 3, 1);
  int res = my_eq_matrix(&mul, &B);
  ck_assert_int_eq(test, CORRECT);
  ck_assert_int_eq(res, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&mul);
}
END_TEST

START_TEST(test_mult) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  int test = my_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  my_create_matrix(2, 3, &A);
  test = my_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);
  my_remove_matrix(&A);

  my_create_matrix(2, 3, &B);
  test = my_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);
  my_remove_matrix(&B);

  A = test_matrix(M_3x2, 3, 2);
  B = test_matrix(M_3x2, 3, 2);
  test = my_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(test, CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);

  A = test_matrix(M_3x3, 3, 3);
  B = test_matrix(M_3x1, 3, 1);
  test = my_mult_matrix(&A, &B, &C);
  double result[3] = {110.9, -3.9, -26.275};
  matrix_t mul = test_matrix(result, 3, 1);
  int res = my_eq_matrix(&mul, &C);
  ck_assert_int_eq(test, CORRECT);
  ck_assert_int_eq(res, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  my_remove_matrix(&mul);
}
END_TEST

START_TEST(test_transpose) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  int test = my_transpose(&A, &B);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  A = test_matrix(M_3x1, 3, 1);
  C = test_matrix(M_3x1, 1, 3);
  test = my_transpose(&A, &B);
  int res = my_eq_matrix(&B, &C);
  ck_assert_int_eq(test, CORRECT);
  ck_assert_int_eq(res, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
}
END_TEST

START_TEST(test_calc_complements) {
  matrix_t A = {0};
  matrix_t B;
  matrix_t C;

  int test = my_calc_complements(&A, &B);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  my_create_matrix(1, 3, &A);
  test = my_calc_complements(&A, &B);
  ck_assert_int_eq(test, CALCULATION_ERROR);
  my_remove_matrix(&A);

  A = test_matrix(M_1, 1, 1);
  test = my_calc_complements(&A, &B);
  ck_assert_int_eq(test, CORRECT);
  ck_assert_int_eq(B.matrix[0][0], 1);
  my_remove_matrix(&A);
  my_remove_matrix(&B);

  A = test_matrix(M_3x3, 3, 3);
  test = my_calc_complements(&A, &B);
  double result[9] = {-5.85,   -64.8, 34.5125, 1.3,   14.4,
                      -112.55, 126,   -56.5,   -17.25};
  C = test_matrix(result, 3, 3);
  int res = my_eq_matrix(&B, &C);
  ck_assert_int_eq(test, CORRECT);
  ck_assert_int_eq(res, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  int test = my_inverse_matrix(&A, &B);
  ck_assert_int_eq(test, UNCORRECT_MATRIX);

  my_create_matrix(1, 3, &A);
  test = my_inverse_matrix(&A, &B);
  ck_assert_int_eq(test, CALCULATION_ERROR);
  my_remove_matrix(&A);

  A = test_matrix(M_3x3_zero, 3, 3);
  test = my_inverse_matrix(&A, &B);
  // print_matrix(B);
  ck_assert_int_eq(test, CALCULATION_ERROR);
  my_remove_matrix(&A);

  A = test_matrix(M_1, 1, 1);
  test = my_inverse_matrix(&A, &B);
  ck_assert_int_eq(test, CORRECT);
  // printf("%lf\n", B.matrix[0][0]);
  // ck_assert_float_eq(B.matrix[0][0], 0.2);
  my_remove_matrix(&A);
  my_remove_matrix(&B);

  A = test_matrix(M_3x3_inverse, 3, 3);
  test = my_inverse_matrix(&A, &B);
  double result[9] = {1.0, -1.0, 1.0, -38.0, 41.0, -34.0, 27.0, -29.0, 24.0};
  C = test_matrix(result, 3, 3);
  int res = my_eq_matrix(&B, &C);
  ck_assert_int_eq(test, CORRECT);
  ck_assert_int_eq(res, SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
}
END_TEST

Suite *my_str_suite(void) {
  Suite *suite = suite_create("Matrix");
  TCase *tcase_core = tcase_create("Equelity");

  tcase_add_test(tcase_core, test_create);
  tcase_add_test(tcase_core, test_equal);
  tcase_add_test(tcase_core, test_sum);
  tcase_add_test(tcase_core, test_sub);
  tcase_add_test(tcase_core, test_mult_number);
  tcase_add_test(tcase_core, test_mult);
  tcase_add_test(tcase_core, test_transpose);
  tcase_add_test(tcase_core, test_calc_complements);
  tcase_add_test(tcase_core, test_inverse_2);

  tcase_add_test(tcase_core, my_calc_complement_test);
  tcase_add_test(tcase_core, my_calc_complement_test_2);
  tcase_add_test(tcase_core, my_calc_complement_test_3);
  tcase_add_test(tcase_core, my_create_matrix_test);
  tcase_add_test(tcase_core, my_create_matrix_test_2);
  tcase_add_test(tcase_core, my_create_matrix_test_3);
  tcase_add_test(tcase_core, my_create_matrix_test_4);
  tcase_add_test(tcase_core, my_eq_matrix_test);
  tcase_add_test(tcase_core, my_eq_matrix_test_2);
  tcase_add_test(tcase_core, my_eq_matrix_test_3);
  tcase_add_test(tcase_core, my_eq_matrix_test_4);
  tcase_add_test(tcase_core, my_eq_matrix_test_5);
  tcase_add_test(tcase_core, my_eq_matrix_test_6);
  tcase_add_test(tcase_core, my_sum_and_sub_matrix_test);
  tcase_add_test(tcase_core, my_sum_and_sub_matrix_test_2);
  tcase_add_test(tcase_core, my_sum_and_sub_matrix_test_3);
  tcase_add_test(tcase_core, my_sum_and_sub_matrix_test_4);
  tcase_add_test(tcase_core, my_sum_and_sub_matrix_test_5);
  tcase_add_test(tcase_core, my_mult_number_test);
  tcase_add_test(tcase_core, my_mult_number_test_2);
  tcase_add_test(tcase_core, my_mult_matrix_test);
  tcase_add_test(tcase_core, my_mult_matrix_test_2);
  tcase_add_test(tcase_core, my_transpose_test);
  tcase_add_test(tcase_core, my_determinant_test);
  tcase_add_test(tcase_core, my_determinant_test_2);
  tcase_add_test(tcase_core, my_calc_complements_test);
  tcase_add_test(tcase_core, my_inverse_matrix_test);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = my_str_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

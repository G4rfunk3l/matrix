#ifndef SRC_MY_MATRIX_H_
#define SRC_MY_MATRIX_H_

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CORRECT 0
#define UNCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

#define FAIL 0
#define SUCCESS 1

#define ACCURACY (double)1e-07

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int my_create_matrix(int rows, int columns, matrix_t *result);
void my_remove_matrix(matrix_t *A);
int my_eq_matrix(matrix_t *A, matrix_t *B);
int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_mult_number(matrix_t *A, double number, matrix_t *result);
int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_transpose(matrix_t *A, matrix_t *result);
int my_calc_complements(matrix_t *A, matrix_t *result);
int my_determinant(matrix_t *A, double *result);
int my_inverse_matrix(matrix_t *A, matrix_t *result);

int is_matrix_correct(matrix_t *A);
int is_matrix_square(matrix_t *A);
void get_minor(matrix_t *minor, matrix_t *A, int row, int column);
matrix_t initial_matrix();

#endif  // SRC_MY_MATRIX_H_
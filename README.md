# matrix.h
My own realization of matrix data type (using C language) for Mac and Linux. 
For build static library do make all, for tests do make test.
Usage of library like in tests.c.
## Realized features
A matrix is a collection of numbers arranged into a fixed number of rows and columns.
## Realized functions
### int my_create_matrix(int rows, int columns, matrix_t *result)
Creating matrices
### void my_remove_matrix(matrix_t *A)
Cleaning of matrices
### int my_eq_matrix(matrix_t *A, matrix_t *B)
Matrix comparison
- 0 - FAILURE
- 1 - SUCCESS
### int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
Adding matrices
### int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
Subtracting matrices
### int my_mult_number(matrix_t *A, double number, matrix_t *result);
Matrix multiplication by scalar
### int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
Multiplication of two matrices
### int my_transpose(matrix_t *A, matrix_t *result)
Matrix transpose
### int my_calc_complements(matrix_t *A, matrix_t *result)
Matrix of algebraic complements
### int my_determinant(matrix_t *A, double *result)
Matrix determinant
### int my_inverse_matrix(matrix_t *A, matrix_t *result)
Inverse of the matrix
### The functions return value:
All operations (except matrix comparison) should return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)
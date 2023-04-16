#include "my_matrix.h"

int my_create_matrix(int rows, int columns, matrix_t *result) {
  /* Функция создания матрицы с заданными значениями rows и columns */
  errno = UNCORRECT_MATRIX;
  *result = initial_matrix();
  if (rows > 0 && columns > 0) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int row = 0; row < rows; row++) {
      result->matrix[row] = (double *)calloc(columns, sizeof(double));
    }
    if (result->matrix != NULL) {
      result->rows = rows;
      result->columns = columns;
      errno = CORRECT;
    }
  }
  return errno;
}

void my_remove_matrix(matrix_t *A) {
  /* Функция очистки матрицы */
  if (A->matrix) {
    for (int row = 0; row < A->rows; row++) {
      free(A->matrix[row]);
    }
    free(A->matrix);
    *A = initial_matrix();
  }
}

int my_eq_matrix(matrix_t *A, matrix_t *B) {
  /* Функция проверки эквивалентности матриц */
  int result = FAIL;
  int existence_matrix = 0;

  if (!is_matrix_correct(A) || !is_matrix_correct(B)) {
    existence_matrix = 1;
  }
  if (existence_matrix && A->rows == B->rows && A->columns == B->columns) {
    result = SUCCESS;
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < A->columns; column++) {
        if (fabs(A->matrix[row][column] - B->matrix[row][column]) >= ACCURACY) {
          result = FAIL;
          break;
        }
      }
      if (!result) break;
    }
  }
  return result;
}

int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  /* Функция сложения матриц одного размера */
  errno = CORRECT;
  *result = initial_matrix();
  if (is_matrix_correct(A) || is_matrix_correct(B)) {
    errno = UNCORRECT_MATRIX;
  }
  if (!errno && A->rows == B->rows && A->columns == B->columns) {
    my_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row < result->rows; row++) {
      for (int column = 0; column < result->columns; column++) {
        result->matrix[row][column] =
            A->matrix[row][column] + B->matrix[row][column];
      }
    }
  } else if (errno != UNCORRECT_MATRIX) {
    errno = CALCULATION_ERROR;
  }
  return errno;
}

int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  /* Функция вычитания матриц одного размера */
  errno = CORRECT;
  *result = initial_matrix();
  if (is_matrix_correct(A) || is_matrix_correct(B)) {
    errno = UNCORRECT_MATRIX;
  }
  if (!errno && A->rows == B->rows && A->columns == B->columns) {
    my_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row < result->rows; row++) {
      for (int column = 0; column < result->columns; column++) {
        result->matrix[row][column] =
            A->matrix[row][column] - B->matrix[row][column];
      }
    }
  } else if (errno != UNCORRECT_MATRIX) {
    errno = CALCULATION_ERROR;
  }
  return errno;
}

int my_mult_number(matrix_t *A, double number, matrix_t *result) {
  /* Функция умножения матрицы на число */
  errno = CORRECT;
  *result = initial_matrix();
  if (!(errno = is_matrix_correct(A))) {
    my_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row < result->rows; row++) {
      for (int column = 0; column < result->columns; column++) {
        result->matrix[row][column] = A->matrix[row][column] * number;
      }
    }
  }
  return errno;
}

int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  /* Функция умножения матрицы на матрицу */
  errno = CORRECT;
  *result = initial_matrix();
  if (is_matrix_correct(A) || is_matrix_correct(B)) {
    errno = UNCORRECT_MATRIX;
  }
  if (!errno && A->columns == B->rows) {
    my_create_matrix(A->rows, B->columns, result);
    for (int row = 0; row < result->rows; row++) {
      for (int column = 0; column < result->columns; column++) {
        for (int count = 0; count < A->columns; count++) {
          result->matrix[row][column] +=
              A->matrix[row][count] * B->matrix[count][column];
        }
      }
    }
  } else if (errno != UNCORRECT_MATRIX) {
    errno = CALCULATION_ERROR;
  }
  return errno;
}

int my_transpose(matrix_t *A, matrix_t *result) {
  /* Функция транспонирования матрицы */
  errno = CORRECT;
  if (!(errno = is_matrix_correct(A))) {
    my_create_matrix(A->columns, A->rows, result);
    for (int row = 0; row < result->rows; row++) {
      for (int column = 0; column < result->columns; column++) {
        result->matrix[row][column] = A->matrix[column][row];
      }
    }
  }
  return errno;
}

int my_calc_complements(matrix_t *A, matrix_t *result) {
  /* Функция вычисления матрицы алгебраических дополнений */
  errno = CORRECT;
  *result = initial_matrix();
  if (!(errno = is_matrix_square(A))) {
    my_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1) {
      result->matrix[0][0] = 1.0;
    } else {
      matrix_t minor = initial_matrix();
      double determinant = 0;
      if (!(errno = my_create_matrix(A->rows - 1, A->columns - 1, &minor))) {
        for (int row = 0; row < A->rows; row++) {
          for (int column = 0; column < A->columns; column++) {
            get_minor(&minor, A, row, column);
            my_determinant(&minor, &determinant);
            result->matrix[row][column] =
                determinant * (((row + column) % 2) ? -1 : 1);
          }
        }
      }
      my_remove_matrix(&minor);
    }
  }
  return errno;
}

int my_determinant(matrix_t *A, double *result) {
  /* Функция вычисления определителя матрицы */
  errno = CORRECT;
  *result = 0;
  if (!(errno = is_matrix_square(A))) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else {
      matrix_t algebraic_additions = initial_matrix();
      if (!(errno = my_calc_complements(A, &algebraic_additions))) {
        for (int column = 0; column < A->columns; column++) {
          *result +=
              A->matrix[column][0] * algebraic_additions.matrix[column][0];
        }
      }
      my_remove_matrix(&algebraic_additions);
    }
  } else {
    *result = NAN;
  }
  return errno;
}

int my_inverse_matrix(matrix_t *A, matrix_t *result) {
  /* Функция вычисления обратной матрицы */
  errno = CORRECT;
  double determinant = 0;
  matrix_t algebraic_additions = initial_matrix();
  matrix_t transpose = initial_matrix();
  *result = initial_matrix();
  if (!errno) {
    errno = my_determinant(A, &determinant);
  }
  if (!errno && !determinant) {
    errno = CALCULATION_ERROR;
  }
  if (!errno) {
    errno = my_calc_complements(A, &algebraic_additions);
  }
  if (!errno) {
    errno = my_transpose(&algebraic_additions, &transpose);
  }
  if (!errno) {
    errno = my_mult_number(&transpose, 1.0 / determinant, result);
  }
  my_remove_matrix(&algebraic_additions);
  my_remove_matrix(&transpose);
  return errno;
}

// Служебные функции

int is_matrix_correct(matrix_t *A) {
  errno = CORRECT;
  if (!A || !A->matrix || A->columns <= 0 || A->rows <= 0) {
    errno = UNCORRECT_MATRIX;
  }
  return errno;
}

int is_matrix_square(matrix_t *A) {
  errno = is_matrix_correct(A);
  if (!errno && !(A->rows == A->columns)) {
    errno = CALCULATION_ERROR;
  }
  return errno;
}

void get_minor(matrix_t *minor, matrix_t *A, int row, int column) {
  int row_minor = 0;
  for (int row_A = 0; row_A < A->rows; row_A++) {
    if (row_A != row) {
      int column_minor = 0;
      for (int column_A = 0; column_A < A->columns; column_A++) {
        if (column_A != column) {
          minor->matrix[row_minor][column_minor++] = A->matrix[row_A][column_A];
        }
      }
      row_minor++;
    }
  }
}

matrix_t initial_matrix() {
  matrix_t res = {NULL, 0, 0};
  return res;
}

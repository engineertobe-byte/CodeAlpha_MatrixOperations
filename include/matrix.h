#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_MAX_ROWS 8
#define MATRIX_MAX_COLS 8

typedef struct {
    int rows;
    int cols;
    float data[MATRIX_MAX_ROWS][MATRIX_MAX_COLS];
} Matrix;

/* CodeAlpha Task 2 core operations */
int matrix_add(const Matrix *a, const Matrix *b, Matrix *out);
int matrix_multiply(const Matrix *a, const Matrix *b, Matrix *out);
int matrix_transpose(const Matrix *a, Matrix *out);

/* Numerical primitives reused by the embedded AI engine */
float vector_dot(const float *a, const float *b, int n);
void vector_relu(float *v, int n);

/* Utilities */
void matrix_print(const Matrix *m, const char *name);
int matrix_read(Matrix *m, const char *name);

#endif

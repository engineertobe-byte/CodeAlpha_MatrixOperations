#include <stdio.h>
#include "matrix.h"

int matrix_add(const Matrix *a, const Matrix *b, Matrix *out)
{
    if (a == NULL || b == NULL || out == NULL) return -1;
    if (a->rows != b->rows || a->cols != b->cols) return -1;

    out->rows = a->rows;
    out->cols = a->cols;

    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
            out->data[i][j] = a->data[i][j] + b->data[i][j];

    return 0;
}

int matrix_multiply(const Matrix *a, const Matrix *b, Matrix *out)
{
    if (a == NULL || b == NULL || out == NULL) return -1;
    if (a->cols != b->rows) return -1;
    if (a->rows > MATRIX_MAX_ROWS || b->cols > MATRIX_MAX_COLS) return -1;

    out->rows = a->rows;
    out->cols = b->cols;

    for (int i = 0; i < out->rows; i++) {
        for (int j = 0; j < out->cols; j++) {
            float sum = 0.0f;
            for (int k = 0; k < a->cols; k++)
                sum += a->data[i][k] * b->data[k][j];
            out->data[i][j] = sum;
        }
    }

    return 0;
}

int matrix_transpose(const Matrix *a, Matrix *out)
{
    if (a == NULL || out == NULL) return -1;
    if (a->cols > MATRIX_MAX_ROWS || a->rows > MATRIX_MAX_COLS) return -1;

    out->rows = a->cols;
    out->cols = a->rows;

    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
            out->data[j][i] = a->data[i][j];

    return 0;
}

float vector_dot(const float *a, const float *b, int n)
{
    if (a == NULL || b == NULL || n <= 0) return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < n; i++)
        sum += a[i] * b[i];
    return sum;
}

void vector_relu(float *v, int n)
{
    if (v == NULL || n <= 0) return;
    for (int i = 0; i < n; i++)
        if (v[i] < 0.0f) v[i] = 0.0f;
}

void matrix_print(const Matrix *m, const char *name)
{
    if (m == NULL || name == NULL) return;

    printf("%s (%dx%d):\n", name, m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        printf("  [");
        for (int j = 0; j < m->cols; j++) {
            printf("%8.2f", m->data[i][j]);
            if (j + 1 < m->cols) printf(",");
        }
        printf(" ]\n");
    }
    printf("\n");
}

int matrix_read(Matrix *m, const char *name)
{
    if (m == NULL || name == NULL) return -1;

    printf("Enter rows and cols for %s (max %d): ", name, MATRIX_MAX_ROWS);
    if (scanf("%d %d", &m->rows, &m->cols) != 2) return -1;
    if (m->rows <= 0 || m->cols <= 0 ||
        m->rows > MATRIX_MAX_ROWS || m->cols > MATRIX_MAX_COLS) return -1;

    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++) {
            printf("%s[%d][%d] = ", name, i, j);
            if (scanf("%f", &m->data[i][j]) != 1) return -1;
        }

    return 0;
}

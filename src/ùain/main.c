#include <stdio.h>
#include "matrix.h"
#include "inference.h"

static float clamp01(float x)
{
    if (x < 0.0f) return 0.0f;
    if (x > 1.0f) return 1.0f;
    return x;
}

static void print_menu(void)
{
    printf("\n==========================================================\n");
    printf(" CodeAlpha - Matrix Operations + Embedded Islamic-Bank AI\n");
    printf("==========================================================\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");
    printf("4. Sharia-Compliant Eligibility Inference - Demo (3 applicants)\n");
    printf("5. Sharia-Compliant Eligibility Inference - Interactive\n");
    printf("6. Quick Matrix Demo\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

static void interactive_inference(void)
{
    float input[AI_INPUT_SIZE];

    printf("\nEnter the 4 halal features (values in [0,1]):\n");
    printf("  normalized_income              = "); scanf("%f", &input[0]);
    printf("  debt_to_income_ratio (no riba) = "); scanf("%f", &input[1]);
    printf("  employment_stability_score     = "); scanf("%f", &input[2]);
    printf("  ethical_payment_history_score  = "); scanf("%f", &input[3]);

    for (int i = 0; i < AI_INPUT_SIZE; i++)
        input[i] = clamp01(input[i]);

    printf("\nRunning embedded inference...\n");
    sharia_inference(input);
}

static void demo_matrix_operations(void)
{
    Matrix a = { 2, 3, { {1,2,3}, {4,5,6} } };
    Matrix b = { 2, 3, { {7,8,9}, {10,11,12} } };
    Matrix c = { 3, 2, { {1,2}, {3,4}, {5,6} } };
    Matrix out;

    matrix_print(&a, "A");
    matrix_print(&b, "B");
    matrix_print(&c, "C");

    if (matrix_add(&a, &b, &out) == 0)        matrix_print(&out, "A + B");
    if (matrix_multiply(&a, &c, &out) == 0)   matrix_print(&out, "A * C");
    if (matrix_transpose(&a, &out) == 0)      matrix_print(&out, "Transpose(A)");

    float v1[3] = {1, 2, 3};
    float v2[3] = {4, 5, 6};
    printf("Dot product v1 . v2 = %.2f\n\n", vector_dot(v1, v2, 3));
}

int main(void)
{
    int choice;

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n') {}
            continue;
        }

        if (choice == 0) { printf("Exiting.\n"); break; }

        switch (choice) {
        case 1: {
            Matrix a, b, out;
            printf("\n--- Matrix Addition ---\n");
            if (matrix_read(&a, "A") != 0 || matrix_read(&b, "B") != 0) {
                printf("Invalid input.\n"); break;
            }
            if (matrix_add(&a, &b, &out) == 0) matrix_print(&out, "A + B");
            else printf("Dimensions must match.\n");
            break;
        }
        case 2: {
            Matrix a, b, out;
            printf("\n--- Matrix Multiplication ---\n");
            if (matrix_read(&a, "A") != 0 || matrix_read(&b, "B") != 0) {
                printf("Invalid input.\n"); break;
            }
            if (matrix_multiply(&a, &b, &out) == 0) matrix_print(&out, "A * B");
            else printf("cols(A) must equal rows(B).\n");
            break;
        }
        case 3: {
            Matrix a, out;
            printf("\n--- Matrix Transpose ---\n");
            if (matrix_read(&a, "A") != 0) { printf("Invalid input.\n"); break; }
            if (matrix_transpose(&a, &out) == 0) matrix_print(&out, "Transpose(A)");
            else printf("Transpose failed.\n");
            break;
        }
        case 4:
            printf("\n");
            sharia_inference_demo();
            break;
        case 5:
            interactive_inference();
            break;
        case 6:
            printf("\n--- Quick Matrix Demo ---\n\n");
            demo_matrix_operations();
            break;
        default:
            printf("Invalid option.\n");
            break;
        }
    }

    return 0;
}

#include <stdio.h>
#include "inference.h"
#include "matrix.h"

/*
    Embedded Sharia-compliant eligibility engine.

    Architecture:
        hidden = ReLU(W1 * input + b1)     (W1 = identity -> hidden = input for input >= 0)
        output = W2 * hidden + b2
        decision = argmax(output)

    The output layer encodes three ETHICAL PROFILE TEMPLATES, so the network acts as a
    nearest-template linear classifier built only from matrix-vector products + ReLU.
    These weights are placeholders standing in for a model trained in Python
    (Week 1: Halal Credit Scoring) and exported to C for edge deployment.

    NO INTEREST (riba) is computed anywhere.
*/

/* W1 = identity (4x4) */
static const float W1[AI_HIDDEN_SIZE][AI_INPUT_SIZE] = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};
static const float B1[AI_HIDDEN_SIZE] = { 0.0f, 0.0f, 0.0f, 0.0f };

/* W2 = ethical profile templates (rows = classes, cols = features)
   feature order: [income, debt_ratio_no_riba, stability, ethical_history] */
static const float W2[AI_OUTPUT_SIZE][AI_HIDDEN_SIZE] = {
    { 0.9f, 0.1f, 0.9f, 0.9f },   /* class 0: strong profile  -> Murabaha / Ijara */
    { 0.5f, 0.5f, 0.5f, 0.5f },   /* class 1: borderline      -> manual review     */
    { 0.2f, 0.8f, 0.3f, 0.2f }    /* class 2: high-risk       -> Qard Hasan only   */
};
/* b2 = -0.5 * ||template||^2  (nearest-template bias) */
static const float B2[AI_OUTPUT_SIZE] = { -0.82f, -0.50f, -0.405f };

static const char *LABELS[AI_OUTPUT_SIZE] = {
    "ELIGIBLE: Murabaha / Ijara (fixed-margin sale or lease, NO interest)",
    "REVIEW REQUIRED: manual Sharia-compliance check",
    "QARD HASAN ONLY: benevolent interest-free loan"
};

const char *sharia_label(int idx)
{
    if (idx < 0 || idx >= AI_OUTPUT_SIZE) return "UNKNOWN";
    return LABELS[idx];
}

static void print_vector(const float *v, int n, const char *name)
{
    printf("  %-22s [", name);
    for (int i = 0; i < n; i++) {
        printf("%.2f", v[i]);
        if (i + 1 < n) printf(", ");
    }
    printf("]\n");
}

int sharia_inference(const float input[AI_INPUT_SIZE])
{
    float hidden[AI_HIDDEN_SIZE] = { 0.0f };
    float output[AI_OUTPUT_SIZE] = { 0.0f };

    /* hidden = ReLU(W1 * input + b1)  -> matrix-vector product */
    for (int i = 0; i < AI_HIDDEN_SIZE; i++) {
        float sum = B1[i];
        for (int j = 0; j < AI_INPUT_SIZE; j++)
            sum += W1[i][j] * input[j];
        hidden[i] = sum;
    }
    vector_relu(hidden, AI_HIDDEN_SIZE);

    /* output = W2 * hidden + b2  -> matrix-vector product */
    for (int i = 0; i < AI_OUTPUT_SIZE; i++) {
        float sum = B2[i];
        for (int j = 0; j < AI_HIDDEN_SIZE; j++)
            sum += W2[i][j] * hidden[j];
        output[i] = sum;
    }

    /* decision = argmax  (no softmax needed for a prototype) */
    int predicted = 0;
    for (int i = 1; i < AI_OUTPUT_SIZE; i++)
        if (output[i] > output[predicted]) predicted = i;

    print_vector(input, AI_INPUT_SIZE, "halal features");
    print_vector(hidden, AI_HIDDEN_SIZE, "hidden (after ReLU)");
    print_vector(output, AI_OUTPUT_SIZE, "output logits");
    printf("  => DECISION: [%d] %s\n\n", predicted, sharia_label(predicted));

    return predicted;
}

void sharia_inference_demo(void)
{
    /* Three illustrative applicants (values normalized in [0,1]). */
    float applicant_A[AI_INPUT_SIZE] = { 0.9f, 0.1f, 0.9f, 0.9f }; /* strong     */
    float applicant_B[AI_INPUT_SIZE] = { 0.5f, 0.5f, 0.5f, 0.5f }; /* borderline */
    float applicant_C[AI_INPUT_SIZE] = { 0.2f, 0.8f, 0.3f, 0.2f }; /* high-risk  */

    printf("Embedded Sharia-Compliant Eligibility Engine (C, no ML lib)\n");
    printf("==========================================================\n");
    printf("Features = [income, debt_ratio(no riba), stability, ethical_history]\n\n");

    printf("Applicant A (strong profile):\n");
    sharia_inference(applicant_A);

    printf("Applicant B (borderline profile):\n");
    sharia_inference(applicant_B);

    printf("Applicant C (high-risk profile):\n");
    sharia_inference(applicant_C);

    printf("Note: software-only edge prototype. No interest is computed.\n");
    printf("Weights are placeholders for a Python-trained model (Week 1).\n\n");
}

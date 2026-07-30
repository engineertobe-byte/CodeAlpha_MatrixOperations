# CodeAlpha - Matrix Operations → Embedded Sharia-Compliant Inference Engine

This project implements **C Programming Task 2: Matrix Operations** and extends it
into a **software prototype of Embedded AI applied to Islamic Banking**.

The matrix operations required by the task (addition, multiplication, transpose) are
the exact numerical primitives used inside neural networks. This project reuses them
to run a tiny inference engine **in pure C, with no ML library**, simulating what would
later be deployed on a constrained edge device inside an Islamic bank branch.

## Use case: Sharia-compliant credit eligibility on the edge

Given 4 halal (riba-free) applicant features, the embedded engine predicts one of
three **interest-free** decisions:

| Class | Decision | Meaning |
|-------|----------|---------|
| 0 | `ELIGIBLE_MURABAHA_IJARA` | Eligible for a fixed-margin sale (Murabaha) or lease (Ijara). **No interest.** |
| 1 | `REVIEW_REQUIRED` | Manual Sharia-compliance review (precaution principle). |
| 2 | `QARD_HASAN_ONLY` | Eligible only for a benevolent interest-free loan (Qard Hasan). |

### Input features (all riba-free)
- `normalized_income`
- `debt_to_income_ratio_no_riba` (existing debts **excluding** any interest)
- `employment_stability_score`
- `ethical_payment_history_score`

> The model never computes, stores, or outputs an interest rate. It only assesses
> repayment capacity — which aligns with the Islamic principle of avoiding
> over-indebtedness.

## Why matrix operations = the heart of embedded AI

A linear layer is `y = W * x + b`. This project implements exactly that in C:

```text
hidden = ReLU(W1 * input + b1)
output = W2 * hidden + b2
decision = argmax(output)
```

The output weights encode three **ethical profile templates**, so the network behaves
as a nearest-template classifier built only from matrix-vector products and a ReLU.
In production these weights would be **trained in Python (see Week 1: Halal Credit
Scoring) and exported to C** for edge deployment. This project is the deployment side.

## Link with Week 1 (not a repetition)
- **Week 1 (Python / scikit-learn):** supervised *training* of a halal credit model.
- **Week 2 (C):** library-free *inference* of the same kind of decision, on a
  constrained target. Training vs. deployment = two different skills.

## Features

### Core C Task 2
- Matrix Addition
- Matrix Multiplication
- Matrix Transpose
- Modular functions + 2D arrays

### Embedded AI extension
- Vector dot product
- Matrix-vector product (linear layer)
- ReLU activation
- Argmax decision
- Interactive halal-feature input
- 3-applicant demo (eligible / review / qard-hasan)

## Project Structure

```bash
CodeAlpha_MatrixOperations/
├── README.md
├── Makefile
├── .gitignore
├── include/
│   ├── matrix.h
│   └── inference.h
├── src/
│   ├── main.c
│   ├── matrix.c
│   └── inference.c
└── outputs/
```

## Build

### Linux / macOS
```bash
make
./matrix_ai_prototype
```

### Windows (MinGW)
```bash
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/matrix.c src/inference.c -o matrix_ai_prototype.exe
matrix_ai_prototype.exe
```

## Menu
1. Matrix Addition
2. Matrix Multiplication
3. Matrix Transpose
4. Sharia-Compliant Eligibility Inference — Demo (3 applicants)
5. Sharia-Compliant Eligibility Inference — Interactive
6. Quick Matrix Demo
0. Exit

## Sharia-compliance guarantees
- No interest (riba) computed anywhere.
- Fixed-margin contracts (Murabaha/Ijara) and benevolent loan (Qard Hasan) only.
- Local inference: applicant data never leaves the device (privacy / sovereignty).
- Repayment-capacity assessment = anti-over-indebtedness principle.

## Task Completion Checklist
- [x] Matrix Addition
- [x] Matrix Multiplication
- [x] Matrix Transpose
- [x] Functions for modularity
- [x] 2D arrays
- [x] Extended into an embedded-AI inference prototype for Islamic banking

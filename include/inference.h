#ifndef INFERENCE_H
#define INFERENCE_H

#define AI_INPUT_SIZE  4   /* halal features */
#define AI_HIDDEN_SIZE 4
#define AI_OUTPUT_SIZE 3   /* eligible / review / qard-hasan */

/*
    Runs the embedded inference on a single halal feature vector.
    Prints the forward pass and returns the predicted class index.
*/
int sharia_inference(const float input[AI_INPUT_SIZE]);

/* Runs the 3-applicant demonstration. */
void sharia_inference_demo(void);

/* Human-readable label for a class index. */
const char *sharia_label(int idx);

#endif

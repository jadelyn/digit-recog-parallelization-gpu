/*
 * Proj 3-2 SKELETON
 */

#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <cuda_runtime.h>
#include <cutil.h>
#include "utils.h"

/* Does a horizontal flip of the array arr */
void flip_horizontal(float *arr, int width) {
    /* YOU MAY WISH TO IMPLEMENT THIS */

}

/* Transposes the square array ARR. */
void transpose(float *arr, int width) {
    /* YOU MAY WISH TO IMPLEMENT THIS */

}

/* Rotates the square array ARR by 90 degrees counterclockwise. */
void rotate_ccw_90(float *arr, int width) {
    /* YOU MAY WISH TO IMPLEMENT THIS */

}

/* Returns the squared Euclidean distance between TEMPLATE and IMAGE. The size of IMAGE
 * is I_WIDTH * I_HEIGHT, while TEMPLATE is square with side length T_WIDTH. The template
 * image should be flipped, rotated, and translated across IMAGE.
 */
float calc_min_dist(float *image, int i_width, int i_height, float *temp, int t_width) {
    // float* image and float* temp are pointers to GPU addressible memory
    // You MAY NOT copy this data back to CPU addressible memory and you MAY 
    // NOT perform any computation using values from image or temp on the CPU.

    /* YOUR CODE HERE */

    return 0;
}

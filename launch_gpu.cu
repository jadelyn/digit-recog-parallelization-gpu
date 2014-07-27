// launch the gpu computation

#include<cuda_runtime.h>
#include<cutil.h>
#include<sys/time.h>
#include<time.h>
#include "launch_gpu.h"

extern "C" float* launch_gpu_computation(float *image, int i_width, int i_height, float *temp, int t_width) {
    float* gpu_image;
    cudaMalloc(&gpu_image, sizeof(float)*i_width*i_height);
    cudaMemcpy(gpu_image, image, i_width*i_height*sizeof(float), cudaMemcpyHostToDevice);

    float* gpu_temp;
    cudaMalloc(&gpu_temp, sizeof(float)*t_width*t_width);
    cudaMemcpy(gpu_temp, temp, t_width*t_width*sizeof(float), cudaMemcpyHostToDevice);

    double seconds;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    float distance_computed = calc_min_dist(gpu_image, i_width, i_height, gpu_temp, t_width);
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);

    cudaFree(gpu_image);
    cudaFree(gpu_temp);

    float* retVal = (float*)malloc(sizeof(float)*2);
    retVal[0] = (float)seconds;
    retVal[1] = distance_computed;
    return retVal;
}


extern "C" float just_get_dist_gpu(float *image, int i_width, int i_height, float *temp, int t_width) {
    float* res;
    res = launch_gpu_computation(image, i_width, i_height, temp, t_width);
    float retVal = res[1];
    free(res);
    return retVal;
}

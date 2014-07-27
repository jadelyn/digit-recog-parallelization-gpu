/* CS61C Sp14 Project 3
 *
 * ANY MODIFICATIONS TO THIS FILE WILL BE OVERWRITTEN DURING GRADING
 */

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "digit_rec.h"

int main(int argc, char **argv) {
    printf("################################################################################\n");
    printf("# WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! #\n");
    printf("# Running ./digit_rec will fail in part 2 since we only require support for    #\n");
    printf("# templates with power-of-two sizes                                            #\n");
    printf("# Please use one of the other methods to test your code.                       #\n");
    printf("################################################################################\n");
    if ( argc != 2 ) {
        test_basic();
    } else {
        test_bmp(argv[1]);
    }
    return 0;
}

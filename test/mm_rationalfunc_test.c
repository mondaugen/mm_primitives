#include <stdlib.h> 
#include <stdio.h>

#define MMRationalFunc_ArgType double 

#include "mm_rationalfunc.h" 

int main (int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr,"Arguments are m and b.\n");
        return(-1);
    }
    MMLineFunc2D lf;
    MMLineFunc2D_init(&lf);
    lf.m = atof(argv[1]);
    lf.b = atof(argv[2]);
    double x;
    for (x = -1; x <= 1; x += 0.1) {
        printf("%f\n", MMRationalFunc_eval(&lf,x));
    }
    return(0);
}


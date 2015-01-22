/* A vectorized version of rational functions */
#include "mm_rationalfunc_v.h" 

void MMLineFunc2DV_eval(MMRationalFuncV *lf, MMRationalFuncV_ArgType * x, MMRationalFuncV_ArgType * result,
        size_t length)
{
    size_t i;
    for (i = 0; i < length; i++) {
        result[i] = ((MMLineFunc2DV*)lf)->m * x[i] + ((MMLineFunc2DV*)lf)->b;
    }
}

void MMLineFunc2DV_init(MMLineFunc2DV *lf)
{
    ((MMRationalFuncV*)lf)->eval = MMLineFunc2DV_eval;
}

/* Initialize slope and yintercept */
void MMLineFunc2DV_set_mb(MMLineFunc2DV *lf, MMRationalFuncV_ArgType m,
        MMRationalFuncV_ArgType b)
{
    lf->m = m;
    lf->b = b;
}

/* Initialize slope and yintercept from two points (x0,y0) and (x1,y1). Leaves
 * the MMLineFunc2DV untouched if x0 == x1 */
void MMLineFunc2DV_set_points(MMLineFunc2DV *lf,
        MMRationalFuncV_ArgType x0, MMRationalFuncV_ArgType y0,
        MMRationalFuncV_ArgType x1, MMRationalFuncV_ArgType y1)
{
    if (x0 != x1) {
        MMLineFunc2DV_set_mb(lf, (y1 - y0) / (x1 - x0), y0 - x0 * (y1 - y0) / (x1 - x0));
    }
}

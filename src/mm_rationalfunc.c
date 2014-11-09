#include "mm_rationalfunc.h" 

MMRationalFunc_ArgType MMLineFunc2D_eval(MMRationalFunc *lf, MMRationalFunc_ArgType x)
{
    return ((MMLineFunc2D*)lf)->m * x + ((MMLineFunc2D*)lf)->b; 
}

void MMLineFunc2D_init(MMLineFunc2D *lf)
{
    ((MMRationalFunc*)lf)->eval = MMLineFunc2D_eval;
}

/* Initialize slope and yintercept */
void MMLineFunc2D_set_mb(MMLineFunc2D *lf, MMRationalFunc_ArgType m,
        MMRationalFunc_ArgType b)
{
    lf->m = m;
    lf->b = b;
}

/* Initialize slope and yintercept from two points (x0,y0) and (x1,y1). Leaves
 * the MMLineFunc2D untouched if x0 == x1 */
void MMLineFunc2D_set_points(MMLineFunc2D *lf,
        MMRationalFunc_ArgType x0, MMRationalFunc_ArgType y0,
        MMRationalFunc_ArgType x1, MMRationalFunc_ArgType y1,
        )
{
    if (x0 != x1) {
        MMLineFunc2D_set_mb(lf, (y1 - y0) / (x1 - x0), y0 - x0 * (y1 - y0) / (x1 - x0));
    }
}

#ifndef MM_RATIONALFUNC_V_H
#define MM_RATIONALFUNC_V_H 

#include <stddef.h> 

#ifndef MMRationalFuncV_ArgType
 #define  MMRationalFuncV_ArgType float 
#endif  

typedef struct __MMRationalFuncV MMRationalFuncV;

struct __MMRationalFuncV {
    void (*eval)(MMRationalFuncV *, MMRationalFuncV_ArgType *, MMRationalFuncV_ArgType *, size_t length);
};

#define MMRationalFuncV_eval(f,x,r,l) ((MMRationalFuncV*)f)->eval((MMRationalFuncV*)f,x,r,l)

typedef struct __MMLineFunc2DV MMLineFunc2DV;

/* y = m*x + b */
struct __MMLineFunc2DV {
    MMRationalFuncV head;
    MMRationalFuncV_ArgType m;
    MMRationalFuncV_ArgType b;
};

void MMLineFunc2DV_eval(MMRationalFuncV *lf, MMRationalFuncV_ArgType * x, MMRationalFuncV_ArgType * result,
        size_t length);
void MMLineFunc2DV_init(MMLineFunc2DV *lf);
void MMLineFunc2DV_set_mb(MMLineFunc2DV *lf, MMRationalFuncV_ArgType m,
        MMRationalFuncV_ArgType b);
void MMLineFunc2DV_set_points(MMLineFunc2DV *lf,
        MMRationalFuncV_ArgType x0, MMRationalFuncV_ArgType y0,
        MMRationalFuncV_ArgType x1, MMRationalFuncV_ArgType y1);


#endif /* MM_RATIONALFUNC_V_H */

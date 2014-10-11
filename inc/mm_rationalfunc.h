#ifndef MM_RATIONALFUNC_H
#define MM_RATIONALFUNC_H 

#ifndef MMRationalFunc_ArgType
 #define  MMRationalFunc_ArgType float 
#endif  

typedef struct __MMRationalFunc MMRationalFunc;

struct __MMRationalFunc {
    MMRationalFunc_ArgType (*eval)(MMRationalFunc *, MMRationalFunc_ArgType);
};

#define MMRationalFunc_eval(f,x) ((MMRationalFunc*)f)->eval((MMRationalFunc*)f,x)

typedef struct __MMLineFunc2D MMLineFunc2D;

/* y = m*x + b */
struct __MMLineFunc2D {
    MMRationalFunc head;
    double m;
    double b;
};

static MMRationalFunc_ArgType MMLineFunc2D_eval(MMRationalFunc *lf, MMRationalFunc_ArgType x)
{
    return ((MMLineFunc2D*)lf)->m * x + ((MMLineFunc2D*)lf)->b; 
}

static inline void MMLineFunc2D_init(MMLineFunc2D *lf)
{
    ((MMRationalFunc*)lf)->eval = MMLineFunc2D_eval;
}

#endif /* MM_RATIONALFUNC_H */

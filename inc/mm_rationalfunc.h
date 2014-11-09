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

MMRationalFunc_ArgType MMLineFunc2D_eval(MMRationalFunc *lf, MMRationalFunc_ArgType x);
void MMLineFunc2D_init(MMLineFunc2D *lf);
void MMLineFunc2D_set_mb(MMLineFunc2D *lf, MMRationalFunc_ArgType m,
        MMRationalFunc_ArgType b);
void MMLineFunc2D_set_points(MMLineFunc2D *lf,
        MMRationalFunc_ArgType x0, MMRationalFunc_ArgType y0,
        MMRationalFunc_ArgType x1, MMRationalFunc_ArgType y1);


#endif /* MM_RATIONALFUNC_H */

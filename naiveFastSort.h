#ifndef NAIVEFASTSORT_H
#define NAIVEFASTSORT_H

/*
 * Based on Bentley & Sedgewick's algorithm on p.5 of their paper
 * " Fast Algorithm for sorting and searching strings".
 * The algorithm has benn extended.
 */

#include <time.h> // time
#include <stdlib.h> // srand, rand
// srand (time(nullptr));


typedef unsigned int unint;



int a = 0,b = 0,c = 0,d = 0,r = 0,v = 0,i = 0,j = 0, diff_be = 0;
unint tmpv = 0;
#define swap(beg, a) {tmpv = xindex[beg];\
    xindex[beg] = xindex[a];\
    xindex[a] = tmpv;}
#define i2c(i) (x[(i)]=='\0'?'$':x[(i)])
#define min(a, b) (a)>(b)?(b):(a)
#define max(a, b) (a)<(b)?(b):(a)

inline 
void vecswap(unint i, unint j, unint n,  unint *xindex)
{
    while (n-- > 0)
    {
        swap(i, j);
        i++;
        j++;
    }
    return;
}
void ssort1(char *x, unint *xindex, unint beg, unint end, unint depth)
{
    if (beg+1>= end)
        return;
    //uint a,b,c,d,r,v, tmpv;
    diff_be  = end - beg;
    a = (rand() % diff_be) + beg;
    swap(beg, a);
    unint tmpv1 = xindex[beg]+depth;
    v = i2c(tmpv1);
    a = b = beg+1;
    c = d = end-1;
    for(;;)
    {
        while (b <= c && (tmpv1 = xindex[b]+depth, r = i2c(tmpv1) - v) <= 0)
        {
            if (r == 0)
            {
                swap(a,b);
                a++;
            }
            b++;
        }
        while (b <= c && (tmpv1 = xindex[c]+depth, r = i2c(tmpv1) - v) >= 0)
        {
            if (r == 0)
            {
                swap(c, d);
                d--;
            }
            c--;
        }
        if (b > c)
            break;
        swap(b, c);
        b++;
        c--;
    }
    r = min(a-beg, b-a);
    vecswap(beg, b-r, r, xindex);
    r = min(d-c, end-1-d);
    vecswap(b, end-r, r, xindex);
    r = b-a+beg;
    ssort1(x, xindex, beg, r, depth);
    if ((tmpv1 = xindex[r]+depth, i2c(tmpv1)) != 0)
    {
        ssort1(x, xindex, r, a+(end-d-1), depth+1);
    }
    r = d - c + beg;
    ssort1(x, xindex, end-r+beg, r, depth);
    return;    
}


#endif


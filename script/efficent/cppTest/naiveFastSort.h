#ifndef NAIVEFASTSORT_H
#define NAIVEFASTSORT_H

/*
 * Based on Bentley & Sedgewick's algorithm on p.5 of their paper
 * " Fast Algorithm for sorting and searching strings".
 * The algorithm has benn extended.
 */
#include <vector> // std::begin()
#include <time.h> // time
#include <stdlib.h> // srand, rand
#include <iostream>
#include <string.h>
typedef unsigned int unint;
// srand (time(nullptr));

// display the debug message
#define MY_DEBUG_MSG 0

using std::cout;
using std::endl;




namespace naiveFastsort
{

#define swap(beg, a) {auto tmpv = xindex[beg];\
        xindex[beg] = xindex[a];\
        xindex[a] = tmpv;}
#define i2c(i) ((i)>=len_x?'#':x[(i)])
#define min(a, b) (a)>(b)?(b):(a)
#define max(a, b) (a)<(b)?(b):(a)

#define coutputXin(ap, N) {for (int i =0; i != (N);++i) cout << (ap)[i]<<"("<<char(i2c((xindex[i]+depth)))<<") ,";cout << endl;}
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
    void ssort1(char *x, unint *xindex, unint beg, unint end, unint depth, const unint &len_x)
    {
    
        if (beg+1>= end || depth >= len_x)
            return;
        int a = 0,b = 0,c = 0,d = 0,r = 0,v = 0, diff_be = 0;
        unint tmpv = 0, tmpv1 = 0;
#if MY_DEBUG_MSG
        static int mtr = 0;
        mtr++;
        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << mtr << endl;
        cout << beg << "---------depth:"<<depth<<"-------------"  << end << endl;
        coutputXin(xindex,len_x);
#endif
        diff_be  = end - beg;
        a = (rand() % diff_be) + beg;
        swap(beg, a);  
#if MY_DEBUG_MSG
        coutputXin(xindex,len_x);
#endif
        tmpv1 = xindex[beg]+depth;
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
#if MY_DEBUG_MSG
        cout <<" after set the middle, before <= region-----v "<<char(v)<<endl;coutputXin(xindex,len_x);
        cout << "::::::::::::::::<= region::::::::::::::::::::::" << beg<< ", " << r << ", "<< depth << endl;
#endif
        ssort1(x, xindex, beg, r, depth, len_x);
#if MY_DEBUG_MSG
        cout <<"After <= region "<<endl;coutputXin(xindex,len_x);
#endif
        if ((tmpv1 = xindex[r]+depth, i2c(tmpv1)) != '\0')
        {
#if MY_DEBUG_MSG
            cout << "a" << a <<", b" << b << ", c"<< c << ", d" << d << ", beg"<< beg << ", end" << end;
            cout << "::::::::::::::::== region::::::::::::::::::::::" << r<< ", " << (end-d+c)<<", "<< depth << endl;
#endif
            ssort1(x, xindex, r, end-d+c/*a+(end-d-1)*/, depth+1, len_x);
#if MY_DEBUG_MSG
            cout <<"After == region "<<endl;coutputXin(xindex,len_x);
#endif
        }
        r = d - c;
#if MY_DEBUG_MSG
        cout << "a" << a <<", b" << b << ", c"<< c << ", d" << d << ", beg"<< beg << ", end" << end;
        cout << "::::::::::::::::::::::>= region::::::::::::::::" << (end-r)<< ", " << end << ", "<< depth << endl;
#endif
        ssort1(x, xindex, end-r, end, depth, len_x);
#if MY_DEBUG_MSG
        cout <<"After >= region "<<endl;coutputXin(xindex,len_x);
#endif
        return;    
    }
    template <class T, size_t N>
        void a111(T (&array)[N])
        {
            cout << *(std::begin(array)+1) << endl;
            return;
        }
    void test()
    {
        srand (time(nullptr));
        using std::cout;
        using std::endl;
        std::string mcin;
        std::cin >> mcin;
        mcin.push_back('$');
        unint NN = mcin.size();
        unint *xins1=new unint[mcin.size()];
        for (size_t i = 0; i != NN; ++i)
            xins1[i] = i;
        unint beg = 0, end = NN;
        ssort1(&mcin[0], &xins1[0], beg, end, 0, end);
        //for (size_t i = 0; i != NN; ++i)
        //    cout << xins1[i] << endl;

        // delete
        delete[] xins1;
    }
}
#endif


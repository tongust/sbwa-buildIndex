#ifndef SBWT_H
#define SBWT_H

#include <cstring>
#include <vector> // std::begin()
#include <time.h> // time
#include <stdlib.h> // srand, rand
#include <tuple>
using std::tuple;
#include <map>
using std::map;
#include <iostream>
#include <memory>
using std::shared_ptr;
#include <string.h>
#include <algorithm>
#include <iterator>
typedef unsigned int unint;

class sBwt
{
public:
    sBwt():period(2), N(0), X(nullptr), SA(nullptr), B(nullptr), bigO(nullptr)
    {
        bigC[0] =  bigC[1] =  bigC[2] = bigC[3] = 0; 
    }
    sBwt(char * str, const size_t& n): X(str), N(n){  
         bigC[0] =  bigC[1] =  bigC[2] = bigC[3] = 0; 
         bigO = new unint*[4];///////////////new
         for (int i = 0; i != 4; ++i)
         {
             bigO[i] = new unint[N]();//////////new
             bigO[i][0] = 0;
         }
         SA = new unint[N];////////////////new mew
         B = new char[N]; /////////////////new
         // initialize SA with 0,1,...,N-1
         for (size_t i = 0; i != N; ++i)
             {SA[i] = i;}
    }
    ~sBwt(){
        cout << endl;for (int i = 0; i != N; ++i)cout << X[i] << ", ";
        if (X)
            delete[] X;
        if (SA)
            delete[] SA;
        for (int i = 0; i != 4; ++i)
        {
            if (bigO[i])
                delete[] bigO[i];
        }
        if (bigO)
            delete[] bigO;
        if (B)
            delete[] B;
    }
public:
	void sort(const char *x, unint *xindex, unint beg, unint end, unint depth, const unint &len_x);
    void vecswap(unint, unint, unint,  unint *);
public:
    unint period;
    unint N;// the length of reference
    char *X;// the reference reads
    unint *SA;// 
    char *B;// the sbwt
    unint **bigO;
    unint bigC[4];// the bigC, from the First column of bwt matrix
protected:
    static map<char, int> base2num;/* {{'A', 0},{'C', 1},{'G', 2},{'T',3}} */
    static const char num2base[5]; /* {'A','C','G','T'};*/
    
};

/*=======================Definition of Member===============================*/
#define MY_DEBUG_MSG 0
using std::cout;
using std::endl;
#define swap(beg, a) {auto tmpv = xindex[beg];\
        xindex[beg] = xindex[a];\
        xindex[a] = tmpv;}
#define i2c(i) ((i)>=len_x?'$':x[(i)])
#define min(a, b) (a)>(b)?(b):(a)
#define max(a, b) (a)<(b)?(b):(a)
#define coutputXin(ap, N) {for (int i =0; i != (N);++i) cout << (ap)[i]<<"("<<char(i2c((xindex[i]+depth)))<<") ,";cout << endl;}
// static member have to be defined outside the class body.
std::map<char, int> sBwt::base2num = {{'A', 0},{'C', 1},{'G', 2},{'T',3}};
const char sBwt::num2base[5] = "ACGT";
inline 
void sBwt::vecswap(unint i, unint j, unint n,  unint *xindex)
{
    while (n-- > 0)
    {
        swap(i, j);
        i++;
        j++;
    }
    return;
}
void sBwt::sort(const char *x, unint *xindex, unint beg, unint end, unint depth, const unint &len_x)
    
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
    sort(x, xindex, beg, r, depth, len_x);
#if MY_DEBUG_MSG
    cout <<"After <= region "<<endl;coutputXin(xindex,len_x);
#endif
    if ((tmpv1 = xindex[r]+depth, i2c(tmpv1)) != '\0')
    {
#if MY_DEBUG_MSG
        cout << "a" << a <<", b" << b << ", c"<< c << ", d" << d << ", beg"<< beg << ", end" << end;
        cout << "::::::::::::::::== region::::::::::::::::::::::" << r<< ", " << (end-d+c)<<", "<< depth << endl;
#endif
        sort(x, xindex, r, end-d+c/*a+(end-d-1)*/, depth+1, len_x);
#if MY_DEBUG_MSG
        cout <<"After == region "<<endl;coutputXin(xindex,len_x);
#endif
    }
    r = d - c;
#if MY_DEBUG_MSG
    cout << "a" << a <<", b" << b << ", c"<< c << ", d" << d << ", beg"<< beg << ", end" << end;
    cout << "::::::::::::::::::::::>= region::::::::::::::::" << (end-r)<< ", " << end << ", "<< depth << endl;
#endif
    sort(x, xindex, end-r, end, depth, len_x);
#if MY_DEBUG_MSG
    cout <<"After >= region "<<endl;coutputXin(xindex,len_x);
#endif
    return;    
}
void testSBwt()
{
    const unint N = 10;
    char ref[N+1] = "ACCGTGTA$$";
	char *X = new char[N+1];
	std::strcpy(X, ref);
	sBwt sb(X, N);
    sb.sort(sb.X, sb.SA, 0, sb.N, 0, sb.N);
    return;
}
#endif

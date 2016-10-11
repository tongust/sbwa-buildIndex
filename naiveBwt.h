#ifndef NAIVEBWT_H
#define NAIVEBWT_H
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
// srand (time(nullptr));
// display the debug message
#define MY_DEBUG_MSG 0
class naiveBwt
{
public:
    // default construction
    naiveBwt():X(nullptr), SA(nullptr), bigO(nullptr), N(0), B(nullptr)
    {
         bigC[0] =  bigC[1] =  bigC[2] = bigC[3] = 0; 

    }
    // construuction 
    naiveBwt(char * str, const size_t& n): X(str), N(n){  

         bigC[0] =  bigC[1] =  bigC[2] = bigC[3] = 0; 
         bigO = new unint*[4];///////////////new
         for (int i = 0; i != 4; ++i)
         {
             bigO[i] = new unint[N]();//////////new
             bigO[i][0] = 0;
         }
         SA = new unint[N];////////////////new mew
         B = new char[N];
         // initialize SA with 0,1,...,N-1
         for (size_t i = 0; i != N; ++i)
             {SA[i] = i;}

    }
    ~naiveBwt(){
//        cout << endl;for (int i = 0; i != N; ++i)cout << SA[i] << ", ";
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
    void ssort1(const char *x, unint *xindex, unint beg, unint end, unint depth, const unint &len_x);
    void sort()
    {
        if (X && SA)
        {
            ssort1(X, SA, 0, N, 0, N);}
        return ;}
    inline 
    void vecswap(unint, unint, unint,  unint *);
    void BWT();
    void CalBigOC();
    void showFM();
    void buildIndex()
    {
        if(SA && X)
        {
            sort();
            BWT();
            CalBigOC();

        }
        return;
    }
    std::tuple<bool, unint, unint, unint>
        exactBackwardSearch(const char*, const size_t&);

    
public:
    char *X;// the reference sequence. 
    char *B;// the bwt sequence
    unint *SA;// the suffix array of X, size: 1 by N
    unint **bigO;// the Occurences defined in Burrows-Wheeler Transform, also known as Rankall, size: 4 by N
    unint bigC[4];// the bigC, from the First column of bwt matrix
    unint N;// The length of reference sequences.
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
std::map<char, int> naiveBwt::base2num = {{'A', 0},{'C', 1},{'G', 2},{'T',3}};
const char naiveBwt::num2base[5] = "ACGT";
inline 
void naiveBwt::vecswap(unint i, unint j, unint n,  unint *xindex)
{
    while (n-- > 0)
    {
        swap(i, j);
        i++;
        j++;
    }
    return;
}
void naiveBwt::ssort1(const char *x, unint *xindex, unint beg, unint end, unint depth, const unint &len_x)
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

void naiveBwt::BWT()
{
    if(!B)return;
    unint tmp = 0;
    for (size_t i = 0; i != N; i++)
        {
            tmp = SA[i];
            if (!tmp)
            {
                B[i] = '$';
            }
            else
            {
                B[i] = X[tmp-1];
            }
        }
    return;
}
void naiveBwt::CalBigOC()
{
    if(!B)return;
    switch (B[0])
    {
        case 'A':
            bigO[0][0] = 1;
            bigC[0]++;
            break;
        case 'C':
            bigO[1][0] = 1;
            bigC[1]++;
            break;
        case 'G':
            bigO[2][0] = 1;
            bigC[2]++;
            break;
        case 'T':
            bigO[3][0] = 1;
            break;
        default:
            break;
    }
#define CODEBIGO() {bigO[0][i] = bigO[0][i-1];\
                bigO[1][i] = bigO[1][i-1];\
                bigO[2][i] = bigO[2][i-1];\
                bigO[3][i] = bigO[3][i-1];} 
    {
        /* A, C, G, T */
        for (size_t i = 1; i < N; ++i)
        {
            switch (B[i])
            {
                case 'A': 
                    CODEBIGO();
                    bigC[0]++;
                    bigO[0][i] = bigO[0][i-1] + 1;
                    break;
                case 'C': 
                    CODEBIGO();
                    bigC[1]++;
                    bigO[1][i] = bigO[1][i-1] + 1;
                    break;
                case 'G': 
                    CODEBIGO();
                    bigC[2]++;
                    bigO[2][i] = bigO[2][i-1] + 1;
                    break;
                case 'T': 
                    CODEBIGO();
                    bigO[3][i] = bigO[3][i-1] + 1;
                    break;
                default:
                    CODEBIGO();
                    break;
            }

        }
        bigC[3]=bigC[0]+bigC[1]+bigC[2];
        bigC[2]=bigC[0]+bigC[1];
        bigC[1]=bigC[0];
        bigC[0]=0;
    } // End of calculating big-o and big-c

#if 0 
    for (auto i = 0; i != 4; ++i)
        std::cout << bigC[i] << std::endl;
    // cout bigO
    using std::cout;
    using std::endl;
    cout << "Big-O----------\n";
    for (int i = 0; i != N; ++i)
        cout << char(B[i]);
    cout << endl;
    for (int i = 0; i != 4; ++i)
    {
        for (int j = 0; j != N; ++j)
            cout << bigO[i][j] << ",";
        cout << endl;
    }
#endif
    // calculate C

    // delete
//        for (int i = 0; i != 4; ++i)
//        {
//           delete [] bigO[i];
//       }
//        delete[] bigO;
    
    return;
}

std::tuple<bool, unint, unint, unint> 
naiveBwt::exactBackwardSearch(const char *P, const size_t& Np)
{
    char a = P[0];
    unint L= 0, R = N-1;
    long long i = 0;
    for (i = Np-1; i>-1; --i)
    { 
        a = P[i];
        L = bigC[base2num[a]] + (L==0?0:bigO[base2num[a]][L-1])+1;
        R = bigC[base2num[a]] + bigO[base2num[a]][R];
        if (L>R)break;
    }
    if (L <= R)
        return std::make_tuple(true, SA[L], SA[R], (unint)i);// return where to align
    else
        return std::make_tuple(false, L, R, (unint)i);
}

void naiveBwt::showFM()
{
    if (!X)return;
    cout << "\nRef: "<<endl;
    for (int i = 0; i != N; ++i)cout << X[i];
    std::cout << endl << "i\tSA\tFM\tBWT"<< endl;
    for (unint i = 0; i != N; ++i)
    {
        cout << i << "\t" << SA[i] <<"\t";
        unint j = 0;
        for (j = 0; j < N-1; ++j)
        {
            cout << X[(j+SA[i])%N];
        }
        j = N - 1; 
        cout << "\t" << X[(j+SA[i])%N];
        cout << endl;
    }
    cout << endl;
    return;
}







#endif /*NAIVEBWT_H*/

#ifndef NAIVEFASTSORT_H
#define NAIVEFASTSORT_H
/*
 * Based on Bentley & Sedgewick's algorithm on p.5 of their paper
 * " Fast Algorithm for sorting and searching strings".
 * The algorithm has benn extended.
 */
#include <limits>
#include <vector> // std::begin()
#include <time.h> // time
#include <stdlib.h> // srand, rand
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
using std::cout;
using std::endl;



namespace naiveFastsort
{
#define swap(beg, a) {auto tmpv = xindex[beg];\
        xindex[beg] = xindex[a];\
        xindex[a] = tmpv;}
#define i2c(i) ((i)>=len_x?'$':x[(i)])
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
    void ssort1(const char *x, unint *xindex, unint beg, unint end, unint depth, const unint &len_x)
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
    void BWT(const char *T, char *B, unint *SA, const size_t &N)
    {
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
                    B[i] = T[tmp-1];
                }
            }
    }
    void CalBigOC(const unint *SA, const char* B, const size_t &N, unint **bigO, unint* bigC)
    {
//        unint **bigO = new unint*[4];
//       unint bigC[4] = {0,0,0,0};
/*        for (int i = 0; i != 4; ++i)
        {
            bigO[i] = new unint[N]();
            bigO[i][0] = 0;
        }*/
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
        // calculate big-o
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
    unint exactBackwardSearch(const char *P, const size_t& Np, const unint *SA, const char* B, const size_t &N, unint **bigO, unint* bigC)
    {
        map<char, int> base2num = {{'A', 0},{'C', 1},{'G', 2},{'T',3}};
        const char num2base[] = "ACGT";
        char a = P[0];
        unint L= 0, R = N-1;
        for (int i = Np-1; i>-1; --i)
        { 
            a = P[i];
            L = bigC[base2num[a]] + (L==0?0:bigO[base2num[a]][L-1])+1;
            R = bigC[base2num[a]] + bigO[base2num[a]][R];
            if (L>R)break;
        }
        if (L <= R)
            return SA[L];// return where to align
        else
            return 0;
    }
    /*  Verify the ExactSearch  */
    auto genRandDNA = [](char *X, const unint &N)->void
    {
        map<char, int> base2num = {{'A', 0},{'C', 1},{'G', 2},{'T',3}};
        const char num2base[] = "ACGT";
        for (size_t i = 0; i != N; ++i)
        {
            X[i] = num2base[(rand()%4+0)];
        }
        return;
    };
    auto genMutateDNA = [](char *X, const unint &N)->void
    {
        map<char, int> base2num = {{'A', 0},{'C', 1},{'G', 2},{'T',3}};
        const char num2base[] = "ACGT";
        int i_m = (rand()%N) + 0;
        int b_n = base2num[X[i_m]];
        int c_n = b_n;
        while (c_n == b_n)
        {
            c_n = rand()%4+0;
        }
        X[i_m] = num2base[c_n];
        return;
    };
    void test1();
    void test()
    {
        srand (time(nullptr));
        using std::cout;
        using std::endl;
        {
            //                 M  k   
            const size_t N = 8;// the length of ref
            const size_t N_p = 2;// the length of pattern
            // generate the refence reads radnomly
            // and the paterns
            char *X = new char[N];

            genRandDNA(X, N);
            X[N-1] = '$';
            unint *SA = new unint[N];/////////////////////////////////NEW;
            // initialize SA with 0,1,...,N-1
            for (size_t i = 0; i != N; ++i)
                {SA[i] = i;}
            ssort1(X, SA, 0, N, 0, N);
            char *B = new char[N];/////////////////////////////////NEW
            BWT(X, B, SA, N);
            unint **bigO = new unint*[4];///////////////////////////////////NEW NEW
            unint bigC[4] = {0,0,0,0};
            for (int i = 0; i != 4; ++i)
            {
                bigO[i] = new unint[N]();
                bigO[i][0] = 0;
            }
            CalBigOC(SA, B, N, bigO, bigC);
            // print FM
//            cout << "i\t" << "index\t" << "FM\n";
            for (unint i = 0; i != N; ++i)
            {
                cout << i << "\t(" << SA[i] <<")\t";
                for (unint j = 0; j != N; ++j)
                {
                    cout << X[(j+SA[i])%N];
                }
                cout << endl;
            }
            for (int i_iner = 0; i_iner != 0; ++i_iner)
            {
                char pat_0[N_p], pat_1[N_p];
                unint cp_s = rand()%(N-N_p-1)+1;
                std::copy(X+cp_s, X+cp_s+N_p, pat_0);
                std::copy(X+cp_s, X+cp_s+N_p, pat_1);
                genMutateDNA(pat_1, N_p);
                unint res0 = exactBackwardSearch(pat_0,N_p,SA,B,N,bigO,bigC);
                unint res1 = exactBackwardSearch(pat_1,N_p,SA,B,N,bigO,bigC);
                if (res0==cp_s)
                    std::cout << "Match\t"<<cp_s<<"\t"<<res0;
                else
                    std::cout << "Mismatch\t"<<cp_s<<"\t"<<res0;
                if (res1==cp_s) 
                    std::cout << "\tMatch\t"<<cp_s<<"\t"<<res1;
                else
                    std::cout << "\tMismatch\t"<<cp_s<<"\t"<<res1;
                std::cout << std::endl;

            }
            // delete
            delete[] X;
            delete[] B;
            for (int i = 0; i != 4; ++i)
            {
               delete [] bigO[i];
            }
            delete[] bigO;
            delete[] SA;

        }
#ifdef max
#undef max
//        cout << sizeof(long long) << ","<< (std::numeric_limits<int>::max()) << endl;
#endif
    }
}
#endif


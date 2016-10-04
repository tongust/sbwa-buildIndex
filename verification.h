#ifndef VERIFICATION_H
#define VERIFICATION_H
#include <tuple>
#include <iostream>
#include <map>
#include "naiveBwt.h"
using std::map;
class verifySBWA
{
public:
    static void genRandDNA(char *, const unint &);
    static void genMutateDNA(char *X, const unint &N);
    static map<char, int> base2num;
    static const char num2base[5];
    void testnaiveBwt(const size_t& N, const size_t &N_p, const size_t& );

    
};
std::map<char, int> verifySBWA::base2num = {{'A', 0},{'C', 1},{'G', 2},{'T',3}};
const char verifySBWA::num2base[5] = "ACGT";

void verifySBWA::genRandDNA(char *X, const unint &N)
{
    map<char, int> base2num = {{'A', 0},{'C', 1},{'G', 2},{'T',3}};
    const char num2base[] = "ACGT";
    for (size_t i = 0; i != N; ++i)
    {
        X[i] = num2base[(rand()%4+0)];
    }
    return;
}
void verifySBWA::genMutateDNA(char *X, const unint &N)
{
    int i_m = (rand()%N) + 0;
    int b_n = base2num[X[i_m]];
    int c_n = b_n;
    while (c_n == b_n)
    {
        c_n = rand()%4+0;
    }
    X[i_m] = num2base[c_n];
    return;
}

void verifySBWA::testnaiveBwt(const size_t& N, const size_t &N_p, const size_t &test_num = 100 )
{
/*N:    the length of ref
 *N_p:  the length of pattern*/
    srand (time(nullptr));
    char *X = new char[N];///////////////////////////////////NEW
    genRandDNA(X, N);
    X[N-1] = '$';
    naiveBwt tnB(X, N);
    tnB.buildIndex();
    tnB.showFM();
    for (int i_iner = 0; i_iner != test_num; ++i_iner)
    {
        char pat_0[N_p], pat_1[N_p];
        unint cp_s = rand()%(N-N_p-1)+1;
        X = tnB.X;
        std::copy(X+cp_s, X+cp_s+N_p, pat_0);
        std::copy(X+cp_s, X+cp_s+N_p, pat_1);
        genMutateDNA(pat_1, N_p);
        auto res0 = tnB.exactBackwardSearch(pat_0,N_p);
        auto res1 = tnB.exactBackwardSearch(pat_1,N_p);
        if (std::get<0>(res0))
            std::cout << "Match\t"<<cp_s<<"\t"<<std::get<1>(res0);
        else
            std::cout << "Mismatch\t"<<cp_s<<"\t"<<std::get<1>(res0);
        if (std::get<0>(res1)) 
            std::cout << "\tMatch\t"<<cp_s<<"\t"<<std::get<1>(res1);
        else
            std::cout << "\tMismatch\t"<<cp_s<<"\t"<<std::get<1>(res1);
        std::cout << std::endl;
    }
}


#endif /* verification */

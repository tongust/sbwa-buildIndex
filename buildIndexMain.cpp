#include <iostream>
#include <vector>
#include <stdio.h>
#include <seqan/basic.h>
#include <seqan/sequence.h>
#include <seqan/stream.h>
#include <seqan/seq_io.h>

#include <string>

#include "naiveFastSort.h"

using seqan::CharString;
using seqan::SeqFileIn;
using seqan::Dna5String;
using seqan::StringSet;

using std::cout;
using std::endl;

void print_paras(char []);
int main(int argc, char** argv) {
    char a[100];
    sscanf(argv[1], "%s", a);

    print_paras(a);
    naiveFastsort::test();
    return 0;


    CharString r1 = a;
    cout << r1 << endl;
    CharString seqFileName = a;
    StringSet<CharString> id;
    //Dna5String seq;
    std::string seq;
 //   char *seq = new char[0]
    SeqFileIn seqFileIn(seqan::toCString(seqFileName));
    seqan::readRecord(id, seq, seqFileIn);
    seq.push_back('$');
    const char *dnas = seq.c_str();
    auto size_seq = seq.size();
    unint * xins = new unint[size_seq];
    for (size_t i = 0; i != size_seq; ++i)
        xins[i] = i;
    unint beg = 0, end = size_seq;
    naiveFastsort::ssort1(dnas, xins, beg, end, 0, end);
    for (size_t i = 0; i != size_seq; ++i)
        cout << xins[i]<<",";



    delete[] xins;
    return 0;


}
void print_paras(char a[100])
{

    cout 
        << "                                                   \n"
        << "                                                   \n"
        << "      ------------------------------------         \n"
        << "        .....  .....  ...   ...    ..              \n"
        << "           .   .      .  .  .  .   . .             \n"
        << "          .    .....  ...   ...    ....            \n"
        << "         .     .      .  .  .  .   .   .           \n"
        << "        .....  .....  ...   .   .  .    .          \n"
        << "      -------------------------------------        \n"
        << "                                                   \n"
        << "                                                   \n";
        
    cout << "reads: " << a << endl;
    return;
}

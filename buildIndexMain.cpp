#include <iostream>
#include <stdio.h>
#include <seqan/basic.h>
#include <seqan/sequence.h>
#include <seqan/stream.h>
#include <seqan/seq_io.h>


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




    CharString r1 = a;
    cout << r1 << endl;
    CharString seqFileName = a;
    StringSet<CharString> id;
    Dna5String seq;
    SeqFileIn seqFileIn(seqan::toCString(seqFileName));
    seqan::readRecord(id, seq, seqFileIn);

//    std::cout << id << '\t' << seq << '\n';
    //cout << id << endl;    
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

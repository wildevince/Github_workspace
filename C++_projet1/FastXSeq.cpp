#include "FastXSeq.h"
//#include <iostream>
#include <fstream>
#include <cstring>
#include <stddef.h>

using namespace std;

//____//____//____/ FastaXSeq /____//____//____//

FastXSeq::FastXSeq(const char* head, string es):
    header(head), string(es) {}

FastXSeq::FastXSeq(const FastXSeq& fx): 
    header(myStrDup(fx.header)),
    sequence(fx.sequence) {} 

FastXSeq::~FastXSeq() {
    if (header) {
        delete[] header;
    }
    if (sequence) {
        delete sequence;
    }
}

const char* FastXSeq::getHeader() {
    return header;
}

string FastXSeq::getSequence() {
    return sequence;
}

void FastXSeq::setHeader(char* head) {
    if (header) {
        delete header;
    }
    else {
        header = head
    }
}

void FastXSeq::toStream(ostream &os) {
    os << "Header : " << (header? hearder: "<no header>") << endl;
    os << "Sequence : " << sequence << endl;
}

void parseq(ifs){
    size_t p = ifs.tellg();
    char* head = ifs.getline();
    setHeader(head);
    string seq = "";
    do {
        char c = ifs.peek();
        if (c != '>' || c != ';' ){
            seq += ifs.get();
        }
    }while (c != '>' || c != ';' )
} 
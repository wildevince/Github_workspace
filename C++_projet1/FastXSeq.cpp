#include "FastXSeq.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stddef.h>

using namespace std;

//____//____//____/ FastXSeq /____//____//____//

FastXSeq::FastXSeq(char* head, size_t p, size_t t, string es):
    header(head), start_seq(p), taille_seq(t), sequence(es) {}

FastXSeq::FastXSeq(const FastXSeq& fx): 
    header(myStrDup(fx.header)),
    start_seq(fx.start_seq),
    taille_seq(fx.taille_seq),
    sequence(fx.sequence) {} 

FastXSeq::~FastXSeq() {
    if (header) {
        delete[] header;
    }
}

FastXSeq& FastXSeq::operator=(const FastXSeq &fx)
{
    if (header) {
        delete[] header;
    }
    //
    this->header = myStrDup(fx.header);
    this->start_seq = fx.start_seq;
    this->taille_seq = fx.taille_seq;
    this->sequence = fx.sequence;
    cout << "Copy Completed" << endl;
    return *this;
}

char* FastXSeq::getHeader() const {
    return header;
}

string FastXSeq::getSequence() const {
    return sequence;
}

size_t FastXSeq::getStart() const {
    return start_seq;
}
size_t FastXSeq::getSize() const {
    return taille_seq;
}

void FastXSeq::setHeader(char* head) {
    if (header) {
        delete[] header;
        header = NULL;
    }
    for (size_t i = 0; i < sizeof(head) ; ++i) 
    {
        this->header[i] = head[i];
    }
}

void FastXSeq::setHeader(string head) 
{
    header = new char[ head.size() ]; 
    for (size_t i = 0; i < head.size() ; ++i) 
    {
        header[i] = head[i];
    } 
}


void FastXSeq::setStart(size_t p) {
    start_seq = p;
}

void FastXSeq::setTaille(size_t t) {
    taille_seq = t;
}

void FastXSeq::toStream(ostream &os) const
{
    os << "\n### coucou le stream XSeq ! ###\n" << endl;
    os << "Header : " << (header? header: "<no header>") << endl;
    os << "positiion sequence dans le fichier : " << start_seq << endl;
    os << "taille Sequence : " << taille_seq << '\n' << endl;
}

void FastXSeq::parseq(ifstream &ifs, size_t p){
    //size_t p = ifs.tellg();
    cout << "Han Solo a fait le raide de Kessel en 12 Parseqs !" <<  endl;
    //
    string head = "";
    ifs.seekg(p);
    getline(ifs, head);
    cout <<"We've found the header : " << head << endl;
    setHeader(head);
    cout <<"So the header : " << header << endl;
    // position du header + taille header 
    setStart(p + head.size());
    cout << "position sequence : " << start_seq << endl; 
    
    // string substr (size_t pos = 0, size_t len = npos) const;

    /*
    string seq = "";
    do {
        char c = ifs.peek();
        if (c != '>' || c != ';' ){
            seq += ifs.get();
        }
    }while (c != '>' || c != ';' )
    */
}
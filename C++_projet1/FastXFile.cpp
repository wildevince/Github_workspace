#include "FastXFile.h"

// déclaration des fonctions locales
const char* myStrDup(const char* s);
bool ifspace(char c, bool .........)

const char* myStrDup(const char* s){
    const char* res = NULL;
    if (s) {
        size_t n = strlen(s) +1;
        res = new char[n];
        for(size_t i=0; i<n; ++i) {
            res[i] = s[i];
        }
    }
    return res;
}

ostream &operator<<(ostream &os, const FastXFile &f){
    f.tostream(os);
    return os;
}


// constructor & delete
FastXFile::FastXFile( const char* f) :
    fileName(NULL), pos(NULL), nb_sequence(0) 
    {
        setFileName(f);
    }

FastXFile::FastXFile( const FastXFile &f ) :
    fileName(nyStrDup(f.fileName)), 
    pos( f.pos ? new size_t[f.nb_sequence] : NULL),
    nb_sequence(f.nb_sequence)
    {
        for(size_t i = 0; i < nb_sequence; ++i)
        {
            pos[i] = f.pos[i];
        }
    }

FastXFile::~FastXFile(){
    if (fileName) { 
        delete[] fileName;
    }
    if (pos) {
        delete[] pos;
    }
}

FastXFile &FastXFile::operator=(const FastXFile &f){
    if (this != &f) {
        if (fileName) { 
            delete[] fileName;
            fileName = NULL;
        }
        if (f.nb_sequence != nb_sequence) {
            if (pos) {
                delete[] pos;
                pos = NULL;
            }
            pos = ( f.pos ? new size_t[f.nb_sequence] : NULL);
        }
        fileName = nyStrDup(f.fileName) ;
        nb_sequence = (f.nb_sequence);
        for(size_t i = 0; i < nb_sequence; ++i)
            {
                pos[i] = f.pos[i];
            }
    }
    return *this;
}

const char* FastxFile::getFileName() const {
    return fileName;}

size_t FastxFile::getNbSequence() const { 
    return nb_sequence;}

void FastxFile::toStream(ostream &os) const {
    os << "File: " << (fileName? fileName : "<no file>") << endl;
    os << "Nb sequence" << nb_sequence << endl;
    // getsequence ?
}

void FastxFile::setFileName(const char* f) {
    if (fileName) {
        delete[] fileName;}
    if (pos) {
        delete[] pos;
        pos = NULL;
        nb_sequence = 0;}
    fileName = myStrDup(f);
    if (fileName) {
        parse();}
}

void FastXFile::parse() {
    ifstream ifs(fileName);
    if (!ifs) {
        throw "Unable to open this file" ;}
    // recherche du premier caractere
    char c = '\n'
    while( (ifs) && (ifspace(ifs.peek())) {
        c = ifs.get();
        }
    if ( ifs ) {
        if (c == '\n') {
            c = ifs.peek();
            if ( (c == '>') || (c == ';') || (c == '@') ) {
            c = '\n';
        }
    }
    if ( c != '\n') {
        throw "erreur doumkumpf !"}
    // now: on sait que le premier caracter est bien '<' ou ';' ou '@'
        if ( ifs.peek == '@') { //tp2
    }else{
    // prochain char = ';' ou '>'
        do {
            string s;
            getline(ifs,s);
            nb_sequence += ( (s[0] == '>')|| (s[0] == ';') )
        } while (ifs);
        pos = new size_t[nb_sequence];
        nb_sequence = 0;
        ifs.clear(); // pour reprendre la lecture du fichier


}
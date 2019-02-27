#include "FastXFile.h"

// fonctions locales
const char* myStrDup(const char* s){
    const char* res = NULL;
    if (s) {
        size_t n = strlen(s) +1;
        res = new char[n];
        for(size_t i=0; i<n; ++i) {
            res[i] = s[i]; }
    } return res; }

ostream &operator<<(ostream &os, const FastXFile &f){
    f.tostream(os);
    return os; }

//____//____//____/ FastaXFile /____//____//____//

// ____ constructor ____ //
FastXFile::FastXFile( const char* f) :
    fileName(NULL), pos(NULL), nb_sequence(0) 
    { setFileName(f); }

// ____ constructor par copie ____ //
FastXFile::FastXFile( const FastXFile &f ) :
    fileName(nyStrDup(f.fileName)), 
    pos( f.pos ? new size_t[f.nb_sequence] : NULL),
    nb_sequence(f.nb_sequence)
    { for(size_t i = 0; i < nb_sequence; ++i)
        { pos[i] = f.pos[i];  } }

// ____ destructeur ____ //
FastXFile::~FastXFile() {
    if (fileName) { 
        delete[] fileName;
    }
    if (pos) {
        delete[] pos;
    }
}

FastXFile &FastXFile::operator= (const FastXFile &f) {
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

//____/ getters /____//
const char* FastxFile::getFileName() const {
    return fileName;}

size_t FastxFile::getNbSequence() const { 
    return nb_sequence;}


//____/ flux sortant /____//
void FastxFile::toStream(ostream &os) const {
    os << "File: " << (fileName? fileName : "<no file>") << endl;
    os << "Nb sequence" << nb_sequence << endl;
    // getsequence ?
}

//___/ setters /____//
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

//___/ methote privé /____//
void FastXFile::parse() {
    //
    ifstream ifs(fileName);// construit le flux depuis this
    //
    if (! ifs.good() ) {
        throw "Unable to open this file" ;}
    //
    // recherche du premier caractere
    char c = '\n'
    while( (ifs.good() ) && (ifspace(ifs.peek() )) {
        // ici tant que; no error dans le flux 
        // && si le prochain charactere est un espace
        c = ifs.get();}
        // ici ifs est un flag ("marque-page" dans notre flux-fichier)
    //
    if ( ifs.good() ) { //on peut lire le fichier
        if (c == '\n') { //le char précédent est un '\n'
            c = ifs.peek(); //char suivant
            if ( (c == '>') || (c == ';') || (c == '@') ) {
                // si le fichier commence par 1 des 3 char speciaux
                c = '\n'; } // alors okay^^
    }
    if ( c != '\n') { // on rencontre alors un char non prévu => error
        throw "erreur doumkumpf !"}
    // now: on sait que le premier caracter est bien '<' ou ';' ou '@'
    // 
        if ( ifs.peek == '@') { 
            //
            //  tp2: FastaQ
            //
        }else{
        // prochain char = ';' ou '>'
            do {
                string s;
                getline(ifs,s);
                nb_sequence += ( (s[0] == '>') || (s[0] == ';') )
            } while (ifs); // compte le nombre de séquence
        pos = new size_t[nb_sequence];
        // creation du tableau 
        nb_sequence = 0;
        ifs.clear(); // reset le flag/"marque-page" ifs
        ifs.seekg(0); // reprend à la position 0
        siez_t p = ifs.tellg(); // donne la position actuelle
        do {
            string s;
            getline(ifs,s);
            if ( (s[0] == '>') || (s[0] == ';') ) {
                pos[nb_sequence++] = p;} 
                // stock la nouvelle position
                // puis encrémente nb_sequence
                //
             p = ifs.tellg(); // donne la nouvelle actuelle
        } while(ifs);

    }
}
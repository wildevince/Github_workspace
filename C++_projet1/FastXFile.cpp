#include "FastXFile.h"
//#include <iostream>
#include <fstream>
#include <cstring>
#include <stddef.h>

using namespace std;

// fonctions locales
char *myStrDup(char *s)
{
    char *res = NULL;
    if (s)
    {
        size_t n = strlen(s) + 1;
        res = new char[n];
        for (size_t i = 0; i < n; ++i)
        {
            res[i] = s[i];
        }
    }
    return res;
}

ostream &operator<<(ostream &os, const FastXFile &f)
{
    f.toStream(os);
    return os;
}

bool ifspace(char c)
{
    if (c) {
        return ( isspace(c)? true: false);
    }
    else {
    return false;
    }
}

//____//____//____/ FastaXFile /____//____//____//

// ____ constructor ____ //
FastXFile::FastXFile(char *f) : fileName(NULL), pos(NULL), nb_sequence(0)
{
    setFileName(f);
}

// ____ constructor par copie ____ //
FastXFile::FastXFile(const FastXFile &f) : fileName(myStrDup(f.fileName)),
                                           pos(f.pos ? new size_t[f.nb_sequence] : NULL),
                                           nb_sequence(f.nb_sequence)
{
    for (size_t i = 0; i < this->nb_sequence; ++i)
    {
        this->pos[i] = f.pos[i];
    }
}

// ____ destructeur ____ //
FastXFile::~FastXFile()
{
    if (this->fileName)
    {
        delete[] this->fileName;
    }
    if (this->pos)
    {
        delete[] this->pos;
    }
}

// ____ operator ____ //
FastXFile &FastXFile::operator=(const FastXFile &f)
{
    if (this != &f)
    {
        if (this->fileName)
        {
            delete[] this->fileName;
            this->fileName = NULL;
        }
        if (f.nb_sequence != this->nb_sequence)
        {
            if (this->pos)
            {
                delete[] this->pos;
                this->pos = NULL;
            }
            this->pos = (f.pos ? new size_t[f.nb_sequence] : NULL);
        }
        this->fileName = myStrDup(f.fileName);
        this->nb_sequence = (f.nb_sequence);
        for (size_t i = 0; i < this->nb_sequence; ++i)
        {
            this->pos[i] = f.pos[i];
        }
    }
    return *this;
}

//____/ getters /____//
char *FastXFile::getFileName() const
{
    return this->fileName;
}

size_t FastXFile::getNbSequence() const
{
    return this->nb_sequence;
}

//____/ flux sortant /____//
void FastXFile::toStream(ostream &os) const
{
    os << "File : " << (this->fileName ? this->fileName : "<no file>") << endl;
    os << "Nb sequence : " << this->nb_sequence << endl;
    // getsequence ?
    // return os;
}

ostream &operator<<(ostream &os, const FastXFile *f)
{
    f->toStream(os);
    return os;
}

//___/ setters /____//
void FastXFile::setFileName(char* f)
{
    if (this->fileName)
    {
        delete[] this->fileName;
    }
    if (this->pos)
    {
        delete[] this->pos;
        this->pos = NULL;
        this->nb_sequence = 0;
    }
    this->fileName = myStrDup(f);
    if (this->fileName)
    {
        parse();
    }
}

//___/ methote privé /____//
void FastXFile::parse()
{
    //
    ifstream ifs(this->fileName); // construit le flux depuis this
    //
    
    if (!ifs.good())
    {
        cout << "### Unable to open this file 1###"<< endl;
        throw "### Unable to open this file 2###"; //"Unable to open this file";
        cout << "### Unable to open this file 3###"<< endl;
    }
    if (ifs) {
        ifs.seekg(0,ios::end);
        size_t sizefile = ifs.tellg();
        if (sizefile == 0) {
            cerr << "### fichier vide ###" << endl;
            throw ;
        }
    }
    //
    // recherche du premier caractere
    char c = '\n';
    while( (ifs) && ifspace(ifs.peek()) ) {
        // ici tant que; no error dans le flux
        // && si le prochain charactere est un espace
        cout << "### le char de la boucle while est: 'couille'"<<  c  ;
        cout << " ###" << endl;
        c = ifs.get();}
        // ici ifs est un flag ("marque-page" dans notre flux-fichier)
    //
    if ( ifs.good() ) { //on peut lire le fichier
        if (c == '\n')
        {                   //le char précédent est un '\n'
            c = ifs.peek(); //char suivant
            if ((c == '>') || (c == ';') || (c == '@'))
            {
                // si le fichier commence par 1 des 3 char speciaux
                c = '\n';
            } // alors okay^^
        }
        if (c != '\n')
        { // on rencontre alors un char non prévu => error
            throw "erreur dummkopf !";
        }
        // now: on sait que le premier caracter est bien '<' ou ';' ou '@'
        //
        if (ifs.peek() == '@')
        {
            //
            //  tp2: FastaQ
            //
        }
        else
        {
            // prochain char = ';' ou '>'
            do
            {
                string s;
                getline(ifs, s);
                this->nb_sequence += ((s[0] == '>') || (s[0] == ';'));
            } while (ifs); // compte le nombre de séquence
            this->pos = new size_t[this->nb_sequence];
            // creation du tableau
            this->nb_sequence = 0;
            ifs.clear();            // reset le flag/"marque-page" ifs
            ifs.seekg(0);           // reprend à la position 0
            size_t p = ifs.tellg(); // donne la position actuelle
            do
            {
                string s;
                getline(ifs, s);
                if ((s[0] == '>') || (s[0] == ';'))
                {
                    this->pos[this->nb_sequence++] = p;
                }
                // stock la nouvelle position
                // puis encrémente nb_sequence
                //
                p = ifs.tellg(); // donne la nouvelle actuelle
            } while (ifs);
        }
        }
}

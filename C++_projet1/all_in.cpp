
#include "all_in.h"

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
    //cout << "Han Solo a fait le raide de Kessel en 12 Parseqs !" <<  endl;
    //
    string head = "";
    ifs.seekg(p);
    getline(ifs, head);
    //cout <<"We've found the header : " << head << endl;
    setHeader(head);
    //cout <<"So the header : " << header << endl;
    // position du header + taille header 
    setStart(p + head.size());
    //cout << "position sequence : " << start_seq << endl; 
    
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


// fonctions locales
char *myStrDup(char *s) //s = &f.fileName
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

bool ifspace(char c) // if char blanc
{
    if (c)
    { // le char existe
        return (isspace(c) ? true : false);
    }
    else
    {
        return false;
    }
}

//____//____//____/ FastaXFile /____//____//____//

// ____ constructor ____ //
FastXFile::FastXFile(char *f) : fileName(NULL),
                                pos(NULL),
                                list_seq(NULL),
                                nb_sequence(0)
{
    setFileName(f);
}

// ____ constructor par copie ____ //
FastXFile::FastXFile(const FastXFile &f) : fileName(myStrDup(f.fileName)),
                                           pos(f.pos ? new size_t[f.nb_sequence] : NULL),
                                           list_seq(f.list_seq? new FastXSeq[f.nb_sequence] : NULL),
                                           //list_seq(f.list_seq ? new FastXSeq() : NULL),
                                           nb_sequence(f.nb_sequence)
{
    for (size_t i = 0; i < this->nb_sequence; ++i)
    {
        this->pos[i] = f.pos[i];
        list_seq[i] = f.list_seq[i];
        //list_seq = f.list_seq;
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
    if (list_seq)
    {
        delete[] list_seq;
        //list_seq->~FastXSeq();
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
            if (this->list_seq)
            {
                delete[] this->list_seq;
                //list_seq->~FastXSeq();
                this->list_seq = NULL;
            }
            this->list_seq = (f.list_seq ? new FastXSeq[f.nb_sequence] : NULL);
            //this->list_seq = (f.list_seq ? new FastXSeq() : NULL);
        }
        this->fileName = myStrDup(f.fileName);
        this->nb_sequence = (f.nb_sequence);
        for (size_t i = 0; i < this->nb_sequence; ++i)
        {
            this->pos[i] = f.pos[i];
            list_seq[i] = f.list_seq[i];
            //list_seq = f.list_seq;
        }
    }
    return *this;
}

FastXSeq& FastXFile::operator[](size_t i)
{
    if (i >= nb_sequence ){
        cerr << "out of range" << endl;
        throw "out of range" ;
    }
    return this->list_seq[i];
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
    os << "Coucou toStream Hibou !!! " << endl;
    os << "File : " << (this->fileName ? this->fileName : "<no file>") << endl;
    os << "Nb sequence : " << this->nb_sequence << endl;
    os << "positions des sequences :  " << endl;
    for (size_t i = 0; i < nb_sequence ; ++i) 
    {
        this->list_seq[i].toStream(os) ;
        os << list_seq << endl;
    }
    /*if (list_seq)
    {
        os << "La sequence : " << list_seq << endl;
    }*/
}

//___/ setters /____//
void FastXFile::setFileName(char *f)
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
        cout << "### Unable to open this file 1###" << endl;
        throw "### Unable to open this file 2###";
    }
    if (ifs)
    { // check fichier vide ?
        ifs.seekg(0, ios::end);
        size_t sizefile = ifs.tellg();
        if (sizefile == 0)
        {
            cerr << "### fichier vide ###" << endl;
            throw;
        }
        ifs.seekg(0);
    }
    //
    // recherche du premier caractere
    char c = '\n';
    while ((ifs) && ifspace(ifs.peek()))
    {
        // ici tant que; no error dans le flux
        // && si le prochain charactere est un espace
        //cout << "### le char de la boucle while est: 'couille'" << c << " ###" << endl;
        c = ifs.get();
    }
    // ici ifs est un flag ("marque-page" dans notre flux-fichier)
    //
    if (ifs.good())
    {
        //on peut lire le fichier
        cout << "Format verified ! \n"
             << endl;
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
            cerr << "Error de format" << endl;
            throw "erreur dummkopf !";
        }
        // now: on sait que le premier caracter est bien '<' ou ';' ou '@'
        //
        if (ifs.peek() == '@')
        {
            //  tp2: FastaQ
            cout << "Zone en travaux revennez plus tard, SVP" << endl;
            //
        }
        else
        {
            cout << "\nStart Parssing FastA... \nPlease wait...\n"
                 << endl;
            // prochain char = ';' ou '>'
            do
            {
                string s;
                getline(ifs, s);
                this->nb_sequence += ((s[0] == '>') || (s[0] == ';'));
                //cout << "nb_seq + 1 = " << nb_sequence << endl;
            } while (ifs); // compte le nombre de séquence
            this->pos = new size_t[this->nb_sequence];
            //this->list_seq = new FastXSeq[nb_sequence];
            // creation du tableau
            this->nb_sequence = 0;
            //cout << " Rock'N Roll" << endl;
            ifs.clear();            // reset le flag/"marque-page" ifs
            ifs.seekg(0);           // reprend à la position 0
            size_t p = ifs.tellg(); // donne la position actuelle
            //FastXSeq* xseq = new FastXSeq() ;
            do
            {
                FastXSeq* xseq = new FastXSeq() ;
                string s;
                getline(ifs, s);
                if ((s[0] == '>') || (s[0] == ';'))
                {
                    this->pos[this->nb_sequence++] = p;
                    xseq->parseq(ifs, p);
                    this->list_seq[this->nb_sequence++] = *xseq;
                    cout << " 1UP " << endl;
                }
                // stock la nouvelle position
                // puis encrémente nb_sequence
                //
                p = ifs.tellg(); // donne la nouvelle actuelle
            } while (ifs);
            //xseq->parseq(ifs, p);
            //this->list_seq = xseq;
        } // end fastA
    }     // end proper parse
    cout << "Job done !" << endl;
} //fin !



int main( int argc, char** argv) {

     if (argc != 2 ) {
        //cerr << "usage:" << basename(argv[0]) << " <sequence>" << endl;
        cerr << "usage:" << argv[0] << " <sequence>" << endl;
        return 1; 
    }
    char* s = argv[1] ; 
    cout << "chaine a verifier: '" << s << "'"<< endl;
    
    // conversion string to char*
    //char* filename = &s;     
    
    FastXFile myfasta(s);
    myfasta.setFileName(s);
    
    myfasta.toStream(cout); 

    cout << "Boujour Je m'appel Lylie" << endl;

    return 0;
}
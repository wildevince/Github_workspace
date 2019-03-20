#include "FastXSeq.h"
#include "FastXFile.h"
#include "tools.h"
#include <fstream>

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
    size_t t = sizeof(head);
    for (size_t i = 0; i < t ; ++i) 
    {
        this->header[i] = head[i];
    }
}

void FastXSeq::setHeader(string head) 
{
    if (header) {
        delete[] header;
        header = NULL;
    }
    header = new char[ head.size() ]; 
    size_t t = head.size();
    for (size_t i = 0; i < t ; ++i) 
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
    //os << "\n### coucou le stream XSeq ! ###\n" << endl;
    os << "Header : " << (header? header: "<no header>") << endl;
    os << "positiion sequence dans le fichier : " << start_seq << endl;
    os << "taille Sequence : " << taille_seq << '\n' << endl;
}

void FastXSeq::parseq(ifstream &ifs, string sp){
    //size_t p = ifs.tellg();
    cout << "\t-getting header" <<  endl;
    //
    //ifs.seekg(p);
    //cout << "position avant header : " << ifs.tellg() << endl; 
    //getline(ifs, cp );
    //
    cout <<"the header 'empty' : header  = " << (header? header: "<no header>") << endl;
    cout <<"We've found the header : head  = " << sp.substr(1) << endl;
    setHeader( sp.substr(1) );
    cout <<"the header 'pased' : header  = " << (header? header: "<no header>") << endl;
    //cout <<"So the header : " << header << endl;
    // position du header + taille header 
    //cout << "position apres header : " << ifs.tellg() << endl; 
    setStart( ifs.tellg() );

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
   cout << endl;
}

void FastXSeq::parseqQ(ifstream &ifs, string line)
{
	//A voir si on rajoute un controle bool isNseq = false while(isN Seq) isNseq=(count==)?true:false;
	bool hasN = false;
	do
	{
		// Block Header 
		cout << "Header Trouve :" << line.substr(1) << endl;
		this->setHeader(line.substr(1)); // Recupere l'entete
		// Block SEq
		size_t count = 0;
		hasN = false;
		getline(ifs, line);
		while (line[0] != '+')
		{
			cout << "controle line seq : " << line << endl;
			count += (line.size() - 1) ;// Marcher sur la seq
			hasN = ((line.find('N') == string::npos ? false : true)); // On peut remplacer string::npos par -1
			getline(ifs, line);
		}
		//controle
		cout << "compte =" << count << endl;
		// Block Q
		while (count != 0)
		{
			line = "";
			getline(ifs, line);
			cout << "controle line qual : " << line << endl;
			for (size_t i = 0; i < (line.size() - 1) ; ++i)
			{
				cout << "In the 'for'-terress ^^ joke ^^" << endl;
                if ( !ifspace(line[i]) )
				{
					--count;
                    if (count == 0) {
                        cout << "It is the end : count =" << count << endl;
                        break;
                    }
				}
			}
            int a;
            cin >> a ;
		}
		if (count == 0 && !hasN)
		{
			cout << "Parsing complete " << endl;
			return; //isNseqQ=false
			
		}
	} while (hasN);
    cout << "Mama Mia, here we go again ! " << endl;
	
}

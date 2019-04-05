#include "FastXSeq.h"
#include "FastXFile.h"
#include "tools.h"
#include <fstream>

using namespace std;

//____//____//____/ FastXSeq /____//____//____//

FastXSeq::FastXSeq(char *head, size_t p, size_t t, EncodedSeq *aes) : header(head), start_seq(p), taille_seq(t), es() {
	if (aes) {
		es = *aes;
	}
}

FastXSeq::FastXSeq(const FastXSeq &fx) : header(myStrDup(fx.header)),
										 start_seq(fx.start_seq),
										 taille_seq(fx.taille_seq),
										 es(fx.es) {}

FastXSeq::~FastXSeq()
{
	if (header)
	{
		delete[] header;
	}
}

FastXSeq &FastXSeq::operator=(const FastXSeq &fx)
{
	if (header)
	{
		delete[] header;
	}
	//
	this->header = myStrDup(fx.header);
	this->start_seq = fx.start_seq;
	this->taille_seq = fx.taille_seq;
	this->es = fx.es;
	cout << "Copy Completed" << endl;
	return *this;
}

char FastXSeq::operator[](size_t i)
{
	return this->getSequence().getNucleotide(i);
}

EncodedSeq &FastXSeq::operator+=(const std::string sp)
{
	es += sp; // EncodedSeq::operator+= 
	this->setTaille(es.size()); //Up-to-Date la taille
	return es;
}

char *FastXSeq::getHeader() const
{
	return header;
}

const EncodedSeq& FastXSeq::getSequence() const
{
	return es;
}

size_t FastXSeq::getStart() const
{
	return start_seq;
}
size_t FastXSeq::getSize() const
{
	return taille_seq;
}

void FastXSeq::setHeader(char *head)
{
	if (header)
	{
		delete[] header;
		header = NULL;
	}
	for (size_t i = 0; i < strlen(head); ++i)
	{
		this->header[i] = head[i];
	}
}

void FastXSeq::setHeader(string head)
{
	header = new char[head.size()];
	for (size_t i = 0; i < (head.size() + 1); ++i)
	{
		header[i] = head[i];
	}
}

void FastXSeq::setStart(size_t p)
{
	start_seq = p;
}

void FastXSeq::setTaille(size_t t)
{
	taille_seq = t;
}

void FastXSeq::toStream(ostream &os) const
{
	//os << "\n### coucou le stream XSeq ! ###\n" << endl;
	os << "Header : \n" << (header ? header : "<no header>") << endl;
	os << "positiion sequence dans le fichier : " << start_seq << endl;
	os << "taille Sequence : " << es.size() << '\n' << endl;
	os << "La sequence :\n" << getSequence() << endl;
	   
}

void FastXSeq::parseq(ifstream &ifs, string sp)
{
	bool ignore_seq = false;
	size_t n = 0;
	//size_t p = ifs.tellg();
	cout << "\t-getting header" << endl;
	//
	//ifs.seekg(p);
	//cout << "position avant header : " << ifs.tellg() << endl;
	//getline(ifs, cp );
	//
	//cout <<"We've found the header : " << head << endl;
	setHeader(sp.substr(1));
	//cout <<"So the header : " << header << endl;
	// position du header + taille header
	//cout << "position apres header : " << ifs.tellg() << endl;
	setStart(ifs.tellg());
	//
	//
	//
	char c = ifs.peek();
	//cout << "\tligne 137: Xseq controle du c " << c << endl;
	sp = "";
	ignore_seq = false;
	while (ifs && (c != '>' && c != ';'))
	{
		//if ( c == '>' || c == ';' ) { break; }
		sp = "";
		getline(ifs, sp);
		//cout << "\tla ligne : 143 Xseq "<< sp << endl; 
		for (size_t i = 0; i < sp.size(); ++i) {
			//cout <<"\t controle de sp[i]: 145 " << sp[i] << endl;
			if (ifnucl(sp[i], true)) {
				if (ifnucl(sp[i])) {
					++n;
				} else {
					ignore_seq = true;
					//cout<< "\t Espèce de dégénéré!!!" << endl; 
				}
			} else {
				if (!ifspace(sp[i])) {
					//Erreur dans la séquence à la positon i de la ligne courante
					ignore_seq = true;
					//cout << "\tBla bla et re Bla" << endl;
				}
			}
		}
		c = ifs.peek();
		//cout << "\tcontrole du c : " << c << "	################"<< endl;
	} // end while
	if (!ignore_seq) {
		es.reserve(n);
		ifs.clear();
		ifs.seekg(getStart());
		c = ifs.peek();
		while (ifs && (c != '>' && c != ';'))
		{
			getline(ifs, sp);
			for (size_t i = 0; i < sp.size(); ++i) {
				if (ifnucl(sp[i])) {
					es += sp[i];
				}
			}
			c = ifs.peek();
		}
	} else {
		cout << "\tSéquence ignorée" << endl;
	}
}

void FastXSeq::parseqQ(ifstream &ifs, string line)
{
	//A voir si on rajoute un controle bool isNseq = false while(isN Seq) isNseq=(count==)?true:false;
	bool hasN = false;
	do
	{
		// Block Header
		cout << "Header Trouvé :" << line.substr(1) << endl;
		this->setHeader(line.substr(1)); // Récupère l'entete
		// Block SEq
		setStart(ifs.tellg());
		size_t count = 0;
		bool hasN = false;
		getline(ifs, line);
		while (line[0] != '+')
		{
			cout << "controle line seq : " << line << endl;
			count += line.size() - 1;								  // Marcher sur la seq
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
			//cout << "controle line qual : " << line << endl;
			for (size_t i = 0; i < line.size() - 1; ++i)
			{
				if (!ifspace(line[i]))
				{
					--count;
					if (count == 0)
					{
						cout << "It is the end : count =" << count << endl;
						break;
					}
				}
			}
			int a;
			cin >> a;
		}
		if (count == 0 && !hasN)
		{
			cout << "Parsing complete " << endl;
			return; //isNseqQ=false
		}
	} while (hasN);
}
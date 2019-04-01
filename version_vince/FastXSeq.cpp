#include "FastXSeq.h"
#include "FastXFile.h"
#include "tools.h"
#include <fstream>

using namespace std;

//____//____//____/ FastXSeq /____//____//____//

FastXSeq::FastXSeq(char *head, size_t p, size_t t, EncodedSeq *aes) : header(head), start_seq(p), taille_seq(t), es(aes) {}

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
	if (es)
	{
		delete es;
	}
}

FastXSeq &FastXSeq::operator=(const FastXSeq &fx)
{
	if (header)
	{
		delete[] header;
	}
	if (es)
	{
		delete es;
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
	this->getSequence() += sp; // EncodedSeq::operator+= 
	this->setTaille(es->size()); //Up-to-Date la taille
	return (*es);
}

char *FastXSeq::getHeader() const
{
	return header;
}

EncodedSeq& FastXSeq::getSequence() const
{
	return (*es);
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
	os << "Header : " << (header ? header : "<no header>") << endl;
	os << "positiion sequence dans le fichier : " << start_seq << endl;
	os << "taille Sequence : " << es->size() << '\n'
	   << endl;
}

void FastXSeq::parseq(ifstream &ifs, string sp)
{
	bool hasN = false;
	do
	{
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
		EncodedSeq *aes = new EncodedSeq();
		char c = ifs.peek();
		sp = "";
		hasN = false;
		while (c != '>' || c != ';')
		{
			getline(ifs, sp);
			hasN = (hasN ? true : (sp.find('N') == std::string::npos ? false : true));
			if (!hasN)
			{
				(*aes) += sp;
			}
			c = ifs.peek();
		} // end while
		if (aes->size() == 0 || hasN)
		{
			cout << "\tPas de sequence" << endl;
		}
	} while (hasN); // filtre anti-N
	// (*es) = (*aes);
	//delete aes; 
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
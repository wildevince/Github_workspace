#include <iostream>
#include <string>
#include <algorithm>
//#include <libgen.h>
#include "FastXFile.h"
#include "FastXSeq.h"
#include "encoded_sequence.h"

using namespace std;

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        //cerr << "usage:" << basename(argv[0]) << " <sequence>" << endl;
        cerr << "usage:" << argv[0] << " <sequence>" << endl;
        return 1;
    }
    char *s = argv[1];
    cout << "chaine a verifier: ' " << s << "'" << endl;

    // conversion string to char*
    //char* filename = &s;

    FastXFile myfasta(s);
    myfasta.setFileName(s);
    myfasta.toStream(cout);
    cout << myfasta[0].getSequence() << endl;
    cout << "\n\nBoujour Je m'appel Lylie" << endl;

    return 0;
}

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main( int argc, char** argv) {

    if (argc != 2 ) {
        cerr << "usage:" << basename(argv[0]) << " <sequence>" << endl;
        return 1; 
    }
    string s(argv[1]); 
    cout << "chaine à vérifier: ' " << s << "'"<< endl;
    
    vector<size_t> SA(s.length() );
    //iota (SA.begin(), SA.end(), 0) ; 
    for(size_t i = 0; i < s.length() ; ++i) {
        SA[i] = i; }
    
    cout << "SA = [";
    for (size_t i = 0; i <s.size() ; ++i) {
        cout << (i?", ":"") << SA[i];
    }
    cout << "]" <<endl;
.
.
.
.
.
.
.
.
.
    return 0;
}
 /*
 g++ -Wall -ansi -pedantic ./main.cpp -o runtest

./runtest 
 */


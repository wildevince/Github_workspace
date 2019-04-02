#include "tools.h"
#include <fstream>
#include <cstring>
#include <stddef.h>

using namespace std;



char *myStrDup(char *s) //s = &f.fileName
{
    char *res = NULL;
    if (s)
    {
        size_t n = strlen(s) +1; // N'enleve PAS le +1 d'alban ? 
        //...gentil... la il avait raison ^^
        res = new char[n];
        for (size_t i = 0; i < n; ++i)
        {
            res[i] = s[i];
        }
    }
    return res;
}

bool ifnucl(char c, bool degenerated) {
  return (((c == 'a') || (c == 'A')
        || (c == 'c') || (c == 'C')
        || (c == 'g') || (c == 'G')
        || (c == 't') || (c == 'T')
        || (c == 'u') || (c == 'U'))
        || (degenerated
            && ((c == 'b') || (c == 'B')
             || (c == 'd') || (c == 'D')
             || (c == 'h') || (c == 'H')
             || (c == 'v') || (c == 'V')
             || (c == 'k') || (c == 'K')
             || (c == 'm') || (c == 'M')
             || (c == 'r') || (c == 'R')
             || (c == 'y') || (c == 'Y')
             || (c == 'w') || (c == 'W')
             || (c == 's') || (c == 'S')
             || (c == '-')
             || (c == 'n') || (c == 'N'))));
}

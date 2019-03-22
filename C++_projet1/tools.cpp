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
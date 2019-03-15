#include "tools.h"

#include <stddef.h>
#include <cstring>

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




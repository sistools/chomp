
/* *********************************************************
 * includes
 */

#include "chomp.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>


/* *********************************************************
 * API functions
 */

int
sistool_chomp(
    FILE*   in
,   FILE*   out
,   int     flags
)
{
    int const no_chomp_back =   0 != (SISTOOL_CHOMP_F_NO_CHOMP_BACK & flags);
    int const chomp_front   =   0 != (SISTOOL_CHOMP_F_CHOMP_FRONT   & flags);
    int const flatten       =   0 != (SISTOOL_CHOMP_F_FLATTEN_N     & flags);

    int ch;
    int nlf             =   0;
    int in_front        =   1;

    for (; EOF != (ch = fgetc(in)); )
    {
        if ('\n' == ch)
        {
            ++nlf;
        }
        else
        {
            if (chomp_front)
            {
                if (in_front)
                {
                    nlf = 0;
                }
            }

            if (flatten)
            {
                if (0 != nlf)
                {
                    nlf = 1;
                }
            }

            for (; 0 != nlf; --nlf)
            {
                fputc('\n', out);
            }

            fputc(ch, out);

            in_front = 0;
        }
    }

    if (no_chomp_back)
    {
        if (flatten)
        {
            if (0 != nlf)
            {
                nlf = 1;
            }
        }

        for (; 0 != nlf; --nlf)
        {
            fputc('\n', out);
        }
    }

    return EXIT_SUCCESS;
}


/* ///////////////////// end of file //////////////////// */


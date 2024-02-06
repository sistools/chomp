
#ifndef CHOMP_INCL_H_CHOMP
#define CHOMP_INCL_H_CHOMP

#define SISTOOL_CHOMP_VER_MAJOR         0
#define SISTOOL_CHOMP_VER_MINOR         1
#define SISTOOL_CHOMP_VER_PATCH         0


/* *********************************************************
 * includes
 */

#include <stdio.h>


/* *********************************************************
 * API flags
 */

#define SISTOOL_CHOMP_F_NO_CHOMP_BACK       (0x00000001)
#define SISTOOL_CHOMP_F_CHOMP_FRONT         (0x00000002)
#define SISTOOL_CHOMP_F_FLATTEN_N           (0x00000004)


/* *********************************************************
 * API functions
 */

#ifdef __cplusplus
extern "C"
#endif /* __cplusplus */
int
sistool_chomp(
    FILE*   in
,   FILE*   out
,   int     flags
);

#endif /* !CHOMP_INCL_H_CHOMP */


/* ///////////////////// end of file //////////////////// */


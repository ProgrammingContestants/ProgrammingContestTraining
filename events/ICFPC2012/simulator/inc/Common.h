#ifndef _LAMBDA_COMMON_H
#define _LAMBDA_COMMON_H

#ifdef DEBUG_ON
    #define dbg_cerr cerr
#else
    #define dbg_cerr if (0) cerr
#endif

#endif /* end of include guard */

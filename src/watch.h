#ifndef __FS_WATCH_H_
#ifdef _WIN32

extern "C"
{
    extern int	opterr,
                optind,
                optopt,
                optreset;

    extern char    *optarg;

    int getopt(int nargc, char * const nargv[], const char *ostr);
}
#else
#include <unistd.h>
#endif
#endif __FS_WATCH_H_
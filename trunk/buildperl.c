/*
 * Experimental Perl code in Build.
 *
 *  Written by Ryan C. Gordon. (icculus@clutteredmind.org)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file IS NOT A PART OF Ken Silverman's original release
 */

#include <EXTERN.h>
#include <perl.h>

#include "buildperl.h"

static PerlInterpreter *perl = NULL;
static char *embedding[] = { "", "game.pl" };
//static char *args[] = { NULL };
static SV *framefunc = NULL;
//static SV *ref_framefunc = NULL;
static HV *stash = NULL;

int buildperl_init(void)
{
    int retval = -1;

    printf("initializing perl...\n");

    perl = perl_alloc();
    if (perl == NULL)
        printf("no memory!");
    else
    {
        perl_construct(perl);

        if (perl_parse(perl, NULL, 2, embedding, NULL) == 0)
        {
            printf("perl initialization was successful.\n"
                   "running perl mainline...\n");
            perl_run(perl);
            printf("perl mainline complete.\n");
            retval = 0;

//            framefunc = get_sv("BUILD_frame", FALSE);

            stash = gv_stashpv("main", FALSE);
            if (stash == NULL)
                printf("main stash is NULL!\n");
            else
            {
                framefunc = *(hv_fetch(stash, "BUILD_frame", 11, FALSE));
                if (framefunc == NULL)
                    printf("framefunc == NULL!\n");
            }
        } // if
        else
        {
            printf("perl_parse() failed!\n");
            perl_destruct(perl);
            perl_free(perl);
            perl = NULL;
        } // else
    } // else

    return(retval);
} // initialize_perl


void buildperl_frame(void)
{
    dSP;

    PUSHMARK(SP);

    if (perl != NULL)
    {
//        call_argv("BUILD_frame", G_DISCARD | G_NOARGS, args);
        call_sv(framefunc, G_DISCARD | G_NOARGS);
    } // if
} // buildperl_frame


void buildperl_deinit(void)
{
    printf("buildperl_deinit() called.\n");

    if (perl != NULL)
    {
        perl_destruct(perl);
        perl_free(perl);
        perl = NULL;
        printf("perl interpreter cleanup successful.\n");
    } // if
} // buildperl_deinit

// end of buildperl.c ...


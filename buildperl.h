/*
 * Experimental Perl code in Build, include file.
 *
 *  Written by Ryan C. Gordon. (icculus@clutteredmind.org)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.
// This file IS NOT A PART OF Ken Silverman's original release

#ifndef _INCLUDE_BUILDPERL_H_
#define _INCLUDE_BUILDPERL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if (!defined USE_PERL)
#error Please define USE_PERL before including this file.
#endif

int buildperl_init(void);
void buildperl_frame(void);
void buildperl_deinit(void);

#ifdef __cplusplus
}
#endif

#endif // include-once-blocker.

// end of buildperl.h ...

/* sunos4.h

   System dependencies for SunOS 4 (tested on 4.1.4)... */


/*
 * Copyright 1996 The Board of Trustees of The Leland Stanford
 * Junior University. All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies.  Stanford University
 * makes no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 *
 * This file was contributed by Jonathan Stone.
 */

/*
 * Copyright (c) 1996 The Internet Software Consortium.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of RadioMail Corporation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY RADIOMAIL CORPORATION AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * RADIOMAIL CORPORATION OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#define u_int8_t	unsigned char 	/* Not quite POSIX... */
#define u_int16_t	unsigned short 
#define u_int32_t	unsigned long 

/* The jmp_buf type is an array on SunOS, so we can't dereference it
   and must declare it differently. */
#define jbp_decl(x)	jmp_buf x
#define jref(x)		(x)
#define jdref(x)	(x)
#define jrefproto	jmp_buf

/* struct ether_host source and destination are structs on SunOS. */
#ifndef ETHER_SRC
# define ETHER_SRC(x)	(&((x) -> ether_shost))
#endif
#ifndef ETHER_DEST
# define ETHER_DEST(x)	(&((x) -> ether_dhost))
#endif

#include <syslog.h>
#include <sys/types.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <limits.h>
#include <poll.h>

extern int h_errno;

#include <net/if.h>
#include <net/if_arp.h>

/*
 * Definitions for IP type of service (ip_tos)
 */
#define IPTOS_LOWDELAY          0x10
#define IPTOS_THROUGHPUT        0x08
#define IPTOS_RELIABILITY       0x04
/*      IPTOS_LOWCOST           0x02 XXX */

/* SunOS systems don't have /var/run, but some sites have added it.
   If you want to put dhcpd.pid in /var/run, define _PATH_DHCPD_PID
   in site.h. */
#ifndef _PATH_DHCPD_PID
#define _PATH_DHCPD_PID	"/etc/dhcpd.pid"
#endif

#ifdef __GNUC__
/* Varargs stuff: use stdarg.h instead ... */
#include <stdarg.h>
#define VA_DOTDOTDOT ...
#define VA_start(list, last) va_start (list, last)
#define va_dcl
#else /* !__GNUC__*/
/* Varargs stuff... */
#include <varargs.h>
#define VA_DOTDOTDOT va_alist
#define VA_start(list, last) va_start (list)
#endif /* !__GNUC__*/

/* SunOS doesn't support limited sprintfs. */
#define vsnprintf(buf, size, fmt, list) vsprintf (buf, fmt, list)
#define NO_SNPRINTF

/* SunOS doesn't supply strerror... */
#define NO_STRERROR
char *strerror PROTO ((int));

/* SunOS select() doesn't work on streams, so we have to use poll -
   as usual, SysV can't do networking to save its life. */
#define USE_POLL

/* By default, use NIT API for receiving and sending packets... */
#if defined (USE_DEFAULT_NETWORK)
#  define USE_NIT
#endif

#define EOL	'\n'
#define VOIDPTR	void *

/*
 * Time stuff...
 *
 * Definitions for an ISC DHCPD system that uses time_t
 * to represent time internally as opposed to, for example,  struct timeval.)
 */

#include <time.h>

#define TIME time_t
#define GET_TIME(x)	time ((x))
#define TIME_DIFF(high, low)	 	(*(high) - *(low))
#define SET_TIME(x, y)	(*(x) = (y))
#define ADD_TIME(d, s1, s2) (*(d) = *(s1) + *(s2))
#define SET_MAX_TIME(x)	(*(x) = INT_MAX)

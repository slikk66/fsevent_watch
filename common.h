#ifndef fsevent_watch_common_h
#define fsevent_watch_common_h

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <unistd.h>
#include "compat.h"

#define _str(s) #s
#define _xstr(s) _str(s)

#define COMPILED_AT __DATE__ " " __TIME__

#define FPRINTF_FLAG_CHECK(flags, flag, msg, fd)  \
  do {                                            \
    if ((flags) & (flag)) {                       \
      fprintf(fd, "%s\n", msg); } }               \
  while (0)

#define FLAG_CHECK_STDERR(flags, flag, msg)       \
        FPRINTF_FLAG_CHECK(flags, flag, msg, stderr)

/*
 * FSEVENTSBITS:
 * generated by `make printflags` (and pasted here)
 * flags MUST be ordered (bits ascending) and sorted
 *
 * idea from: http://www.openbsd.org/cgi-bin/cvsweb/src/sbin/ifconfig/ifconfig.c (see printb())
 */
#define	FSEVENTSBITS \
"\1mustscansubdirs\2userdropped\3kerneldropped\4eventidswrapped\5historydone\6rootchanged\7mount\10unmount\11created\12removed\13inodemetamod\14renamed\15modified\16finderinfomod\17changeowner\20xattrmod\21isfile\22isdir\23issymlink\24ownevent"

static inline void
sprintb(char *buf, unsigned short v, char *bits)
{
        int i, any = 0;
        char c;
	char *bufp = buf;

	while ((i = *bits++)) {
		if (v & (1 << (i-1))) {
			if (any)
				*bufp++ = ',';
			any = 1;
			for (; (c = *bits) > 32; bits++)
				*bufp++ = c;
		} else
			for (; *bits > 32; bits++)
				;
	}
	*bufp = '\0';
}

#endif /* fsevent_watch_common_h */

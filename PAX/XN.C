/*++

Copyright 1992 DataFocus Incorporated

Module Name:

	xn.c

Abstract:

	Create mknod, seekdir, and telldir for use with Windows NT POSIX.

Author:

	Christian Carey	(xn@DataFocus.COM)	28-May-1993

Notes:

	This was written for the X86 implementation. It would probably be best
	to test this on other architectures as well.

Revision History:

	28-May-1993	xn@DataFocus.COM

		Initial version.

--*/

#define DIR_DEBUG 0

#if DIR_DEBUG
#include <stdio.h>
#endif
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

signed int mknod (const char *path, mode_t mode, dev_t dev)
{
	signed int status;
	mode_t file_type;

	if (&dev == NULL)
	{
		;
	}
	file_type = mode & S_IFMT;
	if (file_type == S_IFIFO)
	{
		status = mkfifo(path, mode);
	}
	else if (file_type == S_IFDIR)
	{
		status = mkdir(path, mode);
	}
	else
	{
		status = -1;
		errno = ENOSYS;
	}
	return status;
}

void seekdir (DIR *dirp, off_t loc)
{
	unsigned int entries;

#if DIR_DEBUG
	(void) fprintf(stderr, "xn.c/seekdir - loc: %ld\n", (signed long) loc);
	(void) fflush(stderr);
#endif
	if (dirp == NULL)
	{
		errno = EFAULT;
	}
	else if (dirp->Directory < 0 || dirp->Directory >= OPEN_MAX)
	{
		errno = EBADF;
	}
	else if (loc < (off_t) 0)
	{
		errno = EINVAL;
	}
	else
	{
		rewinddir(dirp);
		entries = (unsigned int) (loc/sizeof(struct dirent));
#if DIR_DEBUG
		(void) fprintf(stderr, "xn.c/seekdir - entries: %u\n", entries);
		(void) fflush(stderr);
#endif
		while (entries--)
		{
			(void) readdir(dirp);
		}
	}
}

off_t telldir (DIR *dirp)
{
	off_t status;

	if (dirp == NULL)
	{
		status = (off_t) -1;
		errno = EFAULT;
	}
	else if (dirp->Directory < 0 || dirp->Directory >= OPEN_MAX)
	{
		status = (off_t) -1;
		errno = EBADF;
	}
	else
	{
		status = (off_t) dirp->Index * sizeof(struct dirent);
	}
#if DIR_DEBUG
	(void) fprintf(stderr, "xn.c/telldir - returning %ld\n", (signed long) status);
	(void) fflush(stderr);
#endif
	return status;
}

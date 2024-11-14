//-----------------------------------------------------------------------------
//
// Copyright(C) 2020 Zoe Elsie Watson
//
// See COPYLIB for license information.
//
//-----------------------------------------------------------------------------
//
// Header for target library libc.
//
//-----------------------------------------------------------------------------

#ifndef __GDCC_Header__C__sys__mman_h__
#define __GDCC_Header__C__sys__mman_h__

#include <bits/types.h>
#include <errno.h>

//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// PROT_*
//
#define PROT_NONE  0
#define PROT_EXEC  1
#define PROT_WRITE 2
#define PROT_READ  4

//
// MAP_*
//
#define MAP_FIXED   1
#define MAP_PRIVATE 2
#define MAP_SHARED  4

//
// MS_*
//
#define MS_ASYNC      1
#define MS_INVALIDATE 2
#define MS_SYNC       4

//
// MCL_*
//
#define MCL_CURRENT 1
#define MCL_FUTURE  2

//
// POSIX_MADV_*
//
#define POSIX_MADV_DONTNEED   0
#define POSIX_MADV_NORMAL     1
#define POSIX_MADV_RANDOM     2
#define POSIX_MADV_SEQUENTIAL 3
#define POSIX_MADV_WILLNEED   4

//
// POSIX_TYPED_MEM_*
//
#define POSIX_TYPED_MEM_ALLOCATE        1
#define POSIX_TYPED_MEM_ALLOCATE_CONTIG 2
#define POSIX_TYPED_MEM_MAP_ALLOCATABLE 4

//
// These may be defined as macros, and so will be given placeholder
// implementations.
//
#define mlock(adr, len)                             (errno = ENOSYS, -1)
#define mlockall(flags)                             (errno = ENOSYS, -1)
#define mmap(adr, len, prot, flags, fdes, off)      (errno = ENOSYS, (void *)0)
#define mprotect(adr, len, prot)                    (errno = ENOSYS, -1)
#define msync(adr, len, flags)                      (errno = ENOSYS, -1)
#define munlock(adr, len)                           (errno = ENOSYS, -1)
#define munlockall()                                (errno = ENOSYS, -1)
#define munmap(adr, len)                            (errno = ENOSYS, -1)
#define posix_madvise(adr, len, advice)             (errno = ENOSYS, -1)
#define posix_mem_offset(adr, len, off, clen, fdes) (errno = ENOSYS, -1)
#define posix_typed_mem_get_info(fildes, info)      (errno = ENOSYS, -1)
#define posix_typed_mem_open(name, oflag, tflag)    (errno = ENOSYS, -1)
#define shm_open(name, oflag, mode)                 (errno = ENOSYS, -1)
#define shm_unlink(name)                            (errno = ENOSYS, -1)


//----------------------------------------------------------------------------|
// Types                                                                      |
//

//
// mode_t
//
#ifndef __GDCC_Have__mode_t__
#define __GDCC_Have__mode_t__
typedef __mode_t mode_t;
#endif

//
// off_t
//
#ifndef __GDCC_Have__off_t__
#define __GDCC_Have__off_t__
typedef __off_t off_t;
#endif

//
// size_t
//
#ifndef __GDCC_Have__size_t__
#define __GDCC_Have__size_t__
typedef __size_t size_t;
#endif

//
// posix_typed_mem_info
//
struct posix_typed_mem_info
{
   size_t posix_tmi_length;
};

#endif//__GDCC_Header__C__sys__mman_h__

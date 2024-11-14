//-----------------------------------------------------------------------------
//
// Copyright(C) 2014-2017 David Hill, 2020 Zoe Elsie Watson
//
// See COPYLIB for license information.
//
//-----------------------------------------------------------------------------
//
// String handling.
//
//-----------------------------------------------------------------------------

#define _GNU_SOURCE

#include <string.h>

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

#if __GDCC_Family__ZDACS__
#include <ACS_ZDoom.h>
#endif


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// StrStrImpl
//
#define StrStrImpl(type, conv, name_case, name_str) \
   size_t wordLen = strlen##name_str(word); \
   \
   /* Special cases. */ \
   if(wordLen == 0) return (type *)text; \
   if(wordLen == 1) return str##name_case##chr##name_str(text, *word); \
   \
   /* Allocate partial match table. */ \
   size_t wordTabAuto[128], *wordTab; \
   if(wordLen <= 128) \
      wordTab = wordTabAuto; \
   else \
      wordTab = malloc(sizeof(size_t) * wordLen); \
   \
   /* Memory exhaustion, fall back to a no alloc algorithm. */ \
   if(!wordTab) \
   { \
      while((text = str##name_case##chr##name_str(text, *word))) \
      { \
         for(type const *textItr = text + 1, *wordItr = word + 1;; ++textItr, ++wordItr) \
         { \
            if(!*wordItr) return (type *)text; \
            if(!*textItr) return NULL; \
            \
            if(conv(*textItr) != conv(*wordItr)) break; \
         } \
         \
         ++text; \
      } \
      \
      return NULL; \
   } \
   \
   /* Index 0 has special handling, so just leave wordTab[0] alone entirely. */ \
   wordTab[1] = 0; \
   \
   /* Compute partial match table. */ \
   for(size_t pos = 2, cnd = 0; pos != wordLen;) \
   { \
      if(conv(word[cnd]) == conv(word[pos - 1])) \
         wordTab[pos++] = ++cnd; \
      else if(cnd) \
         cnd = wordTab[cnd]; \
      else \
         wordTab[pos++] = 0; \
   } \
   \
   /* Perform search. */ \
   type const *textItr = text; \
   type const *textEnd = text + strlen##name_str(text); \
   size_t      wordIdx = 0; \
   \
   while(textItr + wordIdx != textEnd) \
   { \
      /* Character match? */ \
      if(conv(word[wordIdx]) == conv(textItr[wordIdx])) \
      { \
         /* Word match? */ \
         if(++wordIdx == wordLen) \
         { \
            if(wordTab != wordTabAuto) free(wordTab); \
            return (type *)textItr; \
         } \
      } \
      else \
      { \
         /* Not at start of word match? */ \
         if(wordIdx) \
         { \
            textItr += wordIdx - wordTab[wordIdx]; \
            wordIdx = wordTab[wordIdx]; \
         } \
         \
         /* First character failure, just advance text iterator. */ \
         else \
            ++textItr; \
      } \
   } \
   \
   if(wordTab != wordTabAuto) free(wordTab); \
   return NULL;


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

//=========================================================
// Copying functions.
//

//
// memcpy
//
void *memcpy(void *restrict s1, void const *restrict s2, size_t n)
{
   char       *i1 = s1;
   char const *i2 = s2;

   while(n--)
      *i1++ = *i2++;

   return s1;
}

//
// memmove
//
void *memmove(void *s1, void const *s2, size_t n)
{
   if(s1 < s2)
   {
      char       *i1 = s1;
      char const *i2 = s2;

      while(n--)
         *i1++ = *i2++;
   }
   else
   {
      char       *i1 = (char       *)s1 + n;
      char const *i2 = (char const *)s2 + n;

      while(n--)
         *--i1 = *--i2;
   }

   return s1;
}

//
// strcpy
//
char *strcpy(char *restrict s1, char const *restrict s2)
{
   for(char *i = s1; (*i = *s2); ++i, ++s2) {}

   return s1;
}

//
// strncpy
//
char *strncpy(char *restrict s1, char const *restrict s2, size_t n)
{
   char *i = s1;

   for(; (*i = *s2) && n; --n, ++i, ++s2) {}

   for(; n; --n) *i++ = 0;

   return s1;
}

//=========================================================
// Concatenation functions.
//

//
// strcat
//
char *strcat(char *restrict s1, char const *restrict s2)
{
   char *i = s1;

   while(*i) ++i;

   for(; (*i = *s2); ++i, ++s2) {}

   return s1;
}

//
// strncat
//
char *strncat(char *restrict s1, char const *restrict s2, size_t n)
{
   char *i = s1;

   while(*i) ++i;

   char *end = i + n;

   while(*s2 && n--) *i++ = *s2++;

   *i = 0;

   return s1;
}

//=========================================================
// Comparison functions.
//

//
// memcmp
//
int memcmp(void const *s1, void const *s2, size_t n)
{
   for(char const *i1 = s1, *i2 = s2; n--; ++i1, ++i2)
   {
      if(*i1 != *i2)
         return *i1 - *i2;
   }

   return 0;
}

//
// strcmp
//
int strcmp(char const *s1, char const *s2)
{
   for(; *s1 && *s2; ++s1, ++s2)
   {
      if(*s1 != *s2)
         return *s1 - *s2;
   }

   return *s1 - *s2;
}

//
// strcoll
//
int strcoll(char const *s1, char const *s2)
{
   return strcmp(s1, s2);
}

//
// strncmp
//
int strncmp(char const *s1, char const *s2, size_t n)
{
   for(; *s1 && *s2 && n--; ++s1, ++s2)
   {
      if(*s1 != *s2)
         return *s1 - *s2;
   }

   return *s1 - *s2;
}

//
// strxfrm
//
size_t strxfrm(char *restrict s1, char const *restrict s2, size_t n)
{
   size_t n2 = strlen(s2);

   if(n2 >= n) return n2;

   memcpy(s1, s2, n2 + 1);
   return n2;
}

//=========================================================
// Search functions
//

//
// memchr
//
void *memchr(void const *s, int c, size_t n)
{
   for(char const *i = s; n--; ++i)
   {
      if(*i == (char)c)
         return (void *)i;
   }

   return NULL;
}

//
// strchr
//
char *strchr(char const *s, int c)
{
   do
   {
      if(*s == (char)c)
         return (char *)s;
   }
   while(*s++);

   return NULL;
}

//
// strcspn
//
size_t strcspn(char const *s1, char const *s2)
{
   char const *i = s1;

   while(*i && strchr(s2, *i)) ++i;

   return i - s1;
}

//
// strpbrk
//
char *strpbrk(char const *s1, char const *s2)
{
   while(*s1)
   {
      if(strchr(s2, *s1))
         return (char *)s1;

      ++s1;
   }

   return NULL;
}

//
// strrchr
//
char *strrchr(char const *s, int c)
{
   char const *found = NULL;

   do
   {
      if(*s == (char)c)
         found = s;
   }
   while(*s++);

   return (char *)found;
}

//
// strspn
//
size_t strspn(char const *s1, char const *s2)
{
   size_t n = 0;

   while(*s1 && strchr(s2, *s1++)) ++n;

   return n;
}

//
// strstr
//
char *strstr(char const *text, char const *word)
{
   StrStrImpl(char,,,);
}

//
// strtok
//
char *strtok(char *restrict s1, char const *restrict s2)
{
   static char *tok;

   char *tmp;

   if(s1) tok = s1;

   if(!tok) return NULL;

   // Skip any separators.
   tok += strcspn(tok, s2);

   // If tok points to the null-terminator, there are no more tokens.
   if(!*tok) return NULL;

   // Store the pointer to the token in a temporary.
   tmp = tok;

   // Look for the end of the token.
   tok = strpbrk(tok, s2);

   // If no end is found, then we're at the last token.
   if(!tok) return tmp;

   // Null-terminate the token and point to the start of the next.
   *tok++ = 0;

   return tmp;
}

//=========================================================
// Miscellaneous functions.
//

//
// memset
//
void *memset(void *s, int c, size_t n)
{
   for(char *i = s; n--;)
      *i++ = (char)c;

   return s;
}

//
// strerror
//
char *strerror(int errnum)
{
   switch(errnum)
   {
   case E2BIG:           return (char *)"argument list too long";
   case EACCES:          return (char *)"permission denied";
   case EADDRINUSE:      return (char *)"address already in use";
   case EADDRNOTAVAIL:   return (char *)"address not available";
   case EAFNOSUPPORT:    return (char *)"address family not supported";
   case EAGAIN:          return (char *)"resource temporarily unavailable";
   case EALREADY:        return (char *)"connection already in progress";
   case EBADE:           return (char *)"invalid exchange";
   case EBADF:           return (char *)"bad file descriptor";
   case EBADFD:          return (char *)"file descriptor in bad state";
   case EBADMSG:         return (char *)"bad message";
   case EBADR:           return (char *)"invalid request descriptor";
   case EBADRQC:         return (char *)"invalid request code";
   case EBADSLT:         return (char *)"invalid slot";
   case EBUSY:           return (char *)"device or resource busy";
   case ECANCELED:       return (char *)"operation canceled";
   case ECHILD:          return (char *)"no child process";
   case ECHRNG:          return (char *)"channel number out of range";
   case ECOMM:           return (char *)"communication error on send";
   case ECONNABORTED:    return (char *)"connection aborted";
   case ECONNREFUSED:    return (char *)"connection refused";
   case ECONNRESET:      return (char *)"connection reset";
   case EDEADLK:         return (char *)"resource deadlock avoided";
   case EDEADLOCK:       return (char *)"file locking deadlock error";
   case EDESTADDRREQ:    return (char *)"destination address required";
   case EDOM:            return (char *)"out of domain";
   case EDQUOT:          return (char *)"disk quota exceeded";
   case EEXIST:          return (char *)"file exists";
   case EFAULT:          return (char *)"bad address";
   case EFBIG:           return (char *)"file too large";
   case EHOSTDOWN:       return (char *)"host is down";
   case EHOSTUNREACH:    return (char *)"host is unreachable";
   case EHWPOISON:       return (char *)"memory page has hardware error";
   case EIDRM:           return (char *)"identifier removed";
   case EILSEQ:          return (char *)"illegal byte sequence";
   case EINPROGRESS:     return (char *)"operation in progress";
   case EINTR:           return (char *)"interrupted function call";
   case EINVAL:          return (char *)"invalid argument";
   case EIO:             return (char *)"input/output error";
   case EISCONN:         return (char *)"socket is connected";
   case EISDIR:          return (char *)"is a directory";
   case EISNAM:          return (char *)"is a named type file";
   case EKEYEXPIRED:     return (char *)"key has expired";
   case EKEYREJECTED:    return (char *)"key was rejected by service";
   case EKEYREVOKED:     return (char *)"key has been revoked";
   case EL2HLT:          return (char *)"level 2 halted";
   case EL2NSYNC:        return (char *)"level 2 not synchronized";
   case EL3HLT:          return (char *)"level 3 halted";
   case EL3RST:          return (char *)"level 3 reset";
   case ELIBACC:         return (char *)"cannot access a needed shared object";
   case ELIBBAD:         return (char *)"accessing a corrupted shared object";
   case ELIBMAX:         return (char *)"attempting to link too many objects";
   case ELIBSCN:         return (char *)"section corrupted";
   case ELIBEXEC:        return (char *)"cannot exec shared object";
   case ELNRANGE:        return (char *)"link number out of range";
   case ELOOP:           return (char *)"too many levels of symbolic links";
   case EMEDIUMTYPE:     return (char *)"wrong medium type";
   case EMFILE:          return (char *)"too many open files";
   case EMLINK:          return (char *)"too many links";
   case EMSGSIZE:        return (char *)"message too long";
   case EMULTIHOP:       return (char *)"multihop attempted";
   case ENAMETOOLONG:    return (char *)"filename too long";
   case ENETDOWN:        return (char *)"network is down";
   case ENETRESET:       return (char *)"connection aborted by network";
   case ENETUNREACH:     return (char *)"network unreachable";
   case ENFILE:          return (char *)"too many open files";
   case ENOANO:          return (char *)"no anode";
   case ENOBUFS:         return (char *)"no buffer space available";
   case ENODATA:         return (char *)"no message on read queue";
   case ENODEV:          return (char *)"no such device";
   case ENOENT:          return (char *)"no such file or directory";
   case ENOEXEC:         return (char *)"exec format error";
   case ENOKEY:          return (char *)"required key not available";
   case ENOLCK:          return (char *)"no locks available";
   case ENOLINK:         return (char *)"link has been severed";
   case ENOMEDIUM:       return (char *)"no medium found";
   case ENOMEM:          return (char *)"cannot allocate memory";
   case ENOMSG:          return (char *)"no message of desired type";
   case ENONET:          return (char *)"not on a network";
   case ENOPKG:          return (char *)"package not installed";
   case ENOPROTOOPT:     return (char *)"protocol not available";
   case ENOSPC:          return (char *)"no space left on device";
   case ENOSR:           return (char *)"no stream resources";
   case ENOSTR:          return (char *)"not a stream";
   case ENOSYS:          return (char *)"function not implemented";
   case ENOTBLK:         return (char *)"block device required";
   case ENOTCONN:        return (char *)"socket not connected";
   case ENOTDIR:         return (char *)"not a directory";
   case ENOTEMPTY:       return (char *)"directory not empty";
   case ENOTRECOVERABLE: return (char *)"state not recoverable";
   case ENOTSOCK:        return (char *)"not a socket";
   case ENOTSUP:         return (char *)"operation not supported";
   case ENOTTY:          return (char *)"inappropriate control operation";
   case ENOTUNIQ:        return (char *)"name not unique on network";
   case ENXIO:           return (char *)"no such device or address";
   case EOPNOTSUPP:      return (char *)"operation not supported on socket";
   case EOVERFLOW:       return (char *)"value too large to be stored";
   case EOWNERDEAD:      return (char *)"owner died";
   case EPERM:           return (char *)"operation not permitted";
   case EPFNOSUPPORT:    return (char *)"protocol family not supported";
   case EPIPE:           return (char *)"broken pipe";
   case EPROTO:          return (char *)"protocol error";
   case EPROTONOSUPPORT: return (char *)"protocol not supported";
   case EPROTOTYPE:      return (char *)"protocol wrong type for socket";
   case ERANGE:          return (char *)"result too large";
   case EREMCHG:         return (char *)"remote address changed";
   case EREMOTE:         return (char *)"object is remote";
   case EREMOTEIO:       return (char *)"remote i/o error";
   case ERESTART:        return (char *)"interrupted system call";
   case ERFKILL:         return (char *)"operation impossible from rf-kill";
   case EROFS:           return (char *)"read-only filesystem";
   case ESHUTDOWN:       return (char *)"cannot send after endpoint shutdown";
   case ESPIPE:          return (char *)"invalid seek";
   case ESOCKTNOSUPPORT: return (char *)"socket type not supported";
   case ESRCH:           return (char *)"no such process";
   case ESTALE:          return (char *)"stale file handle";
   case ESTRPIPE:        return (char *)"streams pipe error";
   case ETIME:           return (char *)"timer expired";
   case ETIMEDOUT:       return (char *)"connection timed out";
   case ETOOMANYREFS:    return (char *)"too many references";
   case ETXTBSY:         return (char *)"text file busy";
   case EUCLEAN:         return (char *)"structure needs cleaning";
   case EUNATCH:         return (char *)"protocol driver not attached";
   case EUSERS:          return (char *)"too many users";
   case EWOULDBLOCK:     return (char *)"operation would block";
   case EXDEV:           return (char *)"improper link";
   case EXFULL:          return (char *)"exchange full";
   default:              return (char *)"unknown error";
   }
}

//
// strlen
//
size_t strlen(char const *s)
{
   size_t n = 0;

   while(*s++) ++n;

   return n;
}

//=========================================================
// GNU extensions.
//

//
// strcasestr
//
char *strcasestr(char const *text, char const *word)
{
   StrStrImpl(char, toupper, case,);
}

//=========================================================
// Implementation extensions.
//

//
// strcasechr
//
char *strcasechr(char const *s, int c)
{
   c = toupper(c);

   do
   {
      if(toupper(*s) == (char)c)
         return (char *)s;
   }
   while(*s++);

   return NULL;
}

//
// strcasechr_str
//
char __str_ars *strcasechr_str(char __str_ars const *s, int c)
{
   c = toupper(c);

   do
   {
      if(toupper(*s) == (char)c)
         return (char __str_ars *)s;
   }
   while(*s++);

   return NULL;
}

//
// strcasestr_str
//
char __str_ars *strcasestr_str(char __str_ars const *text, char __str_ars const *word)
{
   StrStrImpl(char __str_ars, toupper, case, _str);
}

//
// strchr_str
//
char __str_ars *strchr_str(char __str_ars const *s, int c)
{
   do
   {
      if(*s == (char)c)
         return (char __str_ars *)s;
   }
   while(*s++);

   return NULL;
}

//
// strlen_str
//
size_t strlen_str(char __str_ars const *s)
{
   #if __GDCC_Family__ZDACS__
   {
      union {char __str_ars const *s; struct {__str lo; int hi;};} u = {s};

      if(!u.hi) return ACS_StrLen(u.lo);

      int n = ACS_StrLen(u.lo);
      if(n <= u.hi)
         return u.hi - n;
   }
   #endif

   size_t n = 0;

   while(*s++) ++n;

   return n;
}

//
// strstr_str
//
char __str_ars *strstr_str(char __str_ars const *text, char __str_ars const *word)
{
   StrStrImpl(char __str_ars,,, _str);
}

// EOF

#ifndef TCHAR_H_COMPAT
#define TCHAR_H_COMPAT

// Compatibility header for tchar.h on non-Windows platforms
// tchar.h is Windows-specific for Unicode/ANSI string handling

#ifndef _WIN32

// Define TCHAR types for non-Windows platforms
typedef char TCHAR;
typedef char _TCHAR;

// String manipulation macros
#define _T(x) x
#define _TEXT(x) x

// String functions
#define _tprintf printf
#define _ftprintf fprintf
#define _stprintf sprintf
#define _sntprintf snprintf
#define _vtprintf vprintf
#define _vftprintf vfprintf
#define _vstprintf vsprintf
#define _vsntprintf vsnprintf
#define _tscanf scanf
#define _stscanf sscanf
#define _fgetts fgets
#define _fputts fputs
#define _getts gets
#define _putts puts
#define _tmain main
#define _tWinMain WinMain
#define _tenviron environ
#define __targv __argv

// String operations
#define _tcscat strcat
#define _tcschr strchr
#define _tcscmp strcmp
#define _tcscpy strcpy
#define _tcscspn strcspn
#define _tcsdup strdup
#define _tcslen strlen
#define _tcsncat strncat
#define _tcsncmp strncmp
#define _tcsncpy strncpy
#define _tcspbrk strpbrk
#define _tcsrchr strrchr
#define _tcsspn strspn
#define _tcsstr strstr
#define _tcstod strtod
#define _tcstol strtol
#define _tcstoul strtoul
#define _tcsxfrm strxfrm
#define _tcstok strtok
#define _tcsftime strftime

// Character classification
#define _istdigit isdigit
#define _istspace isspace
#define _istalpha isalpha
#define _istalnum isalnum
#define _istpunct ispunct
#define _istupper isupper
#define _istlower islower
#define _totlower tolower
#define _totupper toupper

// File operations
#define _tfopen fopen
#define _tfreopen freopen
#define _tperror perror
#define _tremove remove
#define _trename rename

#endif // _WIN32

#endif // TCHAR_H_COMPAT

/// @file
/// @brief stringification macros

#ifndef STRINGIFY_H
#define STRINGIFY_H

#define _TOSTR(s) __TOSTR(s)
#define __TOSTR(s) #s

#define XSTRINGIFY(s)       STRINGIFY(s)
#define STRINGIFY(s)        #s

#define __xstringify(s)     __stringify(s)
#define __stringify(s)      #s

#define _CONCAT(s1,s2) s1##s2

#endif

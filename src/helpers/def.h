#ifndef CGEN_DEF_H
#define CGEN_DEF_H

#define bool unsigned short
#define true 1
#define false 0

#ifdef _WIN32
#define OS "windows"
#endif
#ifdef _WIN64
#define OS "windows"
#endif
#ifdef __linux__
#define OS "linux"
#endif
#ifdef __APPLE__
#define OS "macos"
#endif
#ifdef __MACH__
#define OS "macos"
#endif
#ifdef __FreeBSD__
#define OS "freebsd"
#endif
#ifndef OS
#define OS "unknown"
#endif

#endif

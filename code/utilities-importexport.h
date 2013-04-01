#ifndef UTILITIES_IMPORTEXPORT_H
#define UTILITIES_IMPORTEXPORT_H

#ifndef DLL_EXPORT
#ifdef WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
#endif

#ifndef DLL_IMPORT
#ifdef WIN32
#define DLL_IMPORT __declspec(dllimport)
#else
#define DLL_IMPORT
#endif
#endif

#ifdef UTILITIES_EXPORT
  #define UTILITIES_LIB DLL_EXPORT
#else
  #define UTILITIES_LIB DLL_IMPORT
#endif

#endif

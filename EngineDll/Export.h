#ifndef EXPORT_H
#define EXPORT_H

#ifdef DLL_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

//#define DllExport __declspec( dllexport )

#endif
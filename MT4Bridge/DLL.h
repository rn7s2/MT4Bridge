#pragma once

#if defined _WIN32
#ifdef MT4BRIDGE_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT __attribute__((dllimport))
#endif

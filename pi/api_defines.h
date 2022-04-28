#pragma once

#ifdef _USRDLL
#ifdef _WIN32
#define API __declspec(dllexport)
#endif
#else
#ifdef _WIN32
#define API __declspec(dllimport)
#endif
#endif
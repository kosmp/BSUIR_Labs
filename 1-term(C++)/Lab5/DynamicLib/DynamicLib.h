#pragma once
#include <iostream>
using namespace std;
#ifdef DYNAMICLIB_EXPORTS
#define DYNAMICLIB_API __declspec(dllexport)
#else
#define DYNAMICLIB_API __declspec(dllimport)
#endif

DYNAMICLIB_API int checkSymbolsPositive(int& n, char* st);
DYNAMICLIB_API int checkSymbols(int& n, char* st);
DYNAMICLIB_API int checkAndEnterSizeArray(int& n);
DYNAMICLIB_API int enterArray(int* arr, int i);
DYNAMICLIB_API bool func(int left, int right, int* arr);

/*
	2017.08.22
	Created by AcrylicShrimp.
*/

#ifndef _UIE_DLL

#define _UIE_DLL

#ifdef _UIE_BUILD

#define UIE_DLL __declspec(dllexport)

#else

#define UIE_DLL __declspec(dllimport)

#endif

#endif
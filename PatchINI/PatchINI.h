// ============================================================================
//  PatchINI.h
// ============================================================================
#pragma once		

#include "wexception.h"
#include "wstring_make.h"


// ============================================================================
//  constants
// ============================================================================
namespace mergeCmds 
{
	const wchar_t setOrAppend = 0; // no character
	const wchar_t appendif = '+';
	const wchar_t removeif = '-';
	const wchar_t remove = '!';
	const wchar_t append = '.';
	const boost::array<wchar_t,4> all = { appendif, removeif, remove, append };
};


// ============================================================================
//  forward declarations
// ============================================================================

class UnINIProperty;
class UnINISection;
class UnINIFile;


// ============================================================================
//  Debug
// ============================================================================

extern void PatchINILogDebug( const wstring& str );

#ifdef _DEBUG
#define LogDebug(text) PatchINILogDebug( wstring(wstring_make() << text << endl) )
#else
#define LogDebug(text)
#endif


// ============================================================================
//  Unicode
// ============================================================================
extern string PatchINIToNarrowString( const wchar_t* pStr );
extern wstring PatchINIToWideString( const char* pStr );


// ============================================================================
//  EOF
// ============================================================================
// ============================================================================
//  PatchINI.cpp : Defines the entry point for the console application.
// ============================================================================

#include "stdafx.h"
#include "PatchINI.h"
#include "PatchINIStatic.h"

#include "UnINIProperty.h"
#include "UnINISection.h"
#include "UnINIFile.h"


// ============================================================================
//  C Interface
// ============================================================================

int PatchINIMerge( const char* mergeini
	, const char* baseini
	, const char* resultini
	, int flags
	, char* errorBuffer
	, int errorBufferCharLen )
{
	// Convert to wide strings
	wstring wmergeini = PatchINIToWideString(mergeini);
	wstring wbaseini = PatchINIToWideString(baseini);
	wstring wresultini = PatchINIToWideString(resultini);
	wstring werror(errorBufferCharLen+1, '\0');
	
	// Main app
	int result = PatchINIMergeW(wmergeini.c_str(), wbaseini.c_str(), wresultini.c_str(), flags, &werror.at(0), errorBufferCharLen);

	// Error handling
	if(result != EXIT_SUCCESS) {
		if(errorBuffer) {
			string error = PatchINIToNarrowString(werror.c_str());
			size_t errorBufferBytes = errorBufferCharLen;
			memset(errorBuffer, '\0', errorBufferBytes);
			if(!error.empty()) {
				memcpy(errorBuffer, error.c_str(), std::max<int>(error.length(), errorBufferBytes-1));
			}
		}
	}

	return result;
}

int PatchINIMergeW( const wchar_t* mergeini
	, const wchar_t* baseini
	, const wchar_t* resultini
	, int flags
	, wchar_t* errorBuffer
	, int errorBufferCharLen )
{
	wstring error;

	try
	{
		UnINIFile changefile(true, (flags & PATCHINI_DEFAULTONLY) == PATCHINI_DEFAULTONLY);
		UnINIFile basefile;

		changefile.Read(mergeini);
		basefile.Read(baseini);

		changefile.MergeInto(basefile);
		basefile.Write(resultini);

		return EXIT_SUCCESS;
	}
	catch (wexception& e)
	{
		error = e.what();
	}
	catch (exception& e)
	{
		error = PatchINIToWideString(e.what());
	}
	catch (...)
	{
		error = L"Unknown PatchINIMerge error";
	}

	if(errorBuffer) {
		size_t errorBufferBytes = errorBufferCharLen * sizeof(wchar_t);
		memset(errorBuffer, '\0', errorBufferBytes);
		if(!error.empty()) {
			memcpy(errorBuffer, error.c_str(), std::max<int>(error.length() * sizeof(wchar_t), errorBufferBytes-1));
		}
	}

	return EXIT_FAILURE;
}

const char *PatchINIDefaultOnlyString()
{
	static const string str = PatchINIToNarrowString(PatchINIDefaultOnlyStringW());
	return str.c_str();
}

const wchar_t *PatchINIDefaultOnlyStringW()
{
	return L"PatchINI::DefaultOnly";
}

// ============================================================================
//  EOF
// ============================================================================
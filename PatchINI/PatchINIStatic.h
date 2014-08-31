// ============================================================================
//  PatchINIStatic.h
// ============================================================================
#pragma once	


// flags
#define PATCHINI_NOFLAGS 0x0000
#define PATCHINI_DEFAULTONLY 0x0001


#ifdef __cplusplus
extern "C" {
#endif

extern const char *PatchINIDefaultOnlyString();
const wchar_t *PatchINIDefaultOnlyStringW();

extern int PatchINIMerge( const char* mergeini
						 , const char* baseini
						 , const char* resultini
						 , int flags
						 , char* errorBuffer
						 , int errorBufferCharLen );

extern int PatchINIMergeW( const wchar_t* mergeini
						 , const wchar_t* baseini
						 , const wchar_t* resultini
						 , int flags
						 , wchar_t* errorBuffer
						 , int errorBufferCharLen );

#ifdef __cplusplus
}
#endif


// ============================================================================
//  EOF
// ============================================================================
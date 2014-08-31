// ============================================================================
//  UnINIFile
// ============================================================================
#pragma once

class UnINISection;

class UnINIFile
{
public:
	friend class UnINISection;

public:
	UnINIFile( bool changefile=false, bool DefaultOnly=false );
	~UnINIFile();

public:
	void DumpDebug( wostream* stream ) const;

	void Read( const wchar_t* path );
	void Write( const wchar_t* path ) const;
	void MergeInto( UnINIFile& basefile ) const;

	UnINISection* FindSection( const wstring& text ) const;
	UnINISection* AddSection( const wstring& text );

private:
	typedef list<UnINISection*> UnINISectionData;

private:
	UnINISectionData Sections;
	bool bChangeFile;
	bool bDefaultOnly;
	wstring filePath;
};
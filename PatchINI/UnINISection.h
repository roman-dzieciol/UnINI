// ============================================================================
//  UnINISection
// ============================================================================
#pragma once

class UnINIProperty;

class UnINISection
{
public:
	UnINISection();
	UnINISection(const wstring& text, UnINIFile* file);

public:
	void DumpDebug( wostream* stream ) const;

	UnINIProperty& AddProperty( const UnINIProperty& prop );

	UnINIProperty* FindProperty( const wstring& text ) const;
	UnINIProperty* FindPropertyValue( const wstring& prop, const wstring& val ) const;

	void RemoveProperty( const wstring& prop );
	void RemovePropertyValue( const wstring& prop, const wstring& val );
	void AppendPropertyValue( const wstring& prop, const wstring& val );

	bool HasText( const wstring& text ) const;
	void ReadLine( const wstring& text );
	void Write( wofstream* stream ) const;
	void MergeInto( UnINIFile* basefile ) const;

private:
	typedef list<UnINIProperty> UnINIPropertyList;

private:
	wstring Text;
	UnINIPropertyList LineData;
	UnINIFile* File;
	bool bSkipSection;
};
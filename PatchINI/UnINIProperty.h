// ============================================================================
//  UnINIProperty
// ============================================================================
#pragma once

class UnINIProperty
{
public:
	UnINIProperty();
	UnINIProperty(const wstring& text);
	UnINIProperty(const wstring& prop, const wstring& val);
	UnINIProperty(const wstring& text, const wstring& prop, const wstring& val, const wstring& cmd);

public:
	bool IsValid() const;
	void SetValue(const wstring& value);
	void UpdateText();
	bool HasPropertyValue( const wstring& prop, const wstring& val ) const;
	bool HasProperty( const wstring& prop ) const;

	void DumpDebug( wostream* stream ) const;
	void Merge( UnINISection* to ) const;
	void Write( wofstream* stream ) const;

private:
	wstring Text;
	wstring Property;
	wstring Value;
	wstring Cmd;
	bool bIsValid;
};


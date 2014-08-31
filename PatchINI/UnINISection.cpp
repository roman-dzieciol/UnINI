// ============================================================================
//  UnINISection
// ============================================================================

#include "stdafx.h"
#include "PatchINI.h"
#include "PatchINIStatic.h"
#include "UnINISection.h"
#include "UnINIProperty.h"
#include "UnINIFile.h"

UnINISection::UnINISection() : File(nullptr), bSkipSection(false)
{
}

UnINISection::UnINISection(const wstring& text, UnINIFile* file) : Text(text), File(file), bSkipSection(false)
{	
	if( !Text.empty() )
		AddProperty(UnINIProperty(wstring_make() << L"[" << Text << L"]"));
}

void UnINISection::DumpDebug( wostream* stream ) const
{
	BOOST_FOREACH(const UnINIProperty& s, LineData) { s.DumpDebug(stream); }
	*stream << endl;
}

UnINIProperty& UnINISection::AddProperty( const UnINIProperty& prop )
{
	LineData.push_back(prop);
	return LineData.back();
}

UnINIProperty* UnINISection::FindProperty( const wstring& text ) const
{
	auto it = find_if( LineData.begin(), LineData.end(), [&]( const UnINIProperty& s ) { return s.HasProperty(text); });
	if( it != LineData.end() )
		return const_cast<UnINIProperty*>(&*it);
	return nullptr;
}

UnINIProperty* UnINISection::FindPropertyValue( const wstring& prop, const wstring& val ) const
{
	auto it = find_if( LineData.begin(), LineData.end(), [&]( const UnINIProperty& s ) { return s.HasPropertyValue(prop, val); });
	if( it != LineData.end() )
		return const_cast<UnINIProperty*>(&*it);
	return nullptr;
}

void UnINISection::RemoveProperty( const wstring& prop )
{
	LogDebug(boost::wformat(L"Remove %1%") % prop);
	LineData.remove_if([&]( UnINIProperty& s ) { return s.HasProperty(prop); });     
}

void UnINISection::RemovePropertyValue( const wstring& prop, const wstring& val )
{
	LogDebug(boost::wformat(L"Remove %1% %2%") % prop % val);            
	LineData.remove_if([&]( UnINIProperty& s ) { return s.HasPropertyValue(prop, val); });             
}

void UnINISection::AppendPropertyValue( const wstring& prop, const wstring& val )
{
	LogDebug(boost::wformat(L"Append %1% %2%") % prop % val);

	// find last existing property with the same name
	auto it = find_if( LineData.rbegin(), LineData.rend(), [&]( UnINIProperty& s ) { return s.HasProperty(prop); });
	if( it != LineData.rend() )
		LineData.insert(it.base(),UnINIProperty(prop, val));
	else
		AddProperty(UnINIProperty(prop, val));
}

void UnINISection::ReadLine( const wstring& text )
{
	if( bSkipSection )
		return;

	wstring prop, val, cmd;
	size_t pos = text.find(L"=");
	if( pos != wstring::npos )
	{
		prop = boost::trim_copy(text.substr(0,pos));
		val = boost::trim_copy(text.substr(pos+1));

		if( File->bChangeFile && prop.substr(0,1).find_first_of(mergeCmds::all.data()) != wstring::npos )
		{
			cmd = prop.substr(0,1);
			prop = prop.substr(1);
		}
	}
	else if( !text.empty() && File->bDefaultOnly )
	{
		size_t pos = text.find(PatchINIDefaultOnlyStringW());
		if( pos != wstring::npos )
			bSkipSection = true;
	}

	AddProperty(UnINIProperty(text, prop, val, cmd));
}

void UnINISection::Write( wofstream* stream ) const
{
	// Write properties
	BOOST_FOREACH(const UnINIProperty& s, LineData) { s.Write(stream); }

	// add empty line after each non-empty section
	if( !Text.empty() && !LineData.empty() )
		*stream << endl;
}

void UnINISection::MergeInto( UnINIFile* basefile ) const
{
	LogDebug(boost::wformat(L"MergeInto"));

	// Get section in basefile
	UnINISection* basesection = basefile->FindSection(Text);
	if(!basesection )
		basesection = basefile->AddSection(Text);

	// Merge sections
	BOOST_FOREACH(const UnINIProperty& s, LineData) { s.Merge(basesection); }
}

bool UnINISection::HasText( const wstring& text ) const
{
	return boost::iequals(text, Text);
}


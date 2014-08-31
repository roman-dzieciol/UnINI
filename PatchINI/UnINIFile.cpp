// ============================================================================
//  UnINIFile
// ============================================================================

#include "stdafx.h"
#include "PatchINI.h"
#include "UnINIFile.h"
#include "UnINIProperty.h"
#include "UnINISection.h"

UnINIFile::UnINIFile( bool changefile, bool DefaultOnly ) 
	: bChangeFile(changefile)
	, bDefaultOnly(DefaultOnly)
{
}

UnINIFile::~UnINIFile()
{
	BOOST_FOREACH( UnINISection* s, Sections) { boost::checked_delete(s); }
}


void UnINIFile::DumpDebug( wostream* stream ) const
{
	BOOST_FOREACH( UnINISection* s, Sections ) { s->DumpDebug(stream); }
}

void UnINIFile::Read( const wchar_t* path )
{
	filePath = path;
	LogDebug(boost::wformat(L"Read %1%") % path);

	wifstream file(path);
	if( !file )
		throw wexception((boost::wformat(L"Cannot open file: %1%") % path).str());

	wstring text;
	UnINISection* CurrentSection = AddSection(L"");
	while( getline(file, text) )
	{
		if( !text.empty() )
		{
			//cout << text << endl;

			// if section
			if( text.at(0) == '[' && text.at(text.length()-1 ) == ']' )
			{
				wstring sectionname = text.substr(1,text.length()-2);
				CurrentSection = FindSection(sectionname);
				if(!CurrentSection )
					CurrentSection = AddSection(sectionname);
			}
			else
			{
				CurrentSection->ReadLine(text);
			}
		}
	}
}

void UnINIFile::Write( const wchar_t* path ) const
{
	LogDebug(boost::wformat(L"Write %1%") % path);
	wofstream file(path);
	if( !file )
		throw wexception((boost::wformat(L"Cannot open file: %1%") % path).str());

	BOOST_FOREACH( UnINISection* s, Sections ) { s->Write(&file); }
}

void UnINIFile::MergeInto( UnINIFile& basefile ) const
{
	LogDebug(boost::wformat(L"MergeInto %1%") % fs::wpath(filePath).filename());
	BOOST_FOREACH( UnINISection* s, Sections ) { s->MergeInto(&basefile); }
}

UnINISection* UnINIFile::FindSection( const wstring& text ) const
{
	auto it = find_if( Sections.rbegin(), Sections.rend(), [&]( UnINISection* s ) { return s->HasText(text); });
	if( it != Sections.rend() )
		return *it;
	return nullptr;
}

UnINISection* UnINIFile::AddSection( const wstring& text )
{
	LogDebug(boost::wformat(L"AddSection %1%") % text);
	Sections.push_back(new UnINISection(text,this));
	return Sections.back();
}
// ============================================================================
//  UnINIProperty
// ============================================================================

#include "stdafx.h"
#include "PatchINI.h"
#include "UnINIProperty.h"
#include "UnINISection.h"

UnINIProperty::UnINIProperty() : bIsValid(false)
{
}

UnINIProperty::UnINIProperty(const wstring& text) : Text(text), bIsValid(false)
{
}

UnINIProperty::UnINIProperty(const wstring& prop, const wstring& val) : Property(prop), Value(val), bIsValid(true)
{
	UpdateText();
}

UnINIProperty::UnINIProperty(const wstring& text, const wstring& prop, const wstring& val, const wstring& cmd) 
	: Text(text), Property(prop), Value(val), Cmd(cmd), bIsValid(!text.empty() && !prop.empty())
{
}

void UnINIProperty::DumpDebug( wostream* stream ) const
{
	*stream << Text << endl;
}

void UnINIProperty::Merge( UnINISection* to ) const
{
	if(!IsValid() )
		return;

	LogDebug(boost::wformat(L"Merge %1% %2%") % Text % Cmd);

	const wchar_t cmd = !Cmd.empty() ? Cmd.at(0) : mergeCmds::setOrAppend;
	switch(cmd)
	{
	case mergeCmds::setOrAppend: 
		{
			UnINIProperty* prop = to->FindProperty(Property);
			if( prop ) {
				prop->SetValue(Value);
			} else {
				to->AppendPropertyValue(Property,Value);
			}
			break;
		}
	case mergeCmds::appendif: 
		{
			if( !to->FindPropertyValue(Property,Value) ) 
			{
				to->AppendPropertyValue(Property,Value);
			}
			break;
		}
	case mergeCmds::removeif: 
		{
			to->RemovePropertyValue(Property,Value);
			break;
		}
	case mergeCmds::append: 
		{
			to->AppendPropertyValue(Property,Value);
			break;
		}
	case mergeCmds::remove: 
		{
			to->RemoveProperty(Property);
			break;
		}
	}
}

void UnINIProperty::Write( wofstream* stream ) const
{
	*stream << Text << endl;
}

bool UnINIProperty::IsValid() const
{
	return bIsValid;
}

void UnINIProperty::SetValue(const wstring& value)
{
	bIsValid = true;
	Value = value;
	UpdateText();
}

void UnINIProperty::UpdateText()
{
	Text = wstring_make() << Cmd << Property << L"=" << Value;
}

bool UnINIProperty::HasPropertyValue( const wstring& prop, const wstring& val ) const
{
	return IsValid() && boost::iequals(prop, Property) && boost::iequals(val, Value);
}

bool UnINIProperty::HasProperty( const wstring& prop ) const
{
	return IsValid() && boost::iequals(prop, Property);
}


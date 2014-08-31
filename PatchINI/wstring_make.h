// ============================================================================
//  wstring_make
// ============================================================================
#pragma once

#include <string>
#include <iostream>
#include <sstream>

class string_make : public std::ostringstream 
{
public:
	operator std::string() const { return str(); };

	template<typename AA>
	string_make &operator << (const AA &str) 
	{
		*static_cast<ostringstream *>(this) << str;
		return *this;
	}
	
	string_make &operator << (std::ostream& ( *pf )(std::ostream&)) 
	{
		*static_cast<std::ostringstream *>(this) << pf;
		return *this;
	}

	string_make &operator << (std::ios& ( *pf )(std::ios&)) 
	{
		*static_cast<std::ostringstream *>(this) << pf;
		return *this;
	}

	string_make &operator << (std::ios_base& ( *pf )(std::ios_base&)) 
	{
		*static_cast<std::ostringstream *>(this) << pf;
		return *this;
	}
};


class wstring_make : public std::wostringstream 
{
public:
	operator std::wstring() const { return str(); };

	template<typename AA>
	wstring_make &operator << (const AA &str) 
	{
		*static_cast<wostringstream *>(this) << str;
		return *this;
	}
	
	wstring_make &operator << (std::wostream& ( *pf )(std::wostream&)) 
	{
		*static_cast<std::wostringstream *>(this) << pf;
		return *this;
	}

	wstring_make &operator << (std::ios& ( *pf )(std::ios&)) 
	{
		*static_cast<std::wostringstream *>(this) << pf;
		return *this;
	}

	wstring_make &operator << (std::ios_base& ( *pf )(std::ios_base&)) 
	{
		*static_cast<std::wostringstream *>(this) << pf;
		return *this;
	}
};
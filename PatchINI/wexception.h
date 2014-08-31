// ============================================================================
//  wexception
// ============================================================================
#pragma once

#include <string>

class wexception
{	
public:
	explicit wexception(const std::wstring& _Message)
	{	// construct from message string
		m_errorMsg = _Message;
	}

	explicit wexception(const wchar_t *_Message)
	{	// construct from message string
		m_errorMsg = _Message;
	}

	const wchar_t *what() const {
		return m_errorMsg.c_str();
	}

	wexception& operator=(const wexception& rhs) {
		if(this != &rhs) {
			m_errorMsg = std::move(rhs.m_errorMsg);
		}
		return *this; 
	}
	
private:
	std::wstring m_errorMsg;
};

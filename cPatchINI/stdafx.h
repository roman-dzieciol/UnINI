// ============================================================================
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
// ============================================================================
#pragma once		


#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

using namespace std;
namespace options = boost::program_options;
namespace fs = boost::filesystem;

// ============================================================================
//  EOF
// ============================================================================
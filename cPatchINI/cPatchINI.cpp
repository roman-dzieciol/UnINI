// ============================================================================
//  cPatcIINI.cpp : Defines the entry point for the console application.
// ============================================================================

#include "stdafx.h"
#include "PatchINI/wexception.h"
#include "PatchINI/wstring_make.h"
#include "PatchINI/PatchINIStatic.h"

// ============================================================================
//  Options
// ============================================================================
namespace consts {
	
	const char *helpCmd = "help";
	const char *patchFileCmd = "patch-file";
	const char *inputFileCmd = "input-file";
	const char *outputFileCmd = "output-file";
	const char *flagsCmd = "flags";
	const char *defaultOnlyCmd = "default-only";
};

// ============================================================================
//  main
// ============================================================================
int wmain(int argc, const wchar_t* argv[])
{
	try
	{
		// Options variables
		wstring patchFile;
		wstring inputFile;
		wstring outputFile;
		int flags = 0;

		string t = PatchINIDefaultOnlyString();

		// Options specs
		options::options_description desc("Options");
		desc.add_options()
			(consts::helpCmd, "Display this help")
			(consts::patchFileCmd, options::wvalue<wstring>(&patchFile), consts::patchFileCmd)
			(consts::inputFileCmd, options::wvalue<wstring>(&inputFile), consts::inputFileCmd)
			(consts::outputFileCmd, options::wvalue<wstring>(&outputFile), consts::outputFileCmd)
			(consts::flagsCmd, options::value<int>(&flags)->default_value(0), consts::flagsCmd)
			(consts::defaultOnlyCmd, (boost::format("Skip INI sections containing the comment: ;%1%") % PatchINIDefaultOnlyString()).str().c_str())
			;
		
		// Options positioning
		options::positional_options_description p;
		p.add(consts::patchFileCmd, 1);
		p.add(consts::inputFileCmd, 1);
		p.add(consts::outputFileCmd, 1);
		p.add(consts::flagsCmd, 1);
		
		// Usage string
		wstring usageStr = (boost::wformat(L"Example usage: %1%") % fs::wpath(argv[0]).filename()).str();
		for( size_t i=0; i<p.max_total_count(); ++i ) { 
			usageStr = (boost::wformat(L"%1% %2%") % usageStr % p.name_for_position(i).c_str()).str(); 
		}

		// Options string
		wstring descStr = (boost::wformat(L"%1%") % (string_make() << desc).str().c_str()).str();

		// Help string
		wstring helpStr = (boost::wformat(L"%1%\n%2%") % descStr % usageStr).str();

		// Parse options
		options::variables_map vm;
		options::store(options::wcommand_line_parser(argc, argv).options(desc).positional(p).run(), vm);
		options::notify(vm);
		
		// Help
        if (vm.count(consts::helpCmd)) {
			wcout << helpStr << endl;
			return EXIT_SUCCESS;
        }

		// Flags
		if(vm.count(consts::defaultOnlyCmd)) {
			flags = flags | PATCHINI_DEFAULTONLY;
		}

		// Required options
		if (!vm.count(consts::patchFileCmd) || !vm.count(consts::inputFileCmd) || !vm.count(consts::outputFileCmd)) {
			throw wexception(helpStr);
		}

		// Main app
		wchar_t errorstr[1024];
		int result = PatchINIMergeW(patchFile.c_str(), inputFile.c_str(), outputFile.c_str(), flags, errorstr, 1024);
		if( result != EXIT_SUCCESS ) {
			throw wexception(errorstr);
		}
		
		return EXIT_SUCCESS;
	}
	catch(wexception& e)
	{
		wcerr << "Error: " << e.what() << endl;
	}
	catch(invalid_argument& e)
	{
		cerr << e.what() << endl;
	}
	catch(exception& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	catch(...)
	{
		cerr << "Unknown exception" << endl;
	}

	return EXIT_FAILURE;
}


// ============================================================================
//  EOF
// ============================================================================
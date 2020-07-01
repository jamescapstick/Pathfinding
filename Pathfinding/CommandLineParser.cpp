#include "CommandLineParser.h"


//------------------------------------------------
//! constructor - parses the command line arguments
//  
//! @param argc number of arguments
//! @param argv argument values
//------------------------------------------------
CommandLineParser::CommandLineParser( int& argc, char** argv )
{
	for ( int argIndex = 1; argIndex < argc; ++argIndex )
	{
		m_args.push_back( std::string( argv[argIndex] ) );
	}
}


//------------------------------------------------
//! gets the option associated with the supplied string
//  
//! @param option option flag - e.g. "-f"
//! @return argument after e.g. "-f"
//------------------------------------------------
const std::string& CommandLineParser::getOption( size_t index ) const
{
	if ( index < m_args.size() )
	{
		return m_args[index];
	}

	//couldn't find it
	static const std::string emptyString( "" );
	return emptyString;
}


//------------------------------------------------
//! gets the option associated with the supplied string
//  
//! @param option option flag - e.g. "-f"
//! @return argument after e.g. "-f"
//------------------------------------------------
const std::string& CommandLineParser::getOption( const std::string& option ) const
{
	auto it = std::find( m_args.begin(), this->m_args.end(), option );
	if ( it != m_args.end() && ++it != m_args.end() )
	{
		return *it;
	}

	//couldn't find it
	static const std::string emptyString( "" );
	return emptyString;
}


//------------------------------------------------
//! gets the option associated with the supplied string
//  
//! @param option option flag - e.g. "-f"
//! @param optionValue receives the argument after e.g. "-f"
//! @return true if we found an option
//------------------------------------------------
bool CommandLineParser::getOption( const std::string& option, std::string& optionValue ) const
{
	auto it = std::find( m_args.begin(), this->m_args.end(), option );
	if ( it != m_args.end() && ++it != m_args.end() )
	{
		optionValue = *it;
		return true;
	}

	return false;
}


//------------------------------------------------
//! tests to see if the supplied option e.g. "-f" exists in the command line
//  
//! @param option option to look for
//! @return true if it is in our argument list
//------------------------------------------------
bool CommandLineParser::gotOption( const std::string& option ) const
{
	return std::find( m_args.begin(), m_args.end(), option ) != m_args.end();
}
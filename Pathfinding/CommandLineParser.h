#pragma once

#include <vector>
#include <string>

class CommandLineParser
{
public:
	CommandLineParser( int& argc, char** argv );

	const std::string&			getOption( size_t index ) const;
	const std::string&			getOption( const std::string& option ) const;
	bool						getOption( const std::string& option, std::string& optionValue ) const;
	bool						gotOption( const std::string& option ) const;

private:
	std::vector<std::string>	m_args;
};


#include "stdafx.h"
#include "Map.h"
#include "MapLocation.h"
#include "CommandLineParser.h"
#include "Path.h"
#include "AStarPathfinder.h"
#include "DijkstrasPathfinder.h"
#include "BestFirstSearchPathfinder.h"

#include <iostream>
#include <fstream>
#include <filesystem>

constexpr int SUCCESS = 0;
constexpr int FAILURE = 1;


//------------------------------------------------
//! outputs a string to show how to use the program
//  
//! @param name program name
//------------------------------------------------
static void showUsage( const std::string& name )
{
	std::cerr << "Usage: " << name << " -f <filename> <option(s)>"
		<< "Options:\n"
		<< "\t-h,--help\t\tShow this help message\n"
		<< "\t-a,--algorithm [astar]\tSpecify the algorithm to use\n"
		<< std::endl;
}

//------------------------------------------------
//! main entry point function
//  
//! @param argc number of command line args
//! @param argv[] list of args
//! @return error code
//------------------------------------------------
int main( int argc, char *argv[] )
{
	//we should have the exe name and the map file name
	if ( argc < 3 )
	{
		showUsage( argv[0] );
		return FAILURE;
	}
	else
	{
		CommandLineParser parser( argc, argv );

		Map map;
		MapLocation startLocation;
		MapLocation endLocation;

		//show usage string?
		if ( parser.gotOption( "-h" ) ||
			 parser.gotOption( "--help" ) )
		{
			showUsage( argv[0] );
		}

		//argv[1] is a filename to open
		std::experimental::filesystem::path mapFilePath = parser.getOption( "-f" );

		if ( !map.load( mapFilePath, startLocation, endLocation ) )
		{
			std::cerr << "Could not open file " << mapFilePath << "\n";
			return FAILURE;
		}

		Path path;
		std::vector<std::unique_ptr<Pathfinder>> pathfinders;

		//did we specify an algorithm?
		std::string algorithmName;
		if ( parser.getOption( "-a", algorithmName ) ||
			 parser.getOption( "--algorithm", algorithmName ) )
		{
			if ( algorithmName.compare( "astar" ) == 0 )
			{
				pathfinders.push_back( std::make_unique<AStarPathfinder>() );
			}
			else if ( algorithmName.compare( "dijkstra" ) == 0 )
			{
				pathfinders.push_back( std::make_unique<DijkstrasPathfinder>() );
			}
			else if ( algorithmName.compare( "bestfirst" ) == 0 )
			{
				pathfinders.push_back( std::make_unique<BestFirstSearchPathfinder>() );
			}
			else
			{
				//error
				std::cerr << "Unrecognised algorithm type specified\n";
				return FAILURE;
			}
		}
		else
		{
			//default case - do all of them
			pathfinders.push_back( std::make_unique<AStarPathfinder>() );
			pathfinders.push_back( std::make_unique<DijkstrasPathfinder>() );
			pathfinders.push_back( std::make_unique<BestFirstSearchPathfinder>() );
		}

		for ( const std::unique_ptr<Pathfinder>& pathfinder : pathfinders )
		{
			if ( !pathfinder->findPath( map, startLocation, endLocation, path ) )
			{
				std::cerr << "Could not find a path through the map\n";
				return FAILURE;
			}
			else
			{
				//add the path to the map
				map.showPath( path );
				map.dump();
				map.clearMetaData();
				path.clear();
			}
		}
	}

	return SUCCESS;
}

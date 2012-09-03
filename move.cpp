#include <stdio.h>
#include <windows.h>

#define MAJOR_VERSION 1
#define MINOR_VERSION 0

// Default to 5 seconds
DWORD waitTime = 5000;

static bool processArgs
	(
	int argc,
	char** argv
	)
{
	bool start = true;

	if( argc > 1 )
	{
		if( strcmp( argv[1], "-h" ) == 0 )
		{
			start = false;

			printf( "MouseMover version %d.%d\n\n", MAJOR_VERSION, MINOR_VERSION );
			printf( "Options:\n" );
			printf( "    -h : Display this help message\n");
			printf( "    -t : Timeout between mouse moves in seconds (defaults to 5 seconds)\n" );
		}
		else if( strcmp( argv[1], "-t" ) == 0 )
		{
			if( argc > 2 )
			{
				waitTime = atoi( argv[2] );
				waitTime *= 1000;

				if( waitTime == 0 )
				{
					waitTime = 5000;
					printf( "Error, invalid timeout specified, defaulting to 5 seconds!\n" );
				}
			}
			else
			{
				printf( "Error, no timeout specified!\n" );
			}
		}
	}

	return start;
}

int main( int argc, char** argv )
{
	if( processArgs( argc, argv ) )
	{
		INPUT mouseMove = {};
		mouseMove.type = INPUT_MOUSE;
		mouseMove.mi.dwFlags = MOUSEEVENTF_MOVE;

		printf( "MouseMover version %d.%d, use -h for help\n", MAJOR_VERSION, MINOR_VERSION );
		printf( "Moving mouse every %d seconds...\n", waitTime / 1000 );

		bool left = true;

		while( 1 )
		{
			if( left )
			{
				mouseMove.mi.dx = -10;
				mouseMove.mi.dy = -10;
			}
			else
			{
				mouseMove.mi.dx = 10;
				mouseMove.mi.dy = 10;
			}

			left = !left;

			SendInput( 1, &mouseMove, sizeof( mouseMove ) );

			Sleep( waitTime );
		}
	}

	return 0;
}
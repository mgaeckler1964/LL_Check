/*
		Project:		LL_Check
		Module:			
		Description:	
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2024 Martin Gäckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Austria, Linz ``AS IS''
		AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
		PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
		LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
		USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		SUCH DAMAGE.
*/
//---------------------------------------------------------------------------
#include <winsock2.h>

#include <io.h>
#include <iostream>
#include <fstream>
#include <time.h>

#include <gak/string.h>
#include <gak/httpProfiler.h>
#include <gak/fmtNumber.h>

#pragma hdrstop

#ifdef _MSC_VER
using std::cerr;
using std::cout;
using std::ofstream;
using std::ios;
#endif

using namespace gak;

//---------------------------------------------------------------------------

#pragma argsused

static int executeCommand( int argc, const char *argv[], bool fromMain );

static char *getCurrentTime( void )
{
	time_t		timer;
	struct tm	*tblock;
	char		*timeStr;
	size_t		timeLen;

	timer = time(NULL);
	tblock = localtime(&timer);
	timeStr = asctime(tblock);
	timeLen = strlen( timeStr );
	timeStr[timeLen-1] = 0;

	return timeStr;
}

static void usage()
{
	cerr << "usage check_http.exe [options] <url>\n\n"
		"options are:\n"
		"-C <cookies> which cookies to send\n"
		"-F <file>    where to save the document\n"
		"-A <count>   how often to send the request - default: 1\n"
		"-A <file>    send requests until <file> has been deleted\n"
		"-D <delay>   which delay between two processes - default: 0\n"
		"-B <size>    receive buffer size - default: 10240\n"
		"-P <proxy>   which proxy server to use\n"
		"-O <port>    which proxy port to use\n"
		"-U <count>   number of user to emulate\n"
		"-I           include subdata (images, frames etc.)\n"
		"-L           log socket errors to stderr\n"
		"-E           log http errors (status >= 400) to stderr\n"
		"-T           log timing to stdout\n"
		"-H           log header to stdout\n"
		"-S <server>  client server mode \\\\<server>\\ll_check \n\n"
		"(c) 2005 by CRESD - Christina Ragg EDV und Sprachen Dienste GmbH, Munich\n";
}

static void dumpHttpObject( net::HTTPrequest *theConnection )
{
	cerr << theConnection->getHeader() << '\n'
		<< theConnection->getBody() << '\n';
}

static void parseCommandLine( const char *exeName, const char *commandLine )
{
	int						argc;
	Array<const char *>		argv;
	char					*localCommandLine = strdup( commandLine );
	char					c, *arg, *cp;
	bool					inString = false;

	argc = 1;
	argv.addElement( exeName );

	arg = cp = localCommandLine;
	while( true )
	{
		c = *cp;

		if( !c || (c == ' ' && !inString) )
		{
			argv.addElement( arg );
			*cp = 0;
			cp++;
			arg = cp;
			argc++;

			if( !c )
			{
				argv.addElement( NULL );
				break;
			}
		}
		else if( c=='"' )
		{
			if( !inString )
			{
				if( cp == arg )
					arg++;
				inString = true;
			}
			else
			{
				if( cp[1] == 0 || cp[1] == ' ' )
				{
					*cp = 0;
				}
				inString = false;
			}

			cp++;
		}
		else
			cp++;
	}


	executeCommand( argc, (const char **)argv.getDataBuffer(), false );

	free( localCommandLine );
}

static int executeControlFile( const char *exeName, const char *fileName )
{
	FILE	*fp;
	STRING	commandLine;

	// create the controlFile
	fp = fopen( fileName, "w" );
	if( fp )
	{
		fclose( fp );
	}
	else
	{
		cerr << "Cannot create control file\n";
/*@*/	return 1;
	}

	cout << "Waiting\n";
	while( !access( fileName, 0 ) )
	{
		fp = fopen( fileName, "r" );
		if( fp )
		{
			commandLine << fp;
			if( commandLine[0U] )
			{
				cout << "Read cmd: " << commandLine << '\n';
				parseCommandLine( exeName, commandLine );

				cout << "Waiting\n";
			}

			fclose( fp );
			fp = fopen( fileName, "w" );
			if( fp )
				fclose( fp );
		}
		Sleep( 1000 );
	}

	return 0;
}

static int executeCommand( int argc, const char *argv[], bool fromMain )
{
	doEnterFunction("executeCommand");

	int			i, statusCode;
	STRING		url, cookies, proxy, outputFile, httpHeader, headerInfo;
	STRING		stopfile, controlFile;
	STRING		commandLine;
	const char	*arg;

	bool		logExceptions	= false;
	bool		logErrors		= false;
	bool		logTiming		= false;
	bool		logHeader		= false;
	bool		includes		= false;
	int			count			= 1;
	int			delay			= 0;
	int			buffsize		= 10240;
	int			proxyPort		= 0;
	int			returnCode		= 0;
	int			userCount		= 1;

	commandLine = argv[0];
	for( i=1; i<argc; i++ )
	{
		arg = argv[i];
		if( *arg == '/' || *arg == '-' )
		{
			arg++;
			switch( toupper( *arg ) )
			{
				case 'C':
					i++;
					cookies = argv[i];
					commandLine += " -C";
					commandLine += " \"";
					commandLine += cookies;
					commandLine += '\"';
					break;
				case 'P':
					i++;
					proxy = argv[i];
					commandLine += " -P";
					commandLine += " \"";
					commandLine += proxy;
					commandLine += '\"';
					break;
				case 'F':
					i++;
					outputFile = argv[i];
					commandLine += " -F";
					commandLine += " \"";
					commandLine += outputFile;
					commandLine += '\"';
					break;
				case 'O':
					i++;
					proxyPort = atoi( argv[i] );
					commandLine += " -O ";
					commandLine += formatNumber( proxyPort );
					break;
				case 'B':
					i++;
					buffsize = atoi( argv[i] );
					commandLine += " -B ";
					commandLine += formatNumber( buffsize );
					break;
				case 'D':
					i++;
					delay = atoi( argv[i] );
					commandLine += " -D ";
					commandLine += formatNumber( delay );
					break;
				case 'U':
					i++;
					userCount = atoi( argv[i] );
					commandLine += " -U ";
					commandLine += formatNumber( userCount-1 );
					break;
				case 'S':
					i++;
					if( fromMain )
					{
						controlFile = "\\\\";
						controlFile += argv[i];
						controlFile += "\\LL_CHECK\\";
						controlFile += getenv( "COMPUTERNAME" );
						controlFile += ".ll_check";
						break;
					}

				case 'A':
					i++;
					count = atoi( argv[i] );

					if( !count )
					{
						stopfile = argv[i];
						commandLine += " -A";
						commandLine += " \"";
						commandLine += stopfile;
						commandLine += '\"';
					}
					else
					{
						commandLine += " -A ";
						commandLine += formatNumber( count );
					}

					break;
				case 'L':
					commandLine += " -L";
					logExceptions = true;
					break;
				case 'E':
					commandLine += " -E";
					logErrors = true;
					break;
				case 'T':
					//commandLine += " -T";
					logTiming = true;
					break;
				case 'H':
					commandLine += " -H";
					logHeader = true;
					break;
				case 'I':
					commandLine += " -I";
					includes = true;
					break;
				default:
					cerr << "illegal option " << arg << " found\n";
					usage();
					exit( -1 );
			}
		}
		else if( url[0U] )
		{
			cerr << "more than one url found\n";
			usage();
			exit( -1 );
		}
		else
		{
			url = arg;
			commandLine += " \"";
			commandLine += url;
			commandLine += '\"';
		}
	}

	if( controlFile[0U] )
	{
		returnCode = executeControlFile( argv[0], controlFile );
	}
	else if( !url[0U] )
	{
		cerr << "no url found\n";
		usage();
		exit( -1 );
	}
	else if( userCount > 0 )
	{
		if( userCount > 1 )
		{
			cout << "Start: " << commandLine << '\n';
			WinExec( commandLine, SW_SHOW );
			if( delay > 0 )
				Sleep( delay * 1000 );
		}

		net::HTTPprofiler	*theConnection	= new net::HTTPprofiler;

		if( count < 1 )
			count = 1;

		if( cookies[0U] )
			theConnection->setCookies( cookies );
		if( proxy[0U] )
			theConnection->setProxy( proxy, proxyPort );

		if( stopfile[0U] )
			count = 1;
		for( int i=0; i<count; i++ )
		{
			clock_t startTime = clock();
			size_t responseLen = !i
				? theConnection->Get( (const char *)url, includes, false, false, false, buffsize )
				: theConnection->playScript( false );

			clock_t	endTime = clock();

			statusCode = theConnection->getHttpStatusCode();
			if( !responseLen )
			{
				// error during connection
				if( logExceptions )
				{
					cerr << getCurrentTime() << ",caught signal " << theConnection->getSocketError() << " on try " << i << " when getting " << url << "\n";
					dumpHttpObject( theConnection );
				}
				returnCode++;
			}
			else if( logErrors )
			{
				if( statusCode >= 400 || statusCode < 100 )
				{
					cerr <<	getCurrentTime() << ",bad status code " <<
							statusCode << ' ' <<
							theConnection->getHttpStatusText() <<
							" found on try " << i << " when getting " <<
							url << '\n'
					;
					dumpHttpObject( theConnection );
					returnCode++;
				}
			}
			if( logTiming )
			{
				cout << (endTime-startTime) << ',' << url << ',' << i << '\n';
			}
			if( logHeader )
			{
				cout << url << ',' << i << '\n'
					<< theConnection->getHeader() << '\n';
			}
			if( statusCode == 200 && outputFile[0U] )
			{
				std::ofstream theStream( (const char *)outputFile, ios::out|ios::binary );
				if( !theStream.fail() )
					theStream << theConnection->getBody();
				else
				{
					cerr <<	getCurrentTime() << ",cannot open file " <<
							outputFile << '\n';
					returnCode++;
				}
			}

			if( stopfile[0U] && !access(stopfile, 0) )
				count++;
		}
		delete theConnection;
	}

	if( returnCode )
	{
		cerr << "got " << returnCode << " errors of " << count <<"\n";
	}
	return returnCode;
}

int main( int argc, const char *argv[] )
{
	return executeCommand( argc, argv, true );
}

//---------------------------------------------------------------------------






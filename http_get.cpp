/*
		Project:		LL_Check
		Module:
		Description:
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2026 Martin Gäckler

		This program is free software: you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Linz, Austria ``AS IS''
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

#include <iostream>
#include <fstream>
#include <time.h>

#include <gak/datetime.h>
#include <gak/string.h>
#include <gak/httpProfiler.h>
#include <gak/fmtNumber.h>
#include <gak/mboxParser.h>
#include <gak/stringStream.h>
#include <gak/stdlib.h>
#include <gak/directory.h>

#pragma hdrstop

using namespace gak;

//---------------------------------------------------------------------------

#pragma argsused

static int executeCommand( int argc, const char *argv[], bool fromMain );

static void usage()
{
	std::cerr << "usage http_get.exe [options] <url>\n\n"
		"options are:\n"
		"-C <cookies>          which cookies to send\n"
		"-F <file>             where to save the document\n"
		"-A <count>            how often to send the request - default: 1\n"
		"-A <file>             send requests until <file> has been deleted\n"
		"-D <delay>            which delay between two processes - default: 0\n"
		"-B <size>             receive buffer size - default: 10240\n"
		"-P <proxy>[:<port>]   which proxy server to use\n"
		"-U <count>            number of user to emulate\n"
		"-W <count>            expected file count (incl. subdata)\n"
		"-X <time>             expected time to execute\n"
		"-Y                    Redirect stdout to <ProgramData>\n"
		"-Z <file>             save loaded URLs to a file\n"
		"-I                    include subdata (images, frames etc.)\n"
		"-E                    log socket errors and http errors (status >= 400) to stderr\n"
		"-T                    log timing to stdout\n"
		"-H                    log header to stdout\n"
		"-M                    append problem to mbox file\n"
		"-S <server>           slave mode \\\\<server>\\ll_check \n\n"
		"(c) 2005-2026 by gak - Martin Gäckler, Linz, Austria\n";
	throw( -1 );
}

static void dumpHttpObject( std::ostream &out, net::HTTPrequest *theConnection )
{
	out << theConnection->getHeader() << '\n'
		<< theConnection->getBody() << '\n';
}

static void parseCommandLine( const char *exeName, const char *commandLine )
{
	int						argc;
	Array<const char *>		argv;
	Buffer<char>			localCommandLine( strdup( commandLine ) );
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

	executeCommand( argc, argv.getDataBuffer(), false );
}

static int runSlaveMode( const char *exeName, const char *fileName )
{
	STRING	commandLine;

	// create the controlFile
	{
		std::ofstream fp( fileName );
		if( !fp.is_open() )
		{
			std::cerr << "Cannot create control file\n";
/*@*/		return 1;
		}
	}

	std::cout << "Waiting\n";
	while( !access( fileName, 0 ) )
	{
		std::ifstream in(fileName);
		if( in.is_open() )
		{
			in >> commandLine;
			if( !commandLine.isEmpty() )
			{
				std::cout << "Read cmd: " << commandLine << '\n';
				parseCommandLine( exeName, commandLine );

				std::cout << "Waiting\n";
			}

			in.close();
			{
				std::ofstream fp( fileName );
			}
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
	STRING		stopfile, controlFile, scriptFile;
	STRING		commandLine;
	const char	*arg;

	bool		mboxReports		= false;
	bool		logErrors		= false;
	bool		logTiming		= false;
	bool		logHeader		= false;
	bool		includes		= false;
	bool		redirectStdOut	= false;
	int			count			= 1;
	int			expSubDataCount	= 0;
	int			delay			= 0;
	int			buffsize		= 10240;
	int			proxyPort		= 0;
	int			returnCode		= 0;
	int			userCount		= 1;
	clock_t		maxTime			= 0;

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
				{
					i++;
					proxy = argv[i];
					commandLine += " -P ";
					commandLine += proxy;

					ArrayOfStrings	proxyWithPort;
					proxyWithPort.createElements( proxy, ":" );
					proxy = proxyWithPort[0];
					if( proxyWithPort.size() > 1 )
					{
						proxyPort = atoi( proxyWithPort[1] );
					}
					break;
				}
				case 'F':
					i++;
					outputFile = argv[i];
					commandLine += " -F";
					commandLine += " \"";
					commandLine += outputFile;
					commandLine += '\"';
					break;
				case 'B':
					i++;
					buffsize = atoi( argv[i] );
					commandLine += " -B ";
					commandLine += formatNumber( buffsize );
					break;
				case 'X':
					i++;
					maxTime = atoi( argv[i] );
					commandLine += " -X ";
					commandLine += formatNumber( maxTime );
					break;
				case 'W':
					i++;
					expSubDataCount = atoi( argv[i] );
					commandLine += " -W ";
					commandLine += formatNumber( expSubDataCount );
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
				case 'M':
					commandLine += " -M";
					mboxReports = true;
					break;
				case 'Z':
					i++;
					//commandLine += " -Z";
					scriptFile = argv[i];
					break;
				case 'Y':
					commandLine += " -Y";
					redirectStdOut = true;
					break;
				default:
					std::cerr << "illegal option " << arg << " found\n";
					usage();
			}
		}
		else if( !url.isEmpty() )
		{
			std::cerr << "more than one url found\n";
			usage();
		}
		else
		{
			url = arg;
			commandLine += " \"";
			commandLine += url;
			commandLine += '\"';
		}
	}

	if( !controlFile.isEmpty() )
	{
		returnCode = runSlaveMode( argv[0], controlFile );
	}
	else if( url.isEmpty() )
	{
		std::cerr << "no url found\n";
		usage();
	}
	else if( userCount > 0 )
	{
		if( userCount > 1 )
		{
			std::cout << "Start: " << commandLine << '\n';
			WinExec( commandLine, SW_SHOW );
			if( delay > 0 )
				Sleep( delay * 1000 );
		}

		std::auto_ptr<net::HTTPprofiler>	theConnection( new net::HTTPprofiler );

		theConnection->setUserAgent("check_http/http_get ");
		if( count < 1 )
			count = 1;

		if( !cookies.isEmpty() )
			theConnection->setCookies( cookies );
		if( !proxy.isEmpty() )
			theConnection->setProxy( proxy, proxyPort );

		if( !stopfile.isEmpty() )
			count = 1;
		for( int i=0; i<count; i++ )
		{
			STRING			errBuffer;

			clock_t startTime = clock();
			size_t responseLen = !i
				? theConnection->Get( url, includes, false, false, false, buffsize )
				: theConnection->playScript( false );

			clock_t	execTime = clock() - startTime;

			statusCode = theConnection->getHttpStatusCode();

			if( !responseLen )
			{
				// error during connection
				if( logErrors || mboxReports )
				{
					oSTRINGstream	out(errBuffer);

					out << DateTime() << ",caught signal " << theConnection->getSocketError() << " on try " << i << " when getting " << url << "\n";
					dumpHttpObject( out, theConnection.get() );
				}
				returnCode++;
			}
			else if( logErrors || mboxReports )
			{
				if( statusCode >= 400 || statusCode < 100 )
				{
					oSTRINGstream	out(errBuffer);

					out <<	DateTime() << ",bad status code " <<
							statusCode << ' ' <<
							theConnection->getHttpStatusText() <<
							" found on try " << i << " when getting " <<
							url << '\n'
					;
					dumpHttpObject( out, theConnection.get() );
					returnCode++;
				}
			}
			if( maxTime && execTime > maxTime )
			{
				oSTRINGstream	out(errBuffer);

				out <<	DateTime() << ", too slow execution " <<
						execTime << '>' << maxTime <<
						" found on try " << i << " when getting " <<
						url << '\n' <<
						theConnection->getHeader() << '\n'
				;
				returnCode++;
			}
			if( expSubDataCount && expSubDataCount != theConnection->count() )
			{
				oSTRINGstream	out(errBuffer);

				out <<	DateTime() << ", incorrect number of requests " <<
						expSubDataCount << "!=" << theConnection->count() <<
						" found on try " << i << " when getting " <<
						url << '\n' <<
						theConnection->getHeader() << '\n'
				;
				returnCode++;
			}

			if( !errBuffer.isEmpty() )
			{
				if( logErrors )
				{
					std::cerr << errBuffer;
				}
				if( mboxReports )
				{
					mail::appendMail("http_get errors", errBuffer );
				}
			}
			if( logTiming || logHeader )
			{
				std::ofstream of;
				std::ostream *out = &std::cout;
				if( redirectStdOut )
				{
					STRING logFile = getGlobalConfig() +
							DIRECTORY_DELIMITER_STRING "httpGetTimings.csv";
					of.open( logFile, ios_base::app|ios_base::out );
					out = &of; 
				}
				if( logTiming )
				{
					*out << DateTime() << ',' << execTime << ','
						<< theConnection->count() << ','
						<< responseLen << ','
						<< statusCode << ','
						<< url << ','
						<< i << '\n';
				}
				if( logHeader )
				{
					*out << DateTime() << ',' << url << ',' << i << '\n'
						<< theConnection->getHeader() << '\n';
				}
			}
			if( statusCode == 200 && !outputFile.isEmpty() )
			{
				std::ofstream theStream( outputFile, std::ios::out|std::ios::binary );
				if( !theStream.fail() )
					theStream << theConnection->getBody();
				else
				{
					std::cerr << DateTime() << ",cannot open file " <<
							outputFile << '\n';
					returnCode++;
				}
			}

			if( !scriptFile.isEmpty() )
			{
				theConnection->saveScript( scriptFile );
			}

			if( !stopfile.isEmpty() && !access(stopfile, 0) )
				count++;
		}
	}

	if( returnCode )
	{
		std::cerr << "got " << returnCode << " errors of " << count <<"\n";
	}
	return returnCode;
}

int main( int argc, const char *argv[] )
{
	try
	{
		return executeCommand( argc, argv, true );
	}
	catch( std::exception &e )
	{
		std::cerr << "Exception exit " << e.what() << " of main!!!" << std::endl;
		return -1;
	}
	catch( int err )
	{
		std::cerr << "Exception exit " << err << " of main!!!" << std::endl;
		return err;
	}
	catch( ... )
	{
		std::cerr << "Exception exit of main!!!" << std::endl;
		return -1;
	}
}

//---------------------------------------------------------------------------






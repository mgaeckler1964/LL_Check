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
#include <gak/socketbuf.h>

#include <stdio.h>
#include <time.h>
#include <vcl.h>
#include <vcl/registry.hpp>
#pragma hdrstop

#include <gak/html.h>
#include <gak/vcl_tools.h>
#include <winlib/winlib.h>

#include "httpFrm.h"
#include "httpAutoCheckFrm.h"
#include "httpLoginFrm.h"
#include "DataUnit.h"

//---------------------------------------------------------------------------
using namespace gak;
using namespace vcl;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

extern const char *registryKey;

ThttpForm *httpForm;
//---------------------------------------------------------------------------
static void logFunc( void *form, const char *url, std::size_t numFiles )
{
	ThttpForm	*httpForm = (ThttpForm	*)form;
	STRING		buffer = formatNumber( numFiles );

	buffer += ": ";
	buffer += url;

	httpForm->UrlEdit->Text = (const char *)buffer;
	idleLoop();
}
//---------------------------------------------------------------------------
size_t ThttpForm::getHTTPresult(
	bool getRequest, const char *url,
	bool includes,
	bool anchorTags, bool noExternalLinks,
	bool clearExpiredOnly
)
{
	doEnterFunction("ThttpForm::getHTTPresult");

	T_STRING	htmlErrors;
	STRING		theError;
	size_t		resultLen = httpConnection->playScript( clearExpiredOnly );

	if( !resultLen )		// no script?
	{
		if( getRequest )
			resultLen = httpConnection->Get( url, includes, anchorTags, noExternalLinks, clearExpiredOnly );
		else
			resultLen = httpConnection->Head( url );
	}

	HeadMemo->Text = (const char *)httpConnection->getHeader();
	setMemoText( BodyMemo, httpConnection->getBody() );
	CookieEdit->Text = (const char *)httpConnection->getCookies();

	STRING	statusText = resultLen ? (STRING)"HTTP successfull" : httpConnection->getHttpStatusText();
	STRING	errorText, referer;
	size_t	numGets = httpConnection->getNumGets();
	size_t	numCached = 0;
	clock_t	cacheSavedTime = 0;
	size_t	cacheSavedBytes = 0;

	for( size_t i = 0; i<numGets; i++ )
	{
		statusText += "\r\n\r\n";
		const net::HTTPclientResponse	&theResponse = httpConnection->getHttpResponse(i);
		statusText += theResponse.getUrl();
		statusText += "\r\n";
		statusText += formatNumber( theResponse.getStatusCode() );
		statusText += ": ";
		statusText += theResponse.getStatusText();
		statusText += "\r\n"
			"Time connect/send/receive/parse/total (ticks): ";
		statusText += formatNumber( theResponse.getConnectTime() );
		statusText += "/";
		statusText += formatNumber( theResponse.getSendTime() );
		statusText += "/";
		statusText += formatNumber( theResponse.getReceiveTime() );
		statusText += "/";
		statusText += formatNumber( theResponse.getParseTime() );
		statusText += "/";
		statusText += formatNumber( theResponse.getTotalTime() );
		statusText += "\r\nSize: ";
		statusText += formatNumber( theResponse.getResponseSize() );
		referer = theResponse.getReferer();
		if( !referer.isEmpty() )
		{
			statusText += "\r\nReferer: ";
			statusText += referer;
		}


		htmlErrors = theResponse.getHtmlParserErrors();
		if( !htmlErrors.isEmpty() )
		{
			statusText += "\r\nHTML-Errors:";
			theError = htmlErrors.getFirstToken( "\n" );
			while( theError[0] )
			{
				statusText += "\r\n";
				statusText += theError;

				theError = htmlErrors.getNextToken();
			}
		}
		if( !theResponse.isExpired() )
		{
			statusText += "\r\nCache Hit";
			numCached++;
			cacheSavedTime += theResponse.getTotalTime();
			cacheSavedBytes += theResponse.getResponseSize();
		}
		else
			statusText += "\r\nCache Miss";
		statusText += ' ';
		statusText += theResponse.getExpiration();

		if( theResponse.getStatusCode() >= 400 || !htmlErrors.isEmpty() )
		{
			errorText += "\r\n\r\n";
			errorText += theResponse.getUrl();
			errorText += "\r\n";
			errorText += formatNumber( theResponse.getStatusCode() );
			errorText += ": ";
			errorText += theResponse.getStatusText();

			if( !referer.isEmpty() )
			{
				errorText += "\r\nReferer: ";
				errorText += referer;
			}

			errorText += "\r\nHTML-Errors:";
			theError = htmlErrors.getFirstToken( "\n" );
			while( !theError.isEmpty() )
			{
				errorText += "\r\n";
				errorText += theError;

				theError = htmlErrors.getNextToken();
			}
		}
	}
	statusText += "\r\n\r\nCache Results:";
	statusText += "\r\nCache Hits: ";
	statusText += formatNumber( numCached );
	statusText += "\r\nSize: ";
	statusText += formatNumber( cacheSavedBytes );
	statusText += "\r\nTime (ticks): ";
	statusText += formatNumber( cacheSavedTime );

	MemoStatus->Text = (const char *)statusText;
	MemoErrors->Text = (const char *)errorText;

	STRING	location = httpConnection->getLocation();
	GetLocationButton->Enabled = !location.isEmpty();

	return resultLen;
}

//---------------------------------------------------------------------------
double ThttpForm::doConnection(
	bool getRequest,
	int totalUserCount, int loops, int delay,
	bool complete, bool anchorTags, bool noExternalLinks,
	bool clearExpiredOnly,
	const STRING &url,
	const STRING &proxyServer, int proxyPort,
	const STRING &cookies,
	const STRING &userName, const STRING &password
)
{
	doEnterFunction("ThttpForm::doConnection1" );

	clock_t		firstTimerValue, lastTimerValue, totalTimerValue, avgTimerValue;
	double		avgTime = 0.0;
	size_t		lastResultLen, totalResultLen, avgResultLen,
				lastNumFiles, totalFiles, avgFiles;
	int			i;
	STRING		parameter, commandLine, buffer;

	FILE		*tmpFP = NULL;
	const char	*tmpFileName;
	const char	*tmpPath;
	STRING		tmpFilePath, searchPattern, netPath, controlFile;
	TSearchRec	searchRec;
	int			machineCount = 1, userPerMachine;
	int			myUserCount = totalUserCount;

	httpConnection->setCookies( cookies );
	httpConnection->setProxy( proxyServer, proxyPort );
	httpConnection->setCredentials( userName, password );

	if( getRequest )
	{
		tmpFilePath = "\\\\";
		tmpFilePath += getenv( "COMPUTERNAME" );
		tmpFilePath += "\\LL_CHECK\\";
		netPath = searchPattern = tmpFilePath;
		tmpFilePath += tmpnam( NULL );
		searchPattern += "*.ll_check";

		tmpFP = fopen( tmpFilePath, "w" );
		if( tmpFP )
		{
			fprintf( tmpFP, "ll_check\n" );
			fclose( tmpFP );

			if( !FindFirst( (const char*)searchPattern, 0, searchRec ) )
			{
				do
				{
					machineCount++;
				} while( !FindNext( searchRec ) );
			}
		}
		if( !tmpFP )
		{
			tmpFileName = tmpnam( NULL );
			tmpPath = getenv( "TEMP" );
			tmpFilePath = tmpPath ? tmpPath : "";
			tmpFilePath += '\\';
			tmpFilePath += tmpFileName;
			tmpFP = fopen( tmpFilePath, "w" );
			if( tmpFP )
			{
				fprintf( tmpFP, "ll_check\n" );
				fclose( tmpFP );
			}
		}

		if( totalUserCount > 1 || loops > 1 || !complete )
			anchorTags = false;

		if( totalUserCount > 1 )
		{
			parameter = '"';
			parameter += url;

			parameter += "\" -A ";
			if( tmpFP )		// successfully created tmp file
				parameter += tmpFilePath;
			else
				parameter += formatNumber( loops+totalUserCount );

			if( cookies[0U] )
			{
				parameter += " -C \"";
				parameter += cookies;
				parameter += '"';
			}

			if( proxyServer[0U] )
			{
				parameter += " -P ";
				parameter += proxyServer;
				parameter += " -O ";
				parameter += ProxyPort->Text.c_str();
			}

			if( complete )
				parameter += " -I";

			parameter += " -T";

			commandLine = "http_get.exe ";
			commandLine += parameter;

			if( machineCount > 1 )
			{
				userPerMachine = totalUserCount / machineCount;
				if( userPerMachine > 0 )
				{
					parameter += " -U ";
					parameter += formatNumber( userPerMachine );

					if( delay )
					{
						parameter += " -D ";
						parameter += formatNumber( delay );
					}

					if( !FindFirst( (const char*)searchPattern, 0, searchRec ) )
					{
						do
						{
							controlFile = netPath;
							controlFile += searchRec.Name.c_str();
							FILE	*fp = fopen( controlFile, "w" );
							if( fp )
							{
								fputs( parameter, fp );
								fclose( fp );
								myUserCount -= userPerMachine;

								if( delay )
									Sleep( delay * 1000 );
							}
						} while( !FindNext( searchRec ) );
					}
				}
			}


			for( i=1; i<myUserCount; i++ )
			{
				WinExec( commandLine, SW_SHOW );
				if( delay )
					Sleep( delay * 1000 );
			}
		}
	}

	TimeEdit->Text = "";
	totalResultLen = 0;
	totalFiles = 0;
	totalTimerValue = 0;
	if( anchorTags && getRequest )
		httpConnection->setLogFunc( logFunc, this );
	else
		httpConnection->setLogFunc( NULL, NULL );

	httpConnection->initScript();
	for( i=0; i<loops; i++ )
	{
		lastTimerValue = clock();
		if( loops == 1 )	// loops is always 1 if getRequest == false
			// get request and store the head, status and body
			lastResultLen = getHTTPresult(
				getRequest, url, complete, anchorTags, noExternalLinks, false
			);
		else if( i==0 )
			// record the script
			lastResultLen = httpConnection->Get(
				url, complete, anchorTags, noExternalLinks, false
			);
		else if( i<loops-1 )
			// don't parse the result file just play the script
			lastResultLen = httpConnection->playScript( clearExpiredOnly );
		else
			// get request and store the head, status and body
			// this is the last run of multiple loops
			lastResultLen = getHTTPresult(
				true, url,
				complete, anchorTags, noExternalLinks,
				clearExpiredOnly
			);

		lastTimerValue = clock() - lastTimerValue;
		if( i==0 )
			firstTimerValue = lastTimerValue;

		lastNumFiles = httpConnection->getNumGets();

		buffer = formatNumber( i );
		buffer += ": ";
		buffer += formatNumber( lastNumFiles );
		buffer += '/';
		buffer += formatNumber( lastResultLen );
		buffer += '/';
		buffer += formatFloat( (double)lastTimerValue/(double)CLK_TCK );
		TimeEdit->Text = (const char*)buffer;

		idleLoop();

		totalResultLen += lastResultLen;
		totalTimerValue += lastTimerValue;
		totalFiles += lastNumFiles;
	}

	avgFiles = totalFiles / loops;
	avgResultLen = totalResultLen / loops;
	avgTimerValue = totalTimerValue / loops;

	buffer = formatNumber( avgFiles );
	buffer += '/';
	buffer += formatNumber( avgResultLen );
	buffer += '/';
	avgTime = (double)avgTimerValue /(double)CLK_TCK;
	buffer += formatFloat( avgTime );
	if( clearExpiredOnly && loops > 1 )
	{
		buffer+= '/';
		avgTime = (double)firstTimerValue /(double)CLK_TCK;
		buffer += formatFloat( avgTime );
	}
	TimeEdit->Text = (const char*)buffer;

	// log func could have change the url
	UrlEdit->Text = (const char *)url;

	// indicate other clients to terminate
	if( tmpFP )
		remove( tmpFilePath );

	httpConnection->initScript();

	if( theDataModule && !anchorTags && getRequest && theDataModule->llCheck_DB->Connected )
	{		// store timings of normal gets
		bool	inTransaction = theDataModule->llCheck_DB->InTransaction;

		if( !inTransaction )
			theDataModule->llCheck_DB->StartTransaction();

		try
		{
			theDataModule->HttpTable->Open();
			theDataModule->HttpTable->Insert();
			theDataModule->HttpTableID->AsFloat = -1;
			theDataModule->HttpTableREQUEST_DATE_TIME->AsDateTime = TDateTime::CurrentDateTime();

			// http parameters
			theDataModule->HttpTableHTTP_URL->AsString = (const char *)url;
			theDataModule->HttpTableHTTP_COOKIES->AsString = (const char *)cookies;
			if( proxyServer[0U] )
			{
				theDataModule->HttpTablePROXY_SERVER->AsString = (const char *)proxyServer;
				theDataModule->HttpTablePROXY_PORT->AsInteger = proxyPort;
			}

			// environmental parameters
			theDataModule->HttpTableLOOP_COUNT->AsInteger = loops;
			theDataModule->HttpTableUSER_COUNT->AsInteger = totalUserCount;
			theDataModule->HttpTableCOMPLETE_FLAG->AsString = complete ? "Y" : "N";
			theDataModule->HttpTableLINK_CHECK->AsString = "N";		// not yet

			// the result
			theDataModule->HttpTableTOTAL_SIZE->AsInteger = avgResultLen;
			theDataModule->HttpTableNUM_FILES->AsInteger = avgFiles;
			theDataModule->HttpTableAVG_TIME->AsFloat = avgTime;

			theDataModule->HttpTable->Post();
			theDataModule->HttpTable->Close();

			if( !inTransaction && theDataModule->llCheck_DB->InTransaction )
				theDataModule->llCheck_DB->Commit();
		}
		catch( ... )
		{
			if( !inTransaction && theDataModule->llCheck_DB->InTransaction )
				theDataModule->llCheck_DB->Rollback();

			throw;
		}
	}
	return avgTime;
}
//---------------------------------------------------------------------------
void ThttpForm::doConnection( bool getRequest )
{
	doEnterFunction("ThttpForm::doConnection2" );

	int			loops = (getRequest ? LoopCount->Position : 1),
				userCount = UserCount->Position, delay = Delay->Position;
	bool		complete = Complete->Checked;
	bool		anchorTags = CheckBoxAnchors->Enabled && CheckBoxAnchors->Checked;
	bool		noExternalLinks = !(CheckBoxExternal->Enabled && CheckBoxExternal->Checked);
	bool		clearExpiredOnly = CheckBoxCache->Checked;
	STRING		url = UrlEdit->Text.c_str();
	STRING		proxyServer = ProxyServer->Text.c_str();
	int			proxyPort = atoi( ProxyPort->Text.c_str() );
	STRING		cookies = CookieEdit->Text.c_str();
	STRING		userName = EditUserName->Text.c_str();
	STRING		password = EditPassword->Text.c_str();


	TRegistry	*registry = new TRegistry;
	if( registry->OpenKey( registryKey, true ) )
	{
		registry->WriteString( "httpUrl", (const char *)url );
		registry->WriteString( "httpCookie", (const char *)cookies );
		registry->WriteString( "httpProxy", (const char *)proxyServer );
		registry->WriteString( "httpProxyPort", ProxyPort->Text );
		registry->WriteString( "httpUsername", (const char *)userName );
		registry->WriteString( "httpPassword", (const char *)password );

		registry->CloseKey();
	}
	delete registry;

	doConnection(
		getRequest, userCount, loops, delay, complete,
		anchorTags, noExternalLinks,
		clearExpiredOnly,
		url,
		proxyServer, proxyPort,
		cookies,
		userName, password
	);
}

//---------------------------------------------------------------------------
__fastcall ThttpForm::ThttpForm(TComponent* Owner)
	: TForm(Owner)
{
	httpConnection = new net::HTTPprofiler;
}

__fastcall ThttpForm::~ThttpForm()
{
	delete httpConnection;
}
//---------------------------------------------------------------------------

void __fastcall ThttpForm::GetButtonClick( TObject *Sender )
{
	doEnterFunction("ThttpForm::GetButtonClick" );

	HeadButton->Enabled = false;
	GetButton->Enabled = false;
	GetLocationButton->Enabled = false;
	LoginButton->Enabled = false;

	try
	{
		bool	newUrlFlag = true;
		int		i;
		for(i=0; i<UrlEdit->Items->Count; i++)
		{
			if( UrlEdit->Text == UrlEdit->Items->Strings[i] )
			{
				newUrlFlag = false;
				break;
			}
		}
		if( newUrlFlag )
			UrlEdit->Items->Append(UrlEdit->Text);

		doConnection( Sender == HeadButton ? false : true );
	}
	catch( ... )
	{
		HeadButton->Enabled = true;
		GetButton->Enabled = true;
		LoginButton->Enabled = true;

		throw;
	}
	HeadButton->Enabled = true;
	GetButton->Enabled = true;
	LoginButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall ThttpForm::FormClose(TObject *, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall ThttpForm::LoginButtonClick(TObject *)
{
	if( httpLoginForm->ShowModal() == mrOk )
	{
		STRING		llUrl;
		int			paramPos = UrlEdit->Text.Pos( "?" );

		if( paramPos > 0 )
			llUrl = UrlEdit->Text.SubString( 1, paramPos -1 ).c_str();
		else
			llUrl = UrlEdit->Text.c_str();

		llUrl += "?func=ll.login&username=";
		llUrl += httpLoginForm->UsernameEdit->Text.c_str();
		llUrl += "&password=";
		llUrl += net::webEscape( httpLoginForm->PasswordEdit->Text.c_str() );
		llUrl += "&nextUrl=";
		llUrl += net::webEscape( UrlEdit->Text.c_str() );

		httpConnection->initScript();
		httpConnection->setCookies( CookieEdit->Text.c_str() );
		httpConnection->setProxy(
			ProxyServer->Text.c_str(), atoi( ProxyPort->Text.c_str() )
		);
		getHTTPresult(true, llUrl, false, false, false, false );

		if( !CookieEdit->Text.Length()
		&& httpConnection->getHttpResponse().getStatusCode() == 200 )
		{
			if( paramPos > 0 )
				llUrl = UrlEdit->Text.SubString( 1, paramPos -1 ).c_str();
			else
				llUrl = UrlEdit->Text.c_str();

			llUrl += "?func=ll.login&username=";
			llUrl += httpLoginForm->UsernameEdit->Text.c_str();
			llUrl += "&password=";
			llUrl += net::webEscape(
				encodeUTF8( httpLoginForm->PasswordEdit->Text.c_str() )
			);
			llUrl += "&nextUrl=";
			llUrl += net::webEscape( UrlEdit->Text.c_str() );

			httpConnection->initScript();
			getHTTPresult(true, llUrl, false, false, false, false );
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall ThttpForm::FormShow(TObject *)
{
	TRegistry *registry = new TRegistry;

	if( registry )
	{
		if( registry->OpenKeyReadOnly( registryKey ) )
		{
			if( registry->ValueExists( "httpUrl" ) )
				UrlEdit->Text = registry->ReadString( "httpUrl" );
			if( registry->ValueExists( "httpCookie" ) )
				CookieEdit->Text = registry->ReadString( "httpCookie" );
			if( registry->ValueExists( "httpProxy" ) )
				ProxyServer->Text = registry->ReadString( "httpProxy" );
			if( registry->ValueExists( "httpProxyPort" ) )
				ProxyPort->Text = registry->ReadString( "httpProxyPort" );
			if( registry->ValueExists( "httpUsername" ) )
				EditUserName->Text = registry->ReadString( "httpUsername" );
			if( registry->ValueExists( "httpPassword" ) )
				EditPassword->Text = registry->ReadString( "httpPassword" );

			registry->CloseKey();
		}
		delete registry;
	}
}
//---------------------------------------------------------------------------


void __fastcall ThttpForm::GetLocationButtonClick(TObject *Sender)
{
	GetLocationButton->Enabled = false;

	STRING	location = httpConnection->getLocation();
	if( location[0U] )
	{
		UrlEdit->Text = (const char *)location;
		GetButtonClick( Sender );
	}
}
//---------------------------------------------------------------------------

void __fastcall ThttpForm::enableDisableAnchors(TObject *)
{
	int			loops = LoopCount->Position, userCount = UserCount->Position;
	bool		complete = Complete->Checked;
	bool		anchors = CheckBoxAnchors->Checked;

	if( userCount > 1 || loops > 1 || !complete )
	{
		CheckBoxAnchors->Enabled = false;
		CheckBoxExternal->Enabled = false;
	}
	else
	{
		CheckBoxAnchors->Enabled = true;
		CheckBoxExternal->Enabled = anchors;
	}
}
//---------------------------------------------------------------------------

void __fastcall ThttpForm::AutoCheckButtonClick(TObject *)
{
	if( httpAutoCheckForm->ShowModal() == mrOk )
	{
		int			userCount = httpAutoCheckForm->MinUserUpDown->Position,
					maxUserCount = httpAutoCheckForm->MaxUserUpDown->Position,
					userIncrement = httpAutoCheckForm->UserIncrementUpDown->Position,
					maxAvgTime = httpAutoCheckForm->MaxAvgTimeUpDown->Position;

		double		avgTime;

		int			loops = LoopCount->Position,
					delay = Delay->Position;
		bool		complete = Complete->Checked;
		bool		clearExpiredOnly = CheckBoxCache->Checked;
		STRING		url = UrlEdit->Text.c_str();
		STRING		proxyServer = ProxyServer->Text.c_str();
		int			proxyPort = atoi( ProxyPort->Text.c_str() );
		STRING		cookies = CookieEdit->Text.c_str();
		STRING		userName = EditUserName->Text.c_str();
		STRING		password = EditPassword->Text.c_str();


		TRegistry	*registry = new TRegistry;
		if( registry->OpenKey( registryKey, true ) )
		{
			registry->WriteString( "httpUrl", (const char *)url );
			registry->WriteString( "httpCookie", (const char *)cookies );
			registry->WriteString( "httpProxy", (const char *)proxyServer );
			registry->WriteString( "httpProxyPort", ProxyPort->Text );
			registry->WriteString( "httpUsername", (const char *)userName );
			registry->WriteString( "httpPassword", (const char *)password );

			registry->CloseKey();
		}
		delete registry;

		while( userCount <= maxUserCount )
		{
			UserCount->Position = (short)userCount;
			avgTime = doConnection(
				true, userCount, loops, delay, complete, false, false,
				clearExpiredOnly,
				url,
				proxyServer, proxyPort,
				cookies,
				userName, password
			);
			userCount += userIncrement;
			Sleep( avgTime * 1000 );
			if( maxAvgTime && maxAvgTime<avgTime )
				break;
		}
	}
}
//---------------------------------------------------------------------------


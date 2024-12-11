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

#include <gak/logfile.h>

#include "ServiceMain.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

ThttpCheckService *httpCheckService;
//---------------------------------------------------------------------------
__fastcall ThttpCheckService::ThttpCheckService(TComponent* Owner)
	: TService(Owner)
{
	theThread = NULL;
}

TServiceController __fastcall ThttpCheckService::GetServiceController(void)
{
	return (TServiceController) ServiceController;
}

void __stdcall ServiceController(unsigned CtrlCode)
{
	httpCheckService->Controller(CtrlCode);
}
//---------------------------------------------------------------------------


void __fastcall ThttpCheckService::ServiceStart(TService *,
	  bool &Started)
{
	const char	*temp;
	AnsiString	privateDir = "C:\\";

	if( (temp=getenv("TEMP")) != NULL )
		privateDir = temp;
	if( privateDir[privateDir.Length()] != '\\' )
		privateDir += '\\';

	privateDir += "CheckHttpService";
	mkdir( privateDir.c_str() );

	Session->PrivateDir = privateDir;
//	Session->NetFileDir = privateDir;

	try
	{
		doLogPosition();
		Session->Open();
		doLogPosition();
//		Session->NetFileDir = "";
//		doLogPosition();
	}
	catch( ... )
	{
		EventLog( "%s", "Session Creation Failed" );
		throw;
	}

	doLogValue( privateDir.c_str() );

	try
	{
		doLogPosition();
		llCheckDatabase->Open();
		doLogPosition();
//		Session->NetFileDir = "";
//		doLogPosition();
	}
	catch( ... )
	{
		EventLog( "%s", "Database Connection Failed" );
		throw;
	}
	if( !theThread )
		theThread = new HttpServiceCheckThread( false );

	Started = true;
}
//---------------------------------------------------------------------------

void __fastcall ThttpCheckService::ServiceStop(TService *Sender,
	  bool &Stopped)
{
	ServiceShutdown( Sender );
	Stopped = true;
}
//---------------------------------------------------------------------------

void __fastcall ThttpCheckService::ServiceShutdown(TService *)
{
	if( theThread )
	{
		theThread->Terminate();
		while( theThread->isRunning() )
			Sleep( 1000 );

		delete theThread;
		theThread = NULL;
	}
	llCheckDatabase->Close();
}
//---------------------------------------------------------------------------

void __fastcall ThttpCheckService::NMSMTPConnectionFailed(TObject *)
{
	EventLog( "%s", "SMTP Connection Failed" );
}
//---------------------------------------------------------------------------

void __fastcall ThttpCheckService::NMSMTPAuthenticationFailed(
	  bool &)
{
	EventLog( "%s", "SMTP Authentication Failed" );
}
//---------------------------------------------------------------------------

void __fastcall ThttpCheckService::NMSMTPFailure(TObject *)
{
	EventLog( "%s", "SMTP Failure" );
}
//---------------------------------------------------------------------------

void __fastcall ThttpCheckService::NMSMTPInvalidHost(bool &)
{
	EventLog( "%s", "Invalid SMTP Host" );
}
//---------------------------------------------------------------------------

void __fastcall ThttpCheckService::NMSMTPRecipientNotFound(
	  AnsiString Recipient)
{
	EventLog( "%s: %s", "Recipient Not Found", Recipient.c_str() );
}
//---------------------------------------------------------------------------
/*
	Write a message to the event log

	can be read with the event viewer program
*/
void ThttpCheckService::EventLog( const char *format, ... )
{
	va_list	args;

	HANDLE	eventHndl;
	char	message[1024];
	char	*msg = message;

	va_start( args, format );
	vsprintf( message, format, args );
	va_end( args );

	eventHndl = RegisterEventSource( NULL, DisplayName.c_str() );

	ReportEvent( eventHndl, EVENTLOG_ERROR_TYPE, 0, 0, 0, 1, 0, (LPCTSTR*)&msg, NULL );
	DeregisterEventSource( eventHndl );
}
//---------------------------------------------------------------------------



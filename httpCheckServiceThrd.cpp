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

#include <vcl.h>

#include <gak/httpProfiler.h>
#include <gak/t_string.h>
#pragma hdrstop

#include "httpCheckServiceThrd.h"
#include "ServiceMain.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall HttpServiceCheckThread::HttpServiceCheckThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	running = false;
}
//---------------------------------------------------------------------------
void HttpServiceCheckThread::PostTable( TTable *theTable )
{
	doEnterFunction("HttpServiceCheckThread::PostTable");
	try
	{
		theTable->Post();
	}
	catch( Exception &e )
	{
		httpCheckService->EventLog(
			"%s: %s %s",
			"Unable to write table",
			theTable->TableName.c_str(),
			e.Message.c_str()
		);
	}
	catch( ... )
	{
		httpCheckService->EventLog(
			"%s: %s",
			"Unable to write table",
			theTable->TableName.c_str()
		);
	}
}

bool HttpServiceCheckThread::OpenTable( TTable *theTable )
{
	doEnterFunction("HttpServiceCheckThread::OpenTable");
	try
	{
		theTable->Open();
	}
	catch( Exception &e )
	{
		httpCheckService->EventLog(
			"%s: %s %s",
			"Unable to open table",
			theTable->TableName.c_str(),
			e.Message.c_str()
		);
	}
	catch( ... )
	{
		httpCheckService->EventLog(
			"%s: %s",
			"Unable to open table",
			theTable->TableName.c_str()
		);
	}
	return theTable->Active;
}
//---------------------------------------------------------------------------
void HttpServiceCheckThread::SendAlertMail(
	double execTime,
	int httpStatus,
	STRING httpError,
	STRING socketError
)
{
	doEnterFunction("HttpServiceCheckThread::SendAlertMail");

	char		tempBuffer[1024];
	T_STRING	emailRecieverList;
	STRING		email;

	httpCheckService->NMSMTP->Host = httpCheckService->TableHttpRecurringSMTP_SERVER->AsString;
	if( !httpCheckService->TableHttpRecurringSMTP_PORT->IsNull
	&& httpCheckService->TableHttpRecurringSMTP_PORT->AsInteger )
		httpCheckService->NMSMTP->Port = httpCheckService->TableHttpRecurringSMTP_PORT->AsInteger;
	else
		httpCheckService->NMSMTP->Port = 25;

	emailRecieverList = httpCheckService->TableHttpRecurringE_MAIL_ALERT->AsString.c_str();
	email = emailRecieverList.getFirstToken( ";," );

	httpCheckService->NMSMTP->UserID = httpCheckService->TableHttpRecurringSMTP_USER->AsString;
	httpCheckService->NMSMTP->PostMessage->FromAddress = (const char *)email;
	httpCheckService->NMSMTP->PostMessage->Subject = "\"CRESD HTTP Check\" Performance/Status Alert";
	httpCheckService->NMSMTP->PostMessage->ToAddress->Clear();
	do
	{
		httpCheckService->NMSMTP->PostMessage->ToAddress->Add((const char*)email);
		email = emailRecieverList.getNextToken();
	} while( !email.isEmpty() );
	httpCheckService->NMSMTP->PostMessage->Body->Clear();
	if( execTime > httpCheckService->TableHttpRecurringMAX_TIME->AsFloat )
	{
		httpCheckService->NMSMTP->PostMessage->Body->Add( "There is a performance alert from \"CRESD HTTP Check\" for the URL" );
		httpCheckService->NMSMTP->PostMessage->Body->Add( httpCheckService->TableHttpRecurringHTTP_URL->AsString );
		sprintf( tempBuffer, "Max Time: %.3f Actual Time: %.3f",
			httpCheckService->TableHttpRecurringMAX_TIME->AsFloat,
			execTime
		);
		httpCheckService->NMSMTP->PostMessage->Body->Add( tempBuffer );
		httpCheckService->NMSMTP->PostMessage->Body->Add( "" );
	}
	if( httpStatus != 200 )
	{
		httpCheckService->NMSMTP->PostMessage->Body->Add( "There is a status alert from \"CRESD HTTP Check\" for the URL" );
		httpCheckService->NMSMTP->PostMessage->Body->Add( (const char*)httpError );
		httpCheckService->NMSMTP->PostMessage->Body->Add( (const char*)socketError );
		httpCheckService->NMSMTP->PostMessage->Body->Add( "" );
	}
	httpCheckService->NMSMTP->PostMessage->Body->Add( "See LL Check or HTTP Check for details." );
	httpCheckService->NMSMTP->PostMessage->Body->Add( "" );
	httpCheckService->NMSMTP->PostMessage->Body->Add( "(c) 2009 by CRESD GmbH - Munich - http://www.cresd.de/" );
	try
	{
		httpCheckService->NMSMTP->Connect();
		httpCheckService->NMSMTP->SendMail();
		httpCheckService->NMSMTP->Disconnect();
	}
	catch( ... )
	{
		httpCheckService->EventLog( "%s", "Unable to send alert mail" );
	}
}

//---------------------------------------------------------------------------
void HttpServiceCheckThread::storeHttpTime(
	TDateTime now,
	double execTime,
	size_t responseSize,
	size_t numFiles
)
{
	doEnterFunction("HttpServiceCheckThread::storeHttpTime");

	if( OpenTable( httpCheckService->TableHTTP_THREAD ) )
	{
		httpCheckService->TableHTTP_THREAD->Insert();

		httpCheckService->TableHTTP_THREADHTTP_URL->AsString
			= httpCheckService->TableHttpRecurringHTTP_URL->AsString
		;
		httpCheckService->TableHTTP_THREADHTTP_COOKIES->AsString
			= httpCheckService->TableHttpRecurringHTTP_COOKIES->AsString
		;
		httpCheckService->TableHTTP_THREADREQUEST_DATE_TIME->AsDateTime
			= now
		;
		httpCheckService->TableHTTP_THREADLOOP_COUNT->AsInteger
			= 1
		;
		httpCheckService->TableHTTP_THREADUSER_COUNT->AsInteger
			= 1
		;
		httpCheckService->TableHTTP_THREADAVG_TIME->AsFloat
			= execTime
		;
		if( !httpCheckService->TableHttpRecurringPROXY_SERVER->IsNull )
			httpCheckService->TableHTTP_THREADPROXY_SERVER->AsString
				= httpCheckService->TableHttpRecurringPROXY_SERVER->AsString
			;
		if( !httpCheckService->TableHttpRecurringPROXY_PORT->IsNull )
			httpCheckService->TableHTTP_THREADPROXY_PORT->AsInteger
				= httpCheckService->TableHttpRecurringPROXY_PORT->AsInteger
			;
		httpCheckService->TableHTTP_THREADCOMPLETE_FLAG->AsString
			= "Y"
		;
		httpCheckService->TableHTTP_THREADLINK_CHECK->AsString
			= "N"
		;
		httpCheckService->TableHTTP_THREADTOTAL_SIZE->AsInteger
			= responseSize
		;
		httpCheckService->TableHTTP_THREADNUM_FILES->AsInteger
			= numFiles
		;
		PostTable( httpCheckService->TableHTTP_THREAD );
		httpCheckService->TableHTTP_THREAD->Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall HttpServiceCheckThread::Execute()
{
	doEnterFunction("HttpServiceCheckThread::Execute");

	bool				sendMail;
	clock_t				startTime;
	double				execTime, sleepTime;
	int					httpStatus;
	size_t				responseSize;
	net::HTTPprofiler	theHttpConnection;
	TDateTime			now, next;

	running = true;
	while( !Terminated )
	{
		now = TDateTime::CurrentDateTime();

		if( OpenTable(httpCheckService->TableHttpRecurring) && !httpCheckService->TableHttpRecurring->Eof )
		{
			next = httpCheckService->TableHttpRecurringNEXT_START->AsDateTime;
			while( next <= now )
			{
				/*
					check if last try was successful
				*/
				if(
					(
						!httpCheckService->TableHttpRecurringLAST_TIME->IsNull
						&&	httpCheckService->TableHttpRecurringLAST_TIME->AsFloat > httpCheckService->TableHttpRecurringMAX_TIME->AsFloat
					)
				||
					(
						!httpCheckService->TableHttpRecurringLAST_STATUS->IsNull
						&& httpCheckService->TableHttpRecurringLAST_STATUS->AsInteger != 200
					)
				)
					sendMail = false;	// do not send the mail twice
				else
					sendMail = true;

				/*
					setup request
				*/
				theHttpConnection.setProxy(
					httpCheckService->TableHttpRecurringPROXY_SERVER->AsString.c_str(),
					httpCheckService->TableHttpRecurringPROXY_PORT->AsInteger
				);
				theHttpConnection.setCookies(
					httpCheckService->TableHttpRecurringHTTP_COOKIES->AsString.c_str()
				);
				startTime = clock();
				now = TDateTime::CurrentDateTime();
				responseSize = theHttpConnection.Get(
					httpCheckService->TableHttpRecurringHTTP_URL->AsString.c_str(),
					true, false, false, false
				);
				execTime = ((double)(clock()-startTime))/((double)CLK_TCK);
				const net::HTTPclientResponse &httpResponse =
					theHttpConnection.getHttpResponse(
						httpCheckService->TableHttpRecurringHTTP_URL->AsString.c_str()
					)
				;
				httpStatus = httpResponse.getStatusCode();

				/*
					send alert mail if required and possible
				*/
				if( sendMail
				&& (execTime > httpCheckService->TableHttpRecurringMAX_TIME->AsFloat || httpStatus != 200)
				&& !httpCheckService->TableHttpRecurringE_MAIL_ALERT->IsNull
				&& !httpCheckService->TableHttpRecurringSMTP_SERVER->IsNull )
				{
					SendAlertMail(
						execTime,
						httpStatus,
						httpResponse.getStatusText(),
						theHttpConnection.getSocketError()
					);
				}

				/*
					store time if successful
				*/
				if( httpStatus == 200 )
				{
					storeHttpTime(
						now, execTime,
						responseSize, theHttpConnection.getNumGets()
					);
				}

				/*
					store result and next time
				*/
				now = TDateTime::CurrentDateTime();
				httpCheckService->TableHttpRecurring->Edit();
				httpCheckService->TableHttpRecurringLAST_TIME->AsFloat
					= execTime
				;
				httpCheckService->TableHttpRecurringLAST_STATUS->AsInteger
					= httpStatus
				;
				next +=
					httpCheckService->TableHttpRecurringINTERVAL->AsFloat / 86400.0
				;
				if( next < now )
					next = now + httpCheckService->TableHttpRecurringINTERVAL->AsFloat / 86400.0;

				httpCheckService->TableHttpRecurringNEXT_START->AsDateTime = next;
				PostTable( httpCheckService->TableHttpRecurring );

				/*
					get next record
				*/
				httpCheckService->TableHttpRecurring->First();

				next = httpCheckService->TableHttpRecurringNEXT_START->AsDateTime;
			}
		}
		else
			next = now + 10.0 / 86400.0;

		httpCheckService->TableHttpRecurring->Close();

		sleepTime = ((double)next-(double)now) * 86400.0;
		if( sleepTime > 10 || sleepTime <= 0 )
			sleepTime = 10;
		Sleep( sleepTime * 1000 );
	}
	running = false;
}
//---------------------------------------------------------------------------

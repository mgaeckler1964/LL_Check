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
#ifndef ServiceMainH
#define ServiceMainH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <vcl.h>
#include <Db.hpp>
#include <DBTables.hpp>

#include "httpCheckServiceThrd.h"
#include <NMsmtp.hpp>
#include <Psock.hpp>

//---------------------------------------------------------------------------
class ThttpCheckService : public TService
{
__published:    // IDE-managed Components
	TDatabase *llCheckDatabase;
	TTable *TableHttpRecurring;
	TFloatField *TableHttpRecurringID;
	TMemoField *TableHttpRecurringHTTP_URL;
	TMemoField *TableHttpRecurringHTTP_COOKIES;
	TStringField *TableHttpRecurringPROXY_SERVER;
	TFloatField *TableHttpRecurringPROXY_PORT;
	TFloatField *TableHttpRecurringINTERVAL;
	TDateTimeField *TableHttpRecurringNEXT_START;
	TFloatField *TableHttpRecurringMAX_TIME;
	TStringField *TableHttpRecurringE_MAIL_ALERT;
	TStringField *TableHttpRecurringSMTP_SERVER;
	TFloatField *TableHttpRecurringSMTP_PORT;
	TFloatField *TableHttpRecurringLAST_TIME;
	TFloatField *TableHttpRecurringLAST_STATUS;
	TNMSMTP *NMSMTP;
	TStringField *TableHttpRecurringSMTP_USER;
	TTable *TableHTTP_THREAD;
	TFloatField *TableHTTP_THREADID;
	TMemoField *TableHTTP_THREADHTTP_URL;
	TMemoField *TableHTTP_THREADHTTP_COOKIES;
	TDateTimeField *TableHTTP_THREADREQUEST_DATE_TIME;
	TFloatField *TableHTTP_THREADLOOP_COUNT;
	TFloatField *TableHTTP_THREADUSER_COUNT;
	TFloatField *TableHTTP_THREADAVG_TIME;
	TStringField *TableHTTP_THREADPROXY_SERVER;
	TFloatField *TableHTTP_THREADPROXY_PORT;
	TStringField *TableHTTP_THREADCOMPLETE_FLAG;
	TStringField *TableHTTP_THREADLINK_CHECK;
	TFloatField *TableHTTP_THREADTOTAL_SIZE;
	TFloatField *TableHTTP_THREADNUM_FILES;
	TFloatField *TableHTTP_THREADMAX_FILES;
	void __fastcall ServiceStart(TService *Sender, bool &Started);
	void __fastcall ServiceStop(TService *Sender, bool &Stopped);
	void __fastcall ServiceShutdown(TService *Sender);
	void __fastcall NMSMTPConnectionFailed(TObject *Sender);
	void __fastcall NMSMTPAuthenticationFailed(bool &Handled);
	void __fastcall NMSMTPFailure(TObject *Sender);
	void __fastcall NMSMTPInvalidHost(bool &Handled);
	void __fastcall NMSMTPRecipientNotFound(AnsiString Recipient);
private:        // User declarations
	HttpServiceCheckThread	*theThread;
public:         // User declarations
	__fastcall ThttpCheckService(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);

	friend void __stdcall ServiceController(unsigned CtrlCode);
	void EventLog( const char *format, ... );
};
//---------------------------------------------------------------------------
extern PACKAGE ThttpCheckService *httpCheckService;
//---------------------------------------------------------------------------
#endif

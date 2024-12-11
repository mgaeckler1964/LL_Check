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

#pragma hdrstop

#include "httpTimesFrm.h"
#include "httpFrm.h"
#include "DataUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
ThttpTimesForm *httpTimesForm = NULL;
//---------------------------------------------------------------------------
__fastcall ThttpTimesForm::ThttpTimesForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall ThttpTimesForm::FormClose(TObject *,
	  TCloseAction &Action)
{
	Action = caFree;
	httpTimesQuery->Close();
	httpTimesForm = NULL;
}
//---------------------------------------------------------------------------
void __fastcall ThttpTimesForm::FormShow(TObject *)
{
	httpTimesQuery->Open();
}
//---------------------------------------------------------------------------
void __fastcall ThttpTimesForm::RefreshButtonClick(TObject *)
{
	httpTimesQuery->Close();
	httpTimesQuery->Open();
}
//---------------------------------------------------------------------------
void __fastcall ThttpTimesForm::DBGridTimesDblClick(TObject *)
{
	Application->CreateForm(__classid(ThttpForm), &httpForm);

	httpForm->UrlEdit->Text = httpTimesQueryURL->AsString;
	httpForm->CookieEdit->Text = httpTimesQueryCOOKIES->AsString;
	httpForm->ProxyServer->Text = httpTimesQueryPROXY_SERVER->AsString;
	httpForm->ProxyPort->Text = httpTimesQueryPROXY_PORT->AsString;
	httpForm->LoopCount->Position = (short)httpTimesQueryLOOP_COUNT->AsInteger;
	httpForm->UserCount->Position = (short)httpTimesQueryUSER_COUNT->AsInteger;
	if( httpTimesQueryCOMPLETE_FLAG->AsString == "Y" )
		httpForm->Complete->Checked = true;
	else
		httpForm->Complete->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall ThttpTimesForm::ButtonDelUrlClick(TObject *)
{
	AnsiString	oldUrl = httpTimesQueryHTTP_URL->AsString;
	AnsiString	message = "Are you sure, you want to remove all entries of the url\r\n";
	message += oldUrl;
	message += "?";

	if( Application->MessageBox( message.c_str(), Application->Title.c_str(), MB_OKCANCEL|MB_ICONQUESTION ) == IDOK )
	{
		httpTimesQuery->Close();
		delUrlQuery->Params->Items[0]->AsString = oldUrl;
		delUrlQuery->ExecSQL();
		httpTimesQuery->Open();
	}
}
//---------------------------------------------------------------------------

void __fastcall ThttpTimesForm::ChangeSort(TObject *)
{
	httpTimesQuery->Close();
	httpTimesQuery->SQL->Clear();
	httpTimesQuery->SQL->Add(
		"select	id,"
				"request_date_time,"
				"substr( http_url, 1, 255 ) as url,"
				"http_url,"
				"substr( http_cookies, 1, 255 ) as cookies,"
				"loop_count,"
				"user_count,"
				"avg_time,"
				"proxy_server,"
				"proxy_port,"
				"COMPLETE_FLAG,"
				"TOTAL_SIZE,"
				"NUM_FILES "
		"from	http_thread" );
	if( RadioButtonSortURL->Checked )
		httpTimesQuery->SQL->Add( "order by 3, user_count, request_date_time desc" );
	else
		httpTimesQuery->SQL->Add( "order by request_date_time desc, 3, user_count" );

	httpTimesQuery->Open();
}
//---------------------------------------------------------------------------


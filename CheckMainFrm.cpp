/*
		Project:		LL_Check
		Module:			
		Description:	
		Author:			Martin G�ckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2024 Martin G�ckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin G�ckler, Austria, Linz ``AS IS''
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

#include "llthreadfrm.h"
#include "webthreadfrm.h"
#include "httpFrm.h"
#include "httpTimesFrm.h"
#include "llStatFrm.h"
#include "webStatFrm.h"
#include "llChartFrm.h"
#include "webChartFrm.h"
#include "httpChartFrm.h"
#include "llServerFrm.h"
#include "webServerFrm.h"
#include "DataUnit.h"
#include "llSummarizedFrm.h"
#include "webSummarizedFrm.h"
#include "CheckMainFrm.h"
#include "AboutFrm.h"
#include "HttpRecurringFrm.h"
#include "DataUnit.h"
#include "WebTestFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCheckMainForm *CheckMainForm;
//---------------------------------------------------------------------------
__fastcall TCheckMainForm::TCheckMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCheckMainForm::FormShow(TObject *)
{
	theDataModule->openDatabase( "LL_CHECK" );
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::ExitClick(TObject *)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------


void __fastcall TCheckMainForm::HTTP1Click(TObject *)
{
	Application->CreateForm(__classid(ThttpForm), &httpForm);
}
//---------------------------------------------------------------------------


void __fastcall TCheckMainForm::Livelink1Click(TObject *)
{
	if( !LLthreadForm )
		Application->CreateForm(__classid(TLLthreadForm), &LLthreadForm);
	LLthreadForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::LLStatisticsClick(TObject *)
{
	if( !llStatForm )
		Application->CreateForm(__classid(TllStatForm), &llStatForm);
	llStatForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::LLChartsClick(TObject *)
{
	Application->CreateForm(__classid(TLLChartForm), &LLChartForm);
}
//---------------------------------------------------------------------------


void __fastcall TCheckMainForm::LLServersClick(TObject *)
{
	llServerForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TCheckMainForm::HTTPTimes1Click(TObject *)
{
	if( !httpTimesForm )
		Application->CreateForm(__classid(ThttpTimesForm), &httpTimesForm);

	httpTimesForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::HTTPCharts1Click(TObject *)
{
	Application->CreateForm(__classid(ThttpChartForm), &httpChartForm);
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::ArrangeVertical1Click(TObject *)
{
	TileMode = tbVertical;
	Tile();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::ArrangeHorizontal1Click(TObject *)
{
	TileMode = tbHorizontal;
	Tile();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::Cascade1Click(TObject *)
{
	Cascade();	
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::LLSummarizeViewClick(TObject *)
{
	if( !llSummarizedForm )
		Application->CreateForm(__classid(TllSummarizedForm), &llSummarizedForm);

	llSummarizedForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TCheckMainForm::Info1Click(TObject *)
{
	AboutBox->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::HTTPAutochecks1Click(TObject *)
{
	if( !HttpRecurringForm )
		Application->CreateForm(__classid(THttpRecurringForm), &HttpRecurringForm);
	HttpRecurringForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::DeleteoldEntriesClick(TObject *)
{
	theDataModule->deleteOldEntries();	
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::WebServersClick(TObject *)
{
	webServerForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::WebRequestsClick(TObject *)
{
	if( !WebThreadForm )
		Application->CreateForm(__classid(TWebThreadForm), &WebThreadForm);
	WebThreadForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::WebStatisticsClick(TObject *)
{
	if( !webStatForm )
		Application->CreateForm(__classid(TwebStatForm), &webStatForm);
	webStatForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::WebSummarizeViewClick(TObject *)
{
	if( !webSummarizedForm )
		Application->CreateForm(__classid(TwebSummarizedForm), &webSummarizedForm);

	webSummarizedForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::WebChartsClick(TObject *)
{
	Application->CreateForm(__classid(TWebChartForm), &WebChartForm);
}
//---------------------------------------------------------------------------

void __fastcall TCheckMainForm::WebTestsClick(TObject *)
{
	Application->CreateForm(__classid(TWebTestForm), &WebTestForm);
}
//---------------------------------------------------------------------------


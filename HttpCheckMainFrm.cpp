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

#include "httpFrm.h"
#include "httpTimesFrm.h"
#include "httpChartFrm.h"
#include "DataUnit.h"
#include "HttpCheckMainFrm.h"
#include "AboutFrm.h"
#include "HttpRecurringFrm.h"
#include "WebTestFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THttpCheckMainForm *HttpCheckMainForm;
//---------------------------------------------------------------------------
__fastcall THttpCheckMainForm::THttpCheckMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THttpCheckMainForm::FormShow(TObject *)
{
	try
	{
		Application->CreateForm(__classid(TtheDataModule), &theDataModule);
		theDataModule->openDatabase( "HTTP_CHECK" );
	}
	catch( ... )
	{
		HTTPTimes->Visible = false;
		HTTPCharts->Visible = false;
		HTTPAutochecks->Visible = false;
		theDataModule = NULL;

//		throw;
	}
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::Exit1Click(TObject *)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::HTTP1Click(TObject *)
{
	Application->CreateForm(__classid(ThttpForm), &httpForm);
}
//---------------------------------------------------------------------------
void __fastcall THttpCheckMainForm::HTTPTimesClick(TObject *)
{
	if( !httpTimesForm )
		Application->CreateForm(__classid(ThttpTimesForm), &httpTimesForm);

	httpTimesForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::HTTPChartsClick(TObject *)
{
	Application->CreateForm(__classid(ThttpChartForm), &httpChartForm);
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::ArrangeVertical1Click(TObject *)
{
	TileMode = tbVertical;
	Tile();
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::ArrangeHorizontal1Click(TObject *)
{
	TileMode = tbHorizontal;
	Tile();
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::Cascade1Click(TObject *)
{
	Cascade();
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::Info1Click(TObject *)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::HTTPAutochecksClick(TObject *)
{
	if( !HttpRecurringForm )
		Application->CreateForm(__classid(THttpRecurringForm), &HttpRecurringForm);
	HttpRecurringForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall THttpCheckMainForm::WebTestsClick(TObject *)
{
	Application->CreateForm(__classid(TWebTestForm), &WebTestForm);
}
//---------------------------------------------------------------------------


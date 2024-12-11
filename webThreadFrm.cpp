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
#include <stdio.h>

#include <dir.h>
#include <vcl.h>
#include <vcl/registry.hpp>
#pragma hdrstop

#include "webThreadFrm.h"
#include "webImportFrm.h"
#include "DataUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TWebThreadForm *WebThreadForm = NULL;

//---------------------------------------------------------------------------
__fastcall TWebThreadForm::TWebThreadForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWebThreadForm::FormShow(TObject *)
{
	ComboBoxBrowser->Items->Clear();
	ComboBoxBrowser->Items->Add( "All Browser" );
	for( QueryBrowser->Open(); !QueryBrowser->Eof; QueryBrowser->Next() )
		ComboBoxBrowser->Items->Add( QueryBrowserHTTP_AGENT->AsString );
	QueryBrowser->Close();
	ComboBoxBrowser->ItemIndex = 0;

	ComboBoxStatus->Items->Clear();
	ComboBoxStatus->Items->Add( "All Status" );
	for( QueryStatus->Open(); !QueryStatus->Eof; QueryStatus->Next() )
		ComboBoxStatus->Items->Add( QueryStatusHTTP_STATUS->AsString );
	QueryStatus->Close();
	ComboBoxStatus->ItemIndex = 0;

	theDataSource->DataSet->Open();

}
//---------------------------------------------------------------------------


void __fastcall TWebThreadForm::SortComboBoxChange(TObject *)
{
	AnsiString	newIndex;

	if( SortComboBox->ItemIndex == 0 )
		newIndex = "WEB_DATE_IDX";
	else if( SortComboBox->ItemIndex == 1 )
		newIndex = "WEB_URL_IDX";
	else if( SortComboBox->ItemIndex == 2 )
		newIndex = "WEB_TIME_IDX";

	theDataModule->webThreadTable->IndexName = newIndex;
}
//---------------------------------------------------------------------------

void __fastcall TWebThreadForm::FormClose(TObject *,
	  TCloseAction &Action)
{
	Action = caFree;
	theDataSource->DataSet->Close();
	WebThreadForm = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TWebThreadForm::ButtonImportClick(TObject *Sender)
{
	webImportForm->ShowModal();
	FormShow( Sender );
}
//---------------------------------------------------------------------------



void __fastcall TWebThreadForm::ComboBoxFilterChange(TObject *)
{
	int logID = theDataModule->webThreadTableID->AsInteger;

	AnsiString browser = ComboBoxBrowser->Items->Strings[ComboBoxBrowser->ItemIndex];
	AnsiString status  = ComboBoxStatus->Items->Strings[ComboBoxStatus->ItemIndex];
	AnsiString filter;

	if( ComboBoxBrowser->ItemIndex > 0 )
		filter = AnsiString("HTTP_AGENT='") + browser + "'";

	if( ComboBoxStatus->ItemIndex > 0 )
	{
		if( filter.Length() )
			filter += " AND ";
		filter += AnsiString("HTTP_STATUS=") + status;
	}

	AnsiString oldFilter = theDataSource->DataSet->Filter;
	if( oldFilter != filter )
	{
		theDataSource->DataSet->Close();
		theDataSource->DataSet->Filter = filter;
		theDataSource->DataSet->Filtered = (filter.Length() != 0);
		theDataSource->DataSet->Open();

		TLocateOptions	nix;
		theDataSource->DataSet->Locate( "ID", logID, nix );
	}
}
//---------------------------------------------------------------------------


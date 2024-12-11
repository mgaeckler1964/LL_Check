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

#include "DataUnit.h"
#include "HttpRecurringFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THttpRecurringForm *HttpRecurringForm = NULL;
//---------------------------------------------------------------------------
__fastcall THttpRecurringForm::THttpRecurringForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall THttpRecurringForm::FormClose(TObject *,
      TCloseAction &Action)
{
	Action = caFree;
	TableHttpRecurring->Close();
	HttpRecurringForm = NULL;
}
//---------------------------------------------------------------------------
void __fastcall THttpRecurringForm::FormShow(TObject *)
{
	TableHttpRecurring->Open();
}
//---------------------------------------------------------------------------
void __fastcall THttpRecurringForm::TableHttpRecurringCalcFields(
	  TDataSet *)
{
	try
	{
		TableHttpRecurringSHORT_URL->AsString = TableHttpRecurringHTTP_URL->AsString;
	}
	catch( ... )
	{
		TableHttpRecurringSHORT_URL->AsString = "Unkown";
		TableHttpRecurring->Refresh();
	}
}
//---------------------------------------------------------------------------
void __fastcall THttpRecurringForm::DBGridDrawColumnCell(TObject *,
	  const TRect &Rect, int DataCol, TColumn *Column,
	  TGridDrawState State)
{
	TGridDrawState	empty;

	if( State == empty )
	{
		if( TableHttpRecurringLAST_STATUS->AsInteger != 200 )
			DBGrid->Canvas->Brush->Color = clYellow;
		else if( TableHttpRecurringLAST_TIME->AsFloat >= TableHttpRecurringMAX_TIME->AsFloat )
			DBGrid->Canvas->Brush->Color = clRed;
	}
	DBGrid->DefaultDrawColumnCell( Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------


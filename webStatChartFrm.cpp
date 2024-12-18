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

#include "webStatChartFrm.h"
#include "webStatFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWebStatChartForm *WebStatChartForm;
//---------------------------------------------------------------------------
__fastcall TWebStatChartForm::TWebStatChartForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TWebStatChartForm::reloadChart( void )
{
}
//---------------------------------------------------------------------------
void __fastcall TWebStatChartForm::FormShow(TObject *Sender)
{
	Count->Checked = true;
	reloadData(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TWebStatChartForm::reloadData(TObject *)
{
	TColor colors[]=
	{
		clRed,
		clYellow,
		clGreen,
		clBlue,
		clFuchsia,
		clLime,
		clAqua,
		clPurple,
		clNavy,
		clMaroon,
		clTeal,
		clOlive,
		clWhite,
		clSilver,
		clGray,
		clBlack,
	};
	int		i=0;

	dbSeries->Clear();

	TQuery *theQuery = webStatForm->theQuery;

	theQuery->DisableControls();
	theQuery->First();
	while( !webStatForm->theQuery->Eof )
	{
		AnsiString request = webStatForm->theQueryREQUEST->AsString;

		dbSeries->AddPie(
			Count->Checked
				? webStatForm->theQueryCOUNTER->AsInteger
				: webStatForm->theQueryTOTAL_TIME->AsFloat,
			request.SubString( 1, 30 ),
			colors[(i++)%16]
		);

		theQuery->Next();
	}
	theQuery->EnableControls();
	theQuery->First();
}
//---------------------------------------------------------------------------
void __fastcall TWebStatChartForm::UpDown1ChangingEx(TObject *,
      bool &AllowChange, short NewValue, TUpDownDirection )
{
	if( NewValue >= 0 && NewValue <= 100 )
	{
		AllowChange = true;
		dbSeries->OtherSlice->Value = NewValue;
	}
	else
		AllowChange = false;
}
//---------------------------------------------------------------------------



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

#include "webStatFrm.h"
#include "webStatChartFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TwebStatForm *webStatForm = NULL;
//---------------------------------------------------------------------------
__fastcall TwebStatForm::TwebStatForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TwebStatForm::FormClose(TObject *, TCloseAction &Action)
{
	theQuery->Close();
	Action = caFree;
	webStatForm = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TwebStatForm::CalcClick(TObject *)
{
	ChartButton->Enabled = true;
	theQuery->Close();

   	theQuery->SQL->Clear();
	if( CheckIgnoreQuery->Checked )
		theQuery->SQL->Add(
			"select	substr( lower(http_url), 1, 255 ) as request, "
					"count(*) as counter, "
					"min( exec_time ) / 1000 as mini, "
					"round( avg( exec_time ) / 1000, 3 ) as average, "
					"max( exec_time ) / 1000 as maxi, "
					"sum( exec_time ) / 1000 as total_time, "
					"min( request_date_time ) as first_call, "
					"max( request_date_time ) as last_call "
			"from	WEB_LOGS "
			"where	request_date_time >= :startDate and request_date_time < :endDate "
			"group by substr( lower(http_url), 1, 255 ) "
		);
	else
		theQuery->SQL->Add(
			"select	substr( lower(http_url) || '?' || lower( http_query ), 1, 255 ) as request, "
					"count(*) as counter, "
					"min( exec_time ) / 1000 as mini, "
					"round( avg( exec_time ) / 1000, 3 ) as average, "
					"max( exec_time ) /1000 as maxi, "
					"sum( exec_time ) /1000 as total_time, "
					"min( request_date_time ) as first_call, "
					"max( request_date_time ) as last_call "
			"from	WEB_LOGS "
			"where	request_date_time >= :startDate and request_date_time < :endDate "
			"group by substr( lower(http_url) || '?' || lower( http_query ), 1, 255 ) "
		);

	if( SortComboBox->ItemIndex == 0 )
		theQuery->SQL->Add( "order by counter desc" );
	else if( SortComboBox->ItemIndex == 1 )
		theQuery->SQL->Add( "order by average desc" );
	else if( SortComboBox->ItemIndex == 2 )
		theQuery->SQL->Add( "order by maxi desc" );
	else if( SortComboBox->ItemIndex == 3 )
		theQuery->SQL->Add( "order by total_time desc" );

	if( OneDay->Checked )
	{
		theQuery->ParamByName( "startDate" )->AsDateTime =DateTimePicker->DateTime;
		theQuery->ParamByName( "endDate" )->AsDateTime =DateTimePicker->DateTime+1;
	}
	else
	{
		theQuery->ParamByName( "startDate" )->AsDateTime = EncodeDate( 1900, 1, 1 );
		theQuery->ParamByName( "endDate" )->AsDateTime = EncodeDate( 2900, 1, 1 );
	}
	theQuery->Open();
}
//---------------------------------------------------------------------------

void __fastcall TwebStatForm::FormShow(TObject *)
{
	ChartButton->Enabled = false;
	DateTimePicker->Date = Date();
	SortComboBox->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TwebStatForm::ChartButtonClick(TObject *)
{
	WebStatChartForm->ShowModal();
//	LLStatChartForm->reloadData(Sender);
}
//---------------------------------------------------------------------------


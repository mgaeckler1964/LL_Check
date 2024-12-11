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
#include <stdlib.h>
#include <vcl.h>
#pragma hdrstop

#include "httpChartFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
ThttpChartForm *httpChartForm;

//---------------------------------------------------------------------------
void ThttpChartForm::reloadData( void )
{
	AnsiString		lastDay;
	int				legend, loopCount;
	char			legendBuff[128];
	TQuery			*theQuery = new TQuery( Application );

	theQuery->DatabaseName = "llCheck_DB";
	theQuery->RequestLive = false;
//	theQuery->UniDirectional = true;

	theQuery->SQL->Clear();

	if( endDatePicker->Date < theDatePicker->Date )
		endDatePicker->Date = theDatePicker->Date;

	if( ModeComboBox->ItemIndex == 0 )
	{
		//Average Time per Request and Hour/Day
		theQuery->SQL->Add( "select to_char( request_date_time, 'YYYY-MM-DD' ) as request_date, "
									"to_number(to_char( request_date_time, 'HH24' )) as hour, "
									"sum(loop_count * avg_time)/sum(loop_count) as avg_time, "
									"sum(loop_count) as loop_count " );

		theQuery->SQL->Add( "from	http_thread" );
		theQuery->SQL->Add( "where	request_date_time >= :minDate and" );
		theQuery->SQL->Add( 	"request_date_time < :maxDate and " );
		theQuery->SQL->Add( 	"lower(http_url) = lower(:theFunc) and " );
		theQuery->SQL->Add( 	"complete_flag = :complete_flag" );

		theQuery->SQL->Add( "group by to_char( request_date_time, 'YYYY-MM-DD' ), to_number(to_char( request_date_time, 'HH24' ))" );
		theQuery->SQL->Add( "order by 1, 2" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcComboBox->Items->Strings[funcComboBox->ItemIndex];
		theQuery->ParamByName( "complete_flag" )->AsString = Complete->Checked ? 'Y' : 'N';
	}
	else if( ModeComboBox->ItemIndex == 1 )
	{
		//Average Time per Request and Hour
		theQuery->SQL->Add( "select	to_number(to_char( request_date_time, 'HH24' )) as hour, "
									"sum(loop_count * avg_time)/sum(loop_count) as avg_time, "
									"sum(loop_count) as loop_count " );

		theQuery->SQL->Add( "from	http_thread" );
		theQuery->SQL->Add( "where	request_date_time >= :minDate and" );
		theQuery->SQL->Add( 	"request_date_time < :maxDate and " );
		theQuery->SQL->Add( 	"lower(http_url) = lower(:theFunc) and " );
		theQuery->SQL->Add( 	"complete_flag = :complete_flag" );

		theQuery->SQL->Add( "group by to_number(to_char( request_date_time, 'HH24' ))" );
		theQuery->SQL->Add( "order by 1" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcComboBox->Items->Strings[funcComboBox->ItemIndex];
		theQuery->ParamByName( "complete_flag" )->AsString = Complete->Checked ? 'Y' : 'N';
	}
	else if( ModeComboBox->ItemIndex == 2 )
	{
		//Average Time per Request and User Count
		theQuery->SQL->Add( "select	user_count, "
									"sum(loop_count * avg_time)/sum(loop_count) as avg_time, "
									"sum(loop_count) as loop_count " );

		theQuery->SQL->Add( "from	http_thread" );
		theQuery->SQL->Add( "where	request_date_time >= :minDate and" );
		theQuery->SQL->Add( 	"request_date_time < :maxDate and " );
		theQuery->SQL->Add( 	"lower(http_url) = lower(:theFunc) and " );
		theQuery->SQL->Add( 	"complete_flag = :complete_flag" );

		theQuery->SQL->Add( "group by user_count" );
		theQuery->SQL->Add( "order by 1" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcComboBox->Items->Strings[funcComboBox->ItemIndex];
		theQuery->ParamByName( "complete_flag" )->AsString = Complete->Checked ? 'Y' : 'N';
	}

	theQuery->Open();

	theSeries->Clear();
	dbSeries->Clear();
	GenerateSeries->Clear();

	while( !theQuery->Eof )
	{
		if( ModeComboBox->ItemIndex == 0 )	// Average Time per Request and Hour/Day
			legend = theQuery->FieldByName( "hour" )->AsInteger;
		else if( ModeComboBox->ItemIndex == 1 )	// Average Time per Request and Hour
			legend = theQuery->FieldByName( "hour" )->AsInteger;
		else if( ModeComboBox->ItemIndex == 2 )
			legend = theQuery->FieldByName( "user_count" )->AsInteger;

		loopCount = theQuery->FieldByName( "loop_count" )->AsInteger;
		if( ModeComboBox->ItemIndex == 0
		&&  lastDay != theQuery->FieldByName( "request_date" )->AsString )	// Average Time per Request and Hour/Day
		{
			lastDay = theQuery->FieldByName( "request_date" )->AsString;
			sprintf( legendBuff, "%s %d.%d", lastDay.c_str(), legend, loopCount );
		}
		else
			sprintf( legendBuff, "%d.%d", legend, loopCount );

		theSeries->Add(
			theQuery->FieldByName( "avg_time" )->AsFloat,
			legendBuff,
			clRed
		);

		theQuery->Next();
	}

	theQuery->Close();

	delete theQuery;
}
//---------------------------------------------------------------------------
__fastcall ThttpChartForm::ThttpChartForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall ThttpChartForm::FormShow(TObject *)
{
	funcQuery->Open();
	funcComboBox->Items->Clear();

	while( !funcQuery->Eof )
	{
		funcComboBox->Items->Add( funcQuery->Fields->Fields[0]->AsString );
		funcQuery->Next();
	}
	funcQuery->Close();

	funcComboBox->ItemIndex = 0;
	theDatePicker->Date = Date();
	endDatePicker->Date = Date();
	ModeComboBox->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall ThttpChartForm::CalcButtonClick(TObject *)
{
	reloadData();
}
//---------------------------------------------------------------------------


void __fastcall ThttpChartForm::FormClose(TObject *, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------




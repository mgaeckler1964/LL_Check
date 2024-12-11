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

#include "llFuncSelFrm.h"
#include "llChartFrm.h"

//---------------------------------------------------------------------------
using namespace gak;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLLChartForm *LLChartForm;

typedef enum
{
	Time_per_Request,
	Average_Time_per_Request_and_Hour,
	Average_Time_per_Request_and_Day,
	Total_Time_per_Hour,
	Total_Time_per_Hour_and_Day,
	Total_Time_per_Hour_and_Server,
	Analyze,
	Average_Requests_per_Hour,
	Requests_per_Day,
	Requests_per_Day_and_Server,
	Usage_per_Hour,
	Usage_per_Day
} CHART_TYPES;

//---------------------------------------------------------------------------
void TLLChartForm::enableDisableControls( void )
{
	if( ModeComboBox->ItemIndex == Time_per_Request )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = true;
		funcDBEdit->Visible = true;
		SelectRequestButton->Visible = true;

		endDatePicker->Visible = false;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = false;
		EditMinRequests->Visible = false;
		UpDownMinRequests->Visible = false;
	}
	else if( ModeComboBox->ItemIndex == Average_Requests_per_Hour )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = false;
		funcDBEdit->Visible = false;
		SelectRequestButton->Visible = false;

		endDatePicker->Visible = true;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = true;
		EditMinRequests->Visible = true;
		UpDownMinRequests->Visible = true;
	}
	else if( ModeComboBox->ItemIndex == Average_Time_per_Request_and_Hour )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = true;
		funcDBEdit->Visible = true;
		SelectRequestButton->Visible = true;

		endDatePicker->Visible = true;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = true;
		EditMinRequests->Visible = true;
		UpDownMinRequests->Visible = true;
	}
	else if( ModeComboBox->ItemIndex == Average_Time_per_Request_and_Day )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = true;
		funcDBEdit->Visible = true;
		SelectRequestButton->Visible = true;

		endDatePicker->Visible = true;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = true;
		EditMinRequests->Visible = true;
		UpDownMinRequests->Visible = true;
	}
	else if( ModeComboBox->ItemIndex == Total_Time_per_Hour )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = false;
		funcDBEdit->Visible = false;
		SelectRequestButton->Visible = false;

		endDatePicker->Visible = false;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = false;
		EditMinRequests->Visible = false;
		UpDownMinRequests->Visible = false;
	}
	else if( ModeComboBox->ItemIndex == Total_Time_per_Hour_and_Day )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = false;
		funcDBEdit->Visible = false;
		SelectRequestButton->Visible = false;

		endDatePicker->Visible = true;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = true;
		EditMinRequests->Visible = true;
		UpDownMinRequests->Visible = true;
	}
	else if( ModeComboBox->ItemIndex == Total_Time_per_Hour_and_Server )
	{
		ServerLabel->Visible = false;
		serverComboBox->Visible = false;

		funcLabel->Visible = false;
		funcDBEdit->Visible = false;
		SelectRequestButton->Visible = false;

		endDatePicker->Visible = false;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = false;
		EditMinRequests->Visible = false;
		UpDownMinRequests->Visible = false;
	}
	else if( ModeComboBox->ItemIndex == Analyze )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = true;
		funcDBEdit->Visible = true;
		SelectRequestButton->Visible = true;

		endDatePicker->Visible = false;

		RoundLabel->Visible = true;
		roundEdit->Visible = true;
		roundUpDown->Visible = true;

		LabelMinRequests->Visible = false;
		EditMinRequests->Visible = false;
		UpDownMinRequests->Visible = false;
	}
	else if( ModeComboBox->ItemIndex == Requests_per_Day )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = false;
		funcDBEdit->Visible = false;
		SelectRequestButton->Visible = false;

		endDatePicker->Visible = true;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = true;
		EditMinRequests->Visible = true;
		UpDownMinRequests->Visible = true;
	}
	else if( ModeComboBox->ItemIndex == Requests_per_Day_and_Server )
	{
		ServerLabel->Visible = false;
		serverComboBox->Visible = false;

		funcLabel->Visible = false;
		funcDBEdit->Visible = false;
		SelectRequestButton->Visible = false;

		endDatePicker->Visible = true;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = false;
		EditMinRequests->Visible = false;
		UpDownMinRequests->Visible = false;
	}
	else if( ModeComboBox->ItemIndex == Usage_per_Hour )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = true;
		funcDBEdit->Visible = true;
		SelectRequestButton->Visible = true;

		endDatePicker->Visible = true;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = false;
		EditMinRequests->Visible = false;
		UpDownMinRequests->Visible = false;
	}
	else if( ModeComboBox->ItemIndex == Usage_per_Day )
	{
		ServerLabel->Visible = true;
		serverComboBox->Visible = true;

		funcLabel->Visible = true;
		funcDBEdit->Visible = true;
		SelectRequestButton->Visible = true;

		endDatePicker->Visible = true;

		RoundLabel->Visible = false;
		roundEdit->Visible = false;
		roundUpDown->Visible = false;

		LabelMinRequests->Visible = false;
		EditMinRequests->Visible = false;
		UpDownMinRequests->Visible = false;
	}
}

//---------------------------------------------------------------------------
void TLLChartForm::reloadData( void )
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

	AnsiString	 	selServer =
		serverComboBox->Items->Strings[serverComboBox->ItemIndex];

	AnsiString	 	day;
	int			 	hour;
	double		 	num_requests;
	char		 	hourBuff[32];
	TQuery		 	*theQuery = new TQuery( Application );
	AnsiString 	 	curServer, lastServer = "";
	size_t		 	serverIdx = (size_t)-1,
					valueCount, averageCount;
	TLineSeries	 	*theLine;
	ArrayOfFloats	theAverage;
	bool		 	calcAverage = false;

	theQuery->DatabaseName = "llCheck_DB";
	theQuery->RequestLive = false;
//	theQuery->UniDirectional = true;

	theQuery->SQL->Clear();

	if( endDatePicker->Date < theDatePicker->Date )
		endDatePicker->Date = theDatePicker->Date;

	if( ModeComboBox->ItemIndex == Time_per_Request )
	{
		// Time per Request
		theQuery->SQL->Add( "select	to_number(to_char( l.request_date_time, 'HH24' )) as hour, "
									"l.exec_time, l.sql_time, l.req_sql_time, l.req_sql_time_loged, l.generate_time" );
		theQuery->SQL->Add( "from	llthread l, server s" );
		theQuery->SQL->Add( "where	l.request_date_time >= :minDate and" );
		theQuery->SQL->Add( 	"l.request_date_time < :maxDate and " );
		theQuery->SQL->Add( 	"l.server = s.id and " );
		if( ignoreObjId )
			theQuery->SQL->Add( 	"lower(l.func) = lower(:theFunc)" );
		else
			theQuery->SQL->Add( 	"lower(l.func) || '(' || to_char(l.object_id) || ')' = lower(:theFunc)" );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "order by l.request_date_time" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = theDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcDBEdit->Text;

		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Average_Requests_per_Hour )
	{
		//Requests per Hour
		theQuery->SQL->Add( "select l.hour, sum(l.num_requests ) as num_requests" );
		theQuery->SQL->Add( "from chart_requests_per_hour l, server s" );
		theQuery->SQL->Add( "where l.day >= :minDate and" );
		theQuery->SQL->Add( 	"l.day < :maxDate and" );
		theQuery->SQL->Add( 	"l.server = s.id" );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "having sum(l.num_requests) >= :minRequests" );

		theQuery->SQL->Add( "group by l.hour" );
		theQuery->SQL->Add( "order by l.hour" );

		theQuery->ParamByName( "minRequests" )->AsInteger = UpDownMinRequests->Position;
		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;

		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Average_Time_per_Request_and_Hour )
	{
		//Average Time per Request and Hour
		theQuery->SQL->Add( "select	l.hour, "
									"sum(l.exec_time)/sum(l.num_requests) as exec_time, "
									"sum(l.sql_time)/sum(l.num_requests) as sql_time, "
									"sum(l.req_sql_time)/sum(l.num_requests) as req_sql_time, "
									"sum(l.req_sql_time_loged)/sum(l.num_requests) as req_sql_time_loged, "
									"sum(l.generate_time)/sum(l.num_requests) as generate_time, "
									"sum(l.num_requests) as num_requests " );
		theQuery->SQL->Add( "from	LLTHREAD_SUMMARY l, server s" );
		theQuery->SQL->Add( "where	l.request_date_time >= :minDate and" );
		theQuery->SQL->Add( 	"l.request_date_time < :maxDate and " );
		theQuery->SQL->Add( 	"l.server = s.id and " );
		if( ignoreObjId )
			theQuery->SQL->Add( 	"lower(l.func) = lower(:theFunc)" );
		else
			theQuery->SQL->Add( 	"lower(l.func) || '(' || to_char(l.object_id) || ')' = lower(:theFunc)" );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "having sum(l.num_requests) >= :minRequests" );

		theQuery->SQL->Add( "group by l.hour" );
		theQuery->SQL->Add( "order by l.hour" );

		theQuery->ParamByName( "minRequests" )->AsInteger = UpDownMinRequests->Position;
		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcDBEdit->Text;
		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Average_Time_per_Request_and_Day )
	{
		//Average Time per Request and Day
		theQuery->SQL->Add( "select	to_char( l.request_date_time, 'YYYY-MM-DD' ) as day, "
									"sum(l.exec_time)/sum(l.num_requests) as exec_time, "
									"sum(l.sql_time)/sum(l.num_requests) as sql_time, "
									"sum(l.req_sql_time)/sum(l.num_requests) as req_sql_time, "
									"sum(l.req_sql_time_loged)/sum(l.num_requests) as req_sql_time_loged, "
									"sum(l.generate_time)/sum(l.num_requests) as generate_time, "
									"sum(l.num_requests) as num_requests " );

		theQuery->SQL->Add( "from	LLTHREAD_SUMMARY l, server s" );
		theQuery->SQL->Add( "where	l.request_date_time >= :minDate and" );
		theQuery->SQL->Add( 	"l.request_date_time < :maxDate and " );
		theQuery->SQL->Add( 	"l.server = s.id and " );
		if( ignoreObjId )
			theQuery->SQL->Add( 	"lower(l.func) = lower(:theFunc)" );
		else
			theQuery->SQL->Add( 	"lower(l.func) || '(' || to_char(l.object_id) || ')' = lower(:theFunc)" );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "having sum(l.num_requests) >= :minRequests" );

		theQuery->SQL->Add( "group by to_char( l.request_date_time, 'YYYY-MM-DD' )" );
		theQuery->SQL->Add( "order by 1" );

		theQuery->ParamByName( "minRequests" )->AsInteger = UpDownMinRequests->Position;
		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcDBEdit->Text;
		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Total_Time_per_Hour )
	{
		// Total Time per Hour
		theQuery->SQL->Add( "select	l.hour, "
									"sum(l.exec_time) as exec_time, "
									"sum(l.sql_time) as sql_time, "
									"sum(l.req_sql_time) as req_sql_time, "
									"sum(l.req_sql_time_loged) as req_sql_time_loged, "
									"sum(l.generate_time) as generate_time, "
									"sum(l.num_requests) as num_requests" );

		theQuery->SQL->Add( "from	chart_requests_per_hour l, server s" );
		theQuery->SQL->Add( "where	l.day >= :minDate and" );
		theQuery->SQL->Add( 	"l.day < :maxDate and " );
		theQuery->SQL->Add( 	"l.server = s.id " );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "group by l.hour" );
		theQuery->SQL->Add( "order by l.hour" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = theDatePicker->Date+1;
		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Total_Time_per_Hour_and_Day )
	{
		// Total Time per Hour and Day
		theQuery->SQL->Add( "select	to_char( l.day, 'YYYY-MM-DD' ) as day,"
									"l.hour, "
									"sum(l.exec_time) as exec_time, "
									"sum(l.sql_time) as sql_time, "
									"sum(l.req_sql_time) as req_sql_time, "
									"sum(l.req_sql_time_loged) as req_sql_time_loged, "
									"sum(l.generate_time) as generate_time, "
									"sum(l.num_requests) as num_requests" );
		theQuery->SQL->Add( "from chart_requests_per_hour l, server s" );
		theQuery->SQL->Add( "where	l.day >= :minDate and" );
		theQuery->SQL->Add( 	"l.day < :maxDate and " );
		theQuery->SQL->Add( 	"l.server = s.id " );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "having sum(l.num_requests) >= :minRequests" );

		theQuery->SQL->Add( "group by to_char( l.day, 'YYYY-MM-DD' ), l.hour" );
		theQuery->SQL->Add( "order by 1, 2" );

		theQuery->ParamByName( "minRequests" )->AsInteger = UpDownMinRequests->Position;
		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Total_Time_per_Hour_and_Server )
	{
		// Total Time per Hour
		theQuery->SQL->Add( "select	s.server_name, l.hour, l.exec_time " );
		theQuery->SQL->Add( "from	chart_requests_per_hour l, server s" );
		theQuery->SQL->Add( "where	l.day >= :minDate and" );
		theQuery->SQL->Add( 	"l.day < :maxDate and " );
		theQuery->SQL->Add( 	"l.server = s.id " );
		theQuery->SQL->Add( "order by s.server_name, l.hour" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = theDatePicker->Date+1;
	}
	else if( ModeComboBox->ItemIndex == Analyze )
	{
		// Analyze
		theQuery->SQL->Add( (AnsiString)"select round( l.exec_time, " + roundEdit->Text + " ) tim, count(*) num_requests " );
		theQuery->SQL->Add( "from	llthread l, server s" );
		theQuery->SQL->Add( "where	l.request_date_time >= :minDate and " );
		theQuery->SQL->Add( 	"l.request_date_time < :maxDate and " );
		theQuery->SQL->Add( 	"l.server = s.id and " );
		if( ignoreObjId )
			theQuery->SQL->Add( 	"lower(l.func) = lower(:theFunc)" );
		else
			theQuery->SQL->Add( 	"lower(l.func) || '(' || to_char(l.object_id) || ')' = lower(:theFunc)" );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( (AnsiString)"group by round( l.exec_time, " + roundEdit->Text + " )" );
		theQuery->SQL->Add( (AnsiString)"order by 1" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = theDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcDBEdit->Text;
		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Requests_per_Day )
	{
		//Requests per Day
		theQuery->SQL->Add( "select to_char( l.day, 'YYYY-MM-DD' ) as day, sum(num_requests ) as num_requests" );
		theQuery->SQL->Add( "from chart_requests_per_day l, server s" );
		theQuery->SQL->Add( "where l.day >= :minDate and" );
		theQuery->SQL->Add( 	"l.day < :maxDate and" );
		theQuery->SQL->Add( 	"l.server = s.id" );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "having sum(l.num_requests) >= :minRequests" );

		theQuery->SQL->Add( "group by to_char( l.day, 'YYYY-MM-DD' )" );
		theQuery->SQL->Add( "order by 1" );

		theQuery->ParamByName( "minRequests" )->AsInteger = UpDownMinRequests->Position;
		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;

		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Requests_per_Day_and_Server )
	{
		//Requests per Day and Server

		theQuery->SQL->Add( "select s.server_name, to_char( l.day, 'YYYY-MM-DD' ) as day, num_requests" );
		theQuery->SQL->Add( "from chart_requests_per_day l, server s" );
		theQuery->SQL->Add( "where l.day >= :minDate and" );
		theQuery->SQL->Add( 	"l.day < :maxDate and" );
		theQuery->SQL->Add( 	"l.server = s.id" );

		theQuery->SQL->Add( "order by 1, 2" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
	}
	else if( ModeComboBox->ItemIndex == Usage_per_Hour )
	{
		theQuery->SQL->Add( "select hour, avg(num_requests) as num_requests" );
		theQuery->SQL->Add( "from llthread_summary l, server s" );
		theQuery->SQL->Add( "where l.request_date_time >= :minDate" );
		theQuery->SQL->Add( "and l.request_date_time < :maxDate" );
		theQuery->SQL->Add( "and l.server = s.id" );
		if( ignoreObjId )
			theQuery->SQL->Add( "and lower(l.func) = lower(:theFunc)" );
		else
			theQuery->SQL->Add( "and lower(l.func) || '(' || to_char(l.object_id) || ')' = lower(:theFunc)" );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "group by hour" );
		theQuery->SQL->Add( "order by 1" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcDBEdit->Text;

		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}
	else if( ModeComboBox->ItemIndex == Usage_per_Day )
	{
		theQuery->SQL->Add( "select to_char( l.request_date_time, 'YYYY-MM-DD' ) as day, sum(num_requests) as num_requests" );
		theQuery->SQL->Add( "from llthread_summary l, server s" );
		theQuery->SQL->Add( "where l.request_date_time >= :minDate" );
		theQuery->SQL->Add( "and l.request_date_time < :maxDate" );
		theQuery->SQL->Add( "and l.server = s.id" );
		if( ignoreObjId )
			theQuery->SQL->Add( "and lower(l.func) = lower(:theFunc)" );
		else
			theQuery->SQL->Add( "and lower(l.func) || '(' || to_char(l.object_id) || ')' = lower(:theFunc)" );

		if( selServer != "All" )
			theQuery->SQL->Add( "and s.server_name = :selServer" );

		theQuery->SQL->Add( "group by to_char( l.request_date_time, 'YYYY-MM-DD' )" );
		theQuery->SQL->Add( "order by 1" );

		theQuery->ParamByName( "minDate" )->AsDateTime = theDatePicker->Date;
		theQuery->ParamByName( "maxDate" )->AsDateTime = endDatePicker->Date+1;
		theQuery->ParamByName( "theFunc" )->AsString = funcDBEdit->Text;

		if( selServer != "All" )
			theQuery->ParamByName( "selServer" )->AsString = selServer;
	}

	theQuery->Open();

	theChart->RemoveAllSeries();
	for(
		gak::Array<TLineSeries*>::iterator it = series.begin(),
			endIT = series.end();
		it != endIT;
		++it
	)
	{
		delete *it;
	}
	series.clear();

	switch( ModeComboBox->ItemIndex )
	{
		case Time_per_Request:
		case Average_Time_per_Request_and_Hour:
		case Total_Time_per_Hour:
		case Total_Time_per_Hour_and_Day:
		case Average_Time_per_Request_and_Day:

			theLine = new TLineSeries( this );
			theLine->Title = "Total Time";
			theLine->SeriesColor = clRed;
			series[0] = theLine;

			theLine = new TLineSeries( this );
			theLine->Title = "SQL Time";
			theLine->SeriesColor = clGreen;
			series[1] = theLine;

			theLine = new TLineSeries( this );
			theLine->Title = "Req. SQL Time";
			theLine->SeriesColor = clBlue;
			series[2] = theLine;

			theLine = new TLineSeries( this );
			theLine->Title = "Req. SQL Time Logged";
			theLine->SeriesColor = clBlack;
			series[3] = theLine;

			theLine = new TLineSeries( this );
			theLine->Title = "Output Time";
			theLine->SeriesColor = clYellow;
			series[4] = theLine;

			calcAverage = true;
			theChart->LeftAxis->Title->Caption = "Seconds";

		case Average_Requests_per_Hour:
		case Usage_per_Hour:
		case Analyze:
		case Requests_per_Day:
		case Usage_per_Day:
			if( ModeComboBox->ItemIndex != Time_per_Request )
			{
				theLine = new TLineSeries( this );
				theLine->Title = "Num. Requests";
				theLine->SeriesColor = clWhite;
				theLine->VertAxis = aRightAxis;
				series.addElement( theLine );
				theChart->RightAxis->Title->Caption = "Count";

				if( series.size() > 1 )
					theChart->RightAxis->Grid->Visible = false;
				else
					theChart->RightAxis->Grid->Visible = true;
			}
			break;
	}
	for(
		gak::Array<TLineSeries*>::iterator it = series.begin(),
			endIT = series.end();
		it != endIT;
		++it
	)
	{
		(*it)->ParentChart = theChart;
	}

	while( !theQuery->Eof )
	{
		if( ModeComboBox->ItemIndex == Time_per_Request
		||	ModeComboBox->ItemIndex == Average_Time_per_Request_and_Hour
		||	ModeComboBox->ItemIndex == Total_Time_per_Hour )
		{
			hour = theQuery->FieldByName( "hour" )->AsInteger;
			itoa( hour, hourBuff, 10 );

			series[0]->Add(
				theQuery->FieldByName( "exec_time" )->AsFloat,
				hourBuff,
				series[0]->SeriesColor
			);
			series[1]->Add(
				theQuery->FieldByName( "sql_time" )->AsFloat,
				hourBuff,
				series[1]->SeriesColor
			);
			series[2]->Add(
				theQuery->FieldByName( "req_sql_time" )->AsFloat,
				hourBuff,
				series[2]->SeriesColor
			);
			series[3]->Add(
				theQuery->FieldByName( "req_sql_time_loged" )->AsFloat,
				hourBuff,
				series[3]->SeriesColor
			);
			series[4]->Add(
				theQuery->FieldByName( "generate_time" )->AsFloat,
				hourBuff,
				series[4]->SeriesColor
			);
			if( ModeComboBox->ItemIndex != Time_per_Request )
			{
				series[5]->Add(
					theQuery->FieldByName( "num_requests" )->AsInteger,
					hourBuff,
					series[5]->SeriesColor
				);
			}
		}
		else if( ModeComboBox->ItemIndex == Total_Time_per_Hour_and_Server )
		{
			hour = theQuery->FieldByName( "hour" )->AsInteger;
			itoa( hour, hourBuff, 10 );

			curServer = theQuery->FieldByName( "server_name" )->AsString;
			if( curServer != lastServer )
			{
				theLine = new TLineSeries( this );
				theLine->Title = curServer;
				theLine->ParentChart = theChart;
				series[++serverIdx] = theLine;
				theLine->SeriesColor = colors[serverIdx%16];
				lastServer = curServer;
			}
			series[serverIdx]->Add(
				theQuery->FieldByName( "exec_time" )->AsFloat,
				hourBuff,
				series[serverIdx]->SeriesColor
			);
		}
		else if( ModeComboBox->ItemIndex == Average_Time_per_Request_and_Day
		|| ModeComboBox->ItemIndex == Total_Time_per_Hour_and_Day )
		{
			day = theQuery->FieldByName( "day" )->AsString;
			if( ModeComboBox->ItemIndex == Total_Time_per_Hour_and_Day )
			{
				day += ':';
				day += theQuery->FieldByName( "hour" )->AsString;
			}

			series[0]->Add(
				theQuery->FieldByName( "exec_time" )->AsFloat,
				day.c_str(),
				series[0]->SeriesColor
			);
			series[1]->Add(
				theQuery->FieldByName( "sql_time" )->AsFloat,
				day.c_str(),
				series[1]->SeriesColor
			);
			series[2]->Add(
				theQuery->FieldByName( "req_sql_time" )->AsFloat,
				day.c_str(),
				series[2]->SeriesColor
			);
			series[3]->Add(
				theQuery->FieldByName( "req_sql_time_loged" )->AsFloat,
				day.c_str(),
				series[3]->SeriesColor
			);
			series[4]->Add(
				theQuery->FieldByName( "generate_time" )->AsFloat,
				day.c_str(),
				series[4]->SeriesColor
			);
			series[5]->Add(
				theQuery->FieldByName( "num_requests" )->AsInteger,
				hourBuff,
				series[5]->SeriesColor
			);
		}
		else if( ModeComboBox->ItemIndex == Average_Requests_per_Hour
		|| ModeComboBox->ItemIndex == Usage_per_Hour )
		{
			// requests per hour
			num_requests = theQuery->FieldByName( "num_requests" )->AsFloat;
			hour = theQuery->FieldByName( "hour" )->AsInteger;

			num_requests /= ((int)endDatePicker->Date - (int)theDatePicker->Date)+1;

			series[0]->Add(
				num_requests,
				itoa( hour, hourBuff, 10 ),
				series[0]->SeriesColor
			 );
		}
		else if( ModeComboBox->ItemIndex == Analyze )
		{
			sprintf( hourBuff, "%.*f", (int)roundUpDown->Position, theQuery->FieldByName( "tim" )->AsFloat );
			series[0]->Add(
				theQuery->FieldByName( "num_requests" )->AsInteger,
				hourBuff,
				series[0]->SeriesColor
			 );
		}
		else if( ModeComboBox->ItemIndex == Requests_per_Day
		|| ModeComboBox->ItemIndex == Usage_per_Day )
		{
			// requests per day
			num_requests = theQuery->FieldByName( "num_requests" )->AsInteger;
			day = theQuery->FieldByName( "day" )->AsString;

			doLogValue( num_requests );

			series[0]->Add(
				num_requests,
				day.c_str(),
				series[0]->SeriesColor
			 );
		}
		else if( ModeComboBox->ItemIndex == Requests_per_Day_and_Server )
		{
			// requests per day and server
			curServer = theQuery->FieldByName( "server_name" )->AsString;
			if( curServer != lastServer )
			{
				theLine = new TLineSeries( this );
				theLine->Title = curServer;
				theLine->ParentChart = theChart;
				series[++serverIdx] = theLine;
				theLine->SeriesColor = colors[serverIdx%16];
				lastServer = curServer;
			}

			num_requests = theQuery->FieldByName( "num_requests" )->AsInteger;
			day = theQuery->FieldByName( "day" )->AsString;

			series[serverIdx]->Add(
				num_requests,
				day.c_str(),
				series[serverIdx]->SeriesColor
			 );
		}
		theQuery->Next();
	}

	theQuery->Close();

	delete theQuery;

	valueCount = series[0]->Count();
	averageCount = valueCount / 32;
	if( calcAverage )
	{
		if( averageCount > 2 )
		{
			theLine = new TLineSeries( this );
			theLine->Title = "Average";
			theLine->SeriesColor = clBlack;
			theLine->ParentChart = theChart;
			series.addElement( theLine );

			for( size_t i=0; i<valueCount; i++ )
			{
				theAverage[i%averageCount] = series[0]->YValue[i];
				theLine->Add(
					theAverage.average(),
					series[0]->XLabel[i],
					theLine->SeriesColor
				);
			}
		}
	}

	if( averageCount < 1 )
		averageCount = 1;
	TrackBar->Min = 1;
	TrackBar->Max = averageCount;
	TrackBar->Position = 1;
	theChart->MaxPointsPerPage = 0;

	ScrollBar->Min = 0;
	ScrollBar->Max = 0;
	ScrollBar->Position = 0;
}

//---------------------------------------------------------------------------
__fastcall TLLChartForm::TLLChartForm(TComponent* Owner)
	: TForm(Owner)
{
	ignoreObjId = false;
}
//---------------------------------------------------------------------------
void __fastcall TLLChartForm::FormShow(TObject *)
{
	funcQuery->Params->Items[0]->AsString = "%";
	funcQuery->Params->Items[1]->AsString = "%";
	funcQuery->Open();

	serverQuery->Open();
	serverComboBox->Items->Clear();
	serverComboBox->Items->Add( "All" );

	while( !serverQuery->Eof )
	{
		serverComboBox->Items->Add( serverQuery->Fields->Fields[0]->AsString );
		serverQuery->Next();
	}
	serverQuery->Close();

	serverComboBox->ItemIndex = 0;
	theDatePicker->Date = Sysutils::Date();
	endDatePicker->Date = Sysutils::Date();
	ModeComboBox->ItemIndex = Time_per_Request;

	enableDisableControls();
}
//---------------------------------------------------------------------------
void __fastcall TLLChartForm::CalcButtonClick(TObject *)
{
	reloadData();
}
//---------------------------------------------------------------------------


void __fastcall TLLChartForm::FormClose(TObject *, TCloseAction &Action)
{
	funcQuery->Close();
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TLLChartForm::ModeComboBoxChange(TObject *)
{
	enableDisableControls();
}
//---------------------------------------------------------------------------

void __fastcall TLLChartForm::SelectRequestButtonClick(TObject *)
{
	llFuncSelForm->functionDBGrid->DataSource = funcSource;
	ignoreObjId = llFuncSelForm->ShowModal( ignoreObjId );
}
//---------------------------------------------------------------------------
void __fastcall TLLChartForm::TrackBarChange(TObject *)
{
	if( series.size() )
	{
		size_t valueCount = series[0]->Count();
		size_t newPageSize = valueCount/TrackBar->Position;
		if( valueCount % TrackBar->Position )
			newPageSize += 1;
		theChart->MaxPointsPerPage = newPageSize;
		ScrollBar->Min = 0;
		ScrollBar->Max = theChart->NumPages()-1;
		ScrollBar->Position = 0;
		theChart->Page = 1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TLLChartForm::ScrollBarChange(TObject *)
{
	theChart->Page = ScrollBar->Position+1;
}
//---------------------------------------------------------------------------

void __fastcall TLLChartForm::CheckBoxSizerClick(TObject *)
{
	PanelSizer->Visible = CheckBoxSizer->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TLLChartForm::CheckBoxLegendClick(TObject *)
{
	theChart->Legend->Visible = CheckBoxLegend->Checked;
}
//---------------------------------------------------------------------------


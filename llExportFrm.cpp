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

#include <vcl.h>

#include <gak/fmtNumber.h>
#include <winlib/winlib.h>

#pragma hdrstop

#include "llExportFrm.h"

using namespace gak;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TllExportForm *llExportForm;

//---------------------------------------------------------------------------
class ExportThread : public TThread
{
private:
	bool	isRunning;

	void doExport( void );

protected:
	void __fastcall Execute();
public:
	__fastcall ExportThread( bool CreateSuspended ) : TThread( CreateSuspended )
	{
		isRunning = false;
	};
	bool IsRunning( void ) const
	{
		return isRunning;
	}
};

static ExportThread	*theExporter = NULL;

//---------------------------------------------------------------------------

void ExportThread::doExport( void )
{
	int				i, counter;
	STRING			serverName;
	STRING			csvFileName;
	unsigned short	year, month, day;
	unsigned short	hour, min, sec, msec;

	STRING		basePath = llExportForm->PathEdit->Text.c_str();
	AnsiString	lastServer = "";
	int			lastThread = -1;
	int			serverCount = llExportForm->ServerListBox->Items->Count;
	FILE		*csvFp = NULL;

	llExportForm->StatusLabel->Caption = "Counting";
	llExportForm->ProgressBar->Position = 0;

	if( basePath == "" || basePath[strlen(basePath)-1] != '\\' )
		basePath += '\\';

	llExportForm->CountQuery->SQL->Clear();
	llExportForm->CountQuery->SQL->Add(
		"select count(*) as counter "
		"from llthread, server "
		"where llthread.server = server.id "
	);
	llExportForm->CountQuery->SQL->Add( "and server_name in ( 'cresd_dummy_server'" );
	for( i=0; i<serverCount; i++ )
	{
		if( llExportForm->ServerListBox->Selected[i] )
		{
			serverName = ", '";
			serverName += llExportForm->ServerListBox->Items->Strings[i].c_str();
			serverName += '\'';
			llExportForm->CountQuery->SQL->Add( (const char*)serverName );
		}
	}
	llExportForm->CountQuery->SQL->Add( ")" );
	llExportForm->CountQuery->Open();
	counter = llExportForm->CountQueryCOUNTER->AsInteger;
	llExportForm->CountQuery->Close();

	if( counter )
	{
		llExportForm->ProgressBar->Max = counter;

		llExportForm->StatusLabel->Caption = "Exporting";

		llExportForm->TimingsQuery->SQL->Clear();
		llExportForm->TimingsQuery->SQL->Add(
			"select * "
			"from llthread, server "
			"where llthread.server = server.id "
		);
		llExportForm->TimingsQuery->SQL->Add( "and server_name in ( 'cresd_dummy_server'" );
		for( i=0; i<serverCount; i++ )
		{
			if( llExportForm->ServerListBox->Selected[i] )
			{
				serverName = ", '";
				serverName += llExportForm->ServerListBox->Items->Strings[i].c_str();
				serverName += '\'';
				llExportForm->TimingsQuery->SQL->Add( (const char*)serverName );
			}
		}
		llExportForm->TimingsQuery->SQL->Add( ") order by server_name, thread, request_date_time" );

		try
		{
			llExportForm->TimingsQuery->Open();
			counter = 0;
			while( !llExportForm->TimingsQuery->Eof && !Terminated )
			{
				if( (lastThread != llExportForm->TimingsQueryTHREAD->AsInteger)
				||  (lastServer != llExportForm->TimingsQuerySERVER_NAME->AsString) )
				{
					lastThread = llExportForm->TimingsQueryTHREAD->AsInteger;
					lastServer = llExportForm->TimingsQuerySERVER_NAME->AsString;

					if( csvFp )
					{
						fclose( csvFp );
						csvFp = NULL;
					}

					csvFileName = basePath;
					csvFileName += llExportForm->TimingsQuerySERVER_NAME->AsString.c_str();
					csvFileName += '_';
					csvFileName += formatNumber( lastThread );
					csvFileName += ".csv";

					csvFp = fopen( csvFileName, "w" );
					if( !csvFp )
					{
						Application->MessageBox( "Error: Cannot create CSV File", csvFileName, MB_ICONERROR );
						break;
					}
					fputs( "Date,Time,StartTick,Thread#,User Name,IP address,Function.Action,Exec. Time,SQL Time,SQL Count,GenerateOutput Time,Object ID,Parent ID,Misc Args,error\n", csvFp );
				}

				llExportForm->TimingsQueryREQUEST_DATE_TIME->AsDateTime.DecodeDate( &year, &month, &day );
				llExportForm->TimingsQueryREQUEST_DATE_TIME->AsDateTime.DecodeTime( &hour, &min, &sec, &msec );
				fprintf( csvFp, "%02d/%02d/%04d,%02d:%02d:%02d,%d,%d,?,?,%s,%f,%f,%d,%f,%d,%d,%s,%s\n",
					month, day, year,
					hour, min, sec,
					llExportForm->TimingsQuerySTART_TICK->AsInteger,
					lastThread,
					llExportForm->TimingsQueryFUNC->AsString.c_str(),
					llExportForm->TimingsQueryEXEC_TIME->AsFloat,
					llExportForm->TimingsQuerySQL_TIME->AsFloat,
					llExportForm->TimingsQuerySQL_COUNT->AsInteger,
					llExportForm->TimingsQueryGENERATE_TIME->AsFloat,
					llExportForm->TimingsQueryOBJECT_ID->AsInteger,
					llExportForm->TimingsQueryPARENT_ID->AsInteger,
					llExportForm->TimingsQueryMISRC_ARGS->AsString.c_str(),
					llExportForm->TimingsQueryERROR->AsString.c_str()
				);

				llExportForm->TimingsQuery->Next();
				llExportForm->ProgressBar->Position = ++counter;
			}

			llExportForm->TimingsQuery->Close();
			if( csvFp )
				fclose( csvFp );
		}
		catch( ... )
		{
			llExportForm->StatusLabel->Caption = "Error";

			if( csvFp )
				fclose( csvFp );
			throw;
		}
	}

	llExportForm->StatusLabel->Caption = Terminated ? "Terminated" : "Finish";
}
//---------------------------------------------------------------------------
void __fastcall ExportThread::Execute()
{
	isRunning = true;
	try
	{
		doExport();
	}
	catch( ... )
	{
		isRunning = false;
		throw;
	}
	isRunning = false;
}

//---------------------------------------------------------------------------
__fastcall TllExportForm::TllExportForm(TComponent* Owner)
	: TForm(Owner)
{
}
void __fastcall TllExportForm::StartStopButtonClick(TObject *)
{
	if( !theExporter )
	{
		theExporter = new ExportThread( false );

		StartStopButton->Caption = "Stop";
		CancelCloseButton->Caption = "Close";
		CancelCloseButton->Enabled = false;
		PathEdit->Enabled = false;
		ServerListBox->Enabled = false;

		threadTimer->Enabled = true;
	}
	else
		theExporter->Terminate();
}

//---------------------------------------------------------------------------
void __fastcall TllExportForm::CancelCloseButtonClick(TObject *)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TllExportForm::FormShow(TObject *)
{
	StartStopButton->Enabled = false;
	StartStopButton->Caption = "Start";
	CancelCloseButton->Enabled = true;
	CancelCloseButton->Caption = "Cancel";
	PathEdit->Enabled = true;
	ServerListBox->Enabled = true;

	ProgressBar->Position = 0;

	ServerListBox->Items->Clear();
	ServerQuery->Open();
	while( !ServerQuery->Eof )
	{
		ServerListBox->Items->Add( ServerQuery->Fields->Fields[0]->AsString );
		ServerQuery->Next();
	}
	ServerQuery->Close();
}
//---------------------------------------------------------------------------

void __fastcall TllExportForm::EnableDisableOK(TObject *)
{
	if( ServerListBox->SelCount && PathEdit->Text > "" )
		StartStopButton->Enabled = true;
	else
		StartStopButton->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TllExportForm::FormClose(TObject *,
	  TCloseAction &Action)
{
	if( theExporter )
		Action = caNone;
}
//---------------------------------------------------------------------------

void __fastcall TllExportForm::FormCloseQuery(TObject *,
	  bool &CanClose)
{
	CanClose = theExporter ? false : true;
}
//---------------------------------------------------------------------------

void __fastcall TllExportForm::threadTimerTimer(TObject *)
{
	if( theExporter && !theExporter->IsRunning() )
	{
		delete theExporter;
		theExporter = NULL;
	}
	if( !theExporter )
	{
		StartStopButton->Caption = "Start";
		CancelCloseButton->Enabled = true;
		PathEdit->Enabled = true;
		ServerListBox->Enabled = true;
		threadTimer->Enabled = false;
	}
}
//---------------------------------------------------------------------------


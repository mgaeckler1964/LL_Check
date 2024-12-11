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
#include <dir.h>
#pragma hdrstop

#include "DataUnit.h"
#include "DeleteFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TtheDataModule *theDataModule;
//---------------------------------------------------------------------------
__fastcall TtheDataModule::TtheDataModule(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void TtheDataModule::openDatabase( const char *appName )
{
	const char	*temp;
	char		buffer[128];
	AnsiString	privateDir = "C:\\";

	if( (temp=getenv("TEMP")) != NULL )
		privateDir = temp;
	if( privateDir[privateDir.Length()] != '\\' )
		privateDir += '\\';

	privateDir += appName;
	sprintf( buffer, "%d", (int)GetCurrentProcessId() );
	privateDir += buffer;
	mkdir( privateDir.c_str() );

	Session->PrivateDir = privateDir;

	try
	{
		Session->Open();
//		Session->NetFileDir = "";
		llCheck_DB->Open();
	}
	catch( Exception &e )
	{
		AnsiString	msg = "Unable to connect to database.\n";
		msg += e.Message.c_str();
		Application->MessageBox(
			msg.c_str(), "Error", MB_ICONSTOP
		);
		exit( 1 );
	}
	catch( ... )
	{
		Application->MessageBox(
			"Unable to connect to database.\nUnkown Error.",
			"Error", MB_ICONSTOP
		);
		exit( 1 );
	}
}

//---------------------------------------------------------------------------
void TtheDataModule::updateLLFunctionsTable( void )
{
	bool inTransaction = llCheck_DB->InTransaction;

	if( !inTransaction && !llCheck_DB->InTransaction )
		theDataModule->llCheck_DB->StartTransaction();

	try
	{
		llFunctionsTable->EmptyTable();
		updateLLFunctionsQuery->ExecSQL();
	}
	catch( ... )
	{
		if( !inTransaction && llCheck_DB->InTransaction )
			llCheck_DB->Rollback();

		throw;
	}

	if( !inTransaction && llCheck_DB->InTransaction )
		llCheck_DB->Commit();

}

void TtheDataModule::updateWebFunctionsTable( void )
{
	bool inTransaction = llCheck_DB->InTransaction;

	if( !inTransaction && !llCheck_DB->InTransaction )
		theDataModule->llCheck_DB->StartTransaction();

	try
	{
		webFunctionsTable->EmptyTable();
		updateWebFunctionsQuery->ExecSQL();
	}
	catch( ... )
	{
		if( !inTransaction && llCheck_DB->InTransaction )
			llCheck_DB->Rollback();

		throw;
	}

	if( !inTransaction && llCheck_DB->InTransaction )
		llCheck_DB->Commit();

}

void __fastcall TtheDataModule::ServerTableBeforeDelete(TDataSet *)
{
	bool inTransaction = llCheck_DB->InTransaction;

	if( !inTransaction && !llCheck_DB->InTransaction )
		theDataModule->llCheck_DB->StartTransaction();

	try
	{
		TQuery	*deleteSQL = new TQuery( NULL );
		deleteSQL->DatabaseName = "llCheck_DB";

		deleteSQL->SQL->Clear();
		deleteSQL->SQL->Add( "delete from chart_requests_per_day where SERVER = :theServer" );
		deleteSQL->Params->Items[0]->AsInteger = ServerTableID->AsInteger;
		deleteSQL->ExecSQL();

		deleteSQL->SQL->Clear();
		deleteSQL->SQL->Add( "delete from chart_requests_per_hour where SERVER = :theServer" );
		deleteSQL->Params->Items[0]->AsInteger = ServerTableID->AsInteger;
		deleteSQL->ExecSQL();

		deleteSQL->SQL->Clear();
		deleteSQL->SQL->Add( "delete from LLTHREAD where SERVER = :theServer" );
		deleteSQL->Params->Items[0]->AsInteger = ServerTableID->AsInteger;
		deleteSQL->ExecSQL();

		deleteSQL->SQL->Clear();
		deleteSQL->SQL->Add( "delete from LLTHREAD_SUMMARY_TABLE where SERVER = :theServer" );
		deleteSQL->Params->Items[0]->AsInteger = ServerTableID->AsInteger;
		deleteSQL->ExecSQL();

		delete deleteSQL;
	}
	catch( ... )
	{
		if( !inTransaction && llCheck_DB->InTransaction )
			llCheck_DB->Rollback();

		throw;
	}

	if( !inTransaction && llCheck_DB->InTransaction )
		llCheck_DB->Commit();
}
//---------------------------------------------------------------------------
void TtheDataModule::deleteOldEntries( void )
{
	if( DeleteDateForm->ShowModal() == mrOk )
	{
		bool inTransaction = llCheck_DB->InTransaction;

		if( !inTransaction && !llCheck_DB->InTransaction )
			theDataModule->llCheck_DB->StartTransaction();

		try
		{
			TQuery	*deleteSQL = new TQuery( NULL );
			deleteSQL->DatabaseName = "llCheck_DB";

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from chart_requests_per_day where DAY < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from chart_requests_per_hour where DAY < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from chart_web_requests_per_day where DAY < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from chart_web_requests_per_hour where DAY < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from HTTP_THREAD where REQUEST_DATE_TIME < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from LLTHREAD where REQUEST_DATE_TIME < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from LLTHREAD_SUMMARY_TABLE where REQUEST_DATE_TIME < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from WEB_LOGS where REQUEST_DATE_TIME < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			deleteSQL->SQL->Clear();
			deleteSQL->SQL->Add( "delete from WEB_SUMMARY_TABLE where REQUEST_DATE_TIME < :theDate" );
			deleteSQL->Params->Items[0]->AsDateTime = DeleteDateForm->DateTimePicker->Date;
			deleteSQL->ExecSQL();

			delete deleteSQL;
		}
		catch( ... )
		{
			if( !inTransaction && llCheck_DB->InTransaction )
				llCheck_DB->Rollback();

			throw;
		}

		if( !inTransaction && llCheck_DB->InTransaction )
			llCheck_DB->Commit();
	}
}
//---------------------------------------------------------------------------

void __fastcall TtheDataModule::webThreadTableCalcFields(TDataSet *)
{
	webThreadTableEXEC_SECS->AsFloat = webThreadTableEXEC_TIME->AsFloat / 1000.0; 	
}
//---------------------------------------------------------------------------

void __fastcall TtheDataModule::WebServerTableBeforeDelete(
      TDataSet *)
{
	bool inTransaction = llCheck_DB->InTransaction;

	if( !inTransaction && !llCheck_DB->InTransaction )
		theDataModule->llCheck_DB->StartTransaction();

	try
	{
		TQuery	*deleteSQL = new TQuery( NULL );
		deleteSQL->DatabaseName = "llCheck_DB";

		deleteSQL->SQL->Clear();
		deleteSQL->SQL->Add( "delete from chart_web_requests_per_day where SERVER = :theServer" );
		deleteSQL->Params->Items[0]->AsInteger = WebServerTableID->AsInteger;
		deleteSQL->ExecSQL();

		deleteSQL->SQL->Clear();
		deleteSQL->SQL->Add( "delete from chart_web_requests_per_hour where SERVER = :theServer" );
		deleteSQL->Params->Items[0]->AsInteger = WebServerTableID->AsInteger;
		deleteSQL->ExecSQL();

		deleteSQL->SQL->Clear();
		deleteSQL->SQL->Add( "delete from WEB_LOGS where SERVER = :theServer" );
		deleteSQL->Params->Items[0]->AsInteger = WebServerTableID->AsInteger;
		deleteSQL->ExecSQL();

		deleteSQL->SQL->Clear();
		deleteSQL->SQL->Add( "delete from WEB_SUMMARY_TABLE where SERVER = :theServer" );
		deleteSQL->Params->Items[0]->AsInteger = WebServerTableID->AsInteger;
		deleteSQL->ExecSQL();

		delete deleteSQL;
	}
	catch( ... )
	{
		if( !inTransaction && llCheck_DB->InTransaction )
			llCheck_DB->Rollback();

		throw;
	}

	if( !inTransaction && llCheck_DB->InTransaction )
		llCheck_DB->Commit();
}
//---------------------------------------------------------------------------


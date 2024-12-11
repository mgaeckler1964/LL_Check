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
#include <fstream>

#include <vcl.h>

#include <gak/csv.h>
#include <gak/numericString.h>

#pragma hdrstop

#include "DataUnit.h"
#include "llImportThrd.h"
#include "ImportStatus.h"

#pragma package(smart_init)

using namespace gak;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Unit1::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall llImportThread::llImportThread(
	bool CreateSuspended,
	bool ignoreErrors, bool summarize, int daysToKeep,
	ImportStatus *statusDisplay )
	: TThread(CreateSuspended)
{
	this->ignoreErrors = ignoreErrors;
	this->summarize = summarize;
	this->daysToKeep = daysToKeep;
	this->statusDisplay = statusDisplay;

	isRunning = true;
}
//---------------------------------------------------------------------------
bool llImportThread::CreateNewRecord(
	std::ifstream &csvFile,
	std::ofstream &errFile,
	ArrayOfStrings &csvLine )
{
	bool			errFlag = false;

	STRING			dateStr, timeStr, startTickStr, ThreadNoStr, UserName,
					ipAddress, FunctionAction, ExecTimeStr, SQLTimeStr,
					SQLCountStr, GenerateOutputTimeStr, ObjectIDStr,
					ParentIDStr, MiscArgs, error,
					reqSQLtimeStr, reqSQLtimeLogedStr, reqSQLcountStr,
					recFetchedStr, recChangedStr;
	FieldSet		record;

	TDateTime		dateTime;
	double			execTime, sqlTime, reqSQLtime, reqSQLtimeLoged;
	unsigned int	day, month, year, hour, minute, second;
	int				startTick, threadNo;
	int				sqlCount, reqSQLcount, recFetchCount, recChangedCount;
	double			generateOutputTime;
	int				objectId, parentId;

	readFIELD_SET( csvFile, csvLine, &record );
	if( !csvFile.eof() )
	{
		dateStr = record["Date"];
		timeStr = record["Time"];
		startTickStr = record["StartTick"];
		ThreadNoStr = record["Thread#"];
		UserName = record["User Name"];
		FunctionAction = record["Function.Action"];
		ExecTimeStr = record["Exec. Time"];
		SQLTimeStr = record["SQL Time"];
		SQLCountStr = record["SQL Count"];
		GenerateOutputTimeStr = record["GenerateOutput Time"];
		ObjectIDStr = record["Object ID"];
		ParentIDStr = record["Parent ID"];
		MiscArgs = record["Misc Args"];
		error  = record["error"];
		reqSQLtimeStr  = record["Req SQL Time"];
		reqSQLtimeLogedStr  = record["Req SQL Time Logged"];
		reqSQLcountStr  = record["Req SQL Count Logged"];
		recFetchedStr  = record["N Recs"];
		recChangedStr  = record["Req N Recs Logged"];

		try
		{
			execTime = ExecTimeStr.getValueN<double>();
			if( UserName != "?" || ExecTimeStr != "0.0" || execTime >= 0.001 )
			{
				sscanf( dateStr, "%u/%u/%u", &month, &day, &year );
				sscanf( timeStr, "%u:%u:%u", &hour, &minute, &second );
				dateTime = EncodeDate( (Word)year, (Word)month, (Word)day ) + EncodeTime( (Word)hour, (Word)minute, (Word)second, 0 );
				startTick = startTickStr.getValueN<unsigned>();
				threadNo = ThreadNoStr.getValueN<unsigned>();
				if( FunctionAction == "" )
					FunctionAction = "-";
				sqlTime = SQLTimeStr.getValueN<double>();
				sqlCount = SQLCountStr.getValueN<unsigned>();
				reqSQLcount = reqSQLcountStr.getValueN<unsigned>();
				generateOutputTime = GenerateOutputTimeStr.getValueN<double>();
				objectId = ObjectIDStr.getValueN<unsigned>();
				parentId = ParentIDStr.getValueN<unsigned>();
				reqSQLtime = reqSQLtimeStr.getValueN<double>();
				reqSQLtimeLoged = reqSQLtimeLogedStr.getValueN<double>();
				recFetchCount = recFetchedStr.getValueN<unsigned>();
				recChangedCount = recChangedStr.getValueN<unsigned>();

				if( execTime < 0 )
					throw Exception( "Exec Time less than 0" );
				if( sqlTime < 0 )
					throw Exception( "SQL Time less than 0" );
				if( generateOutputTime < 0 )
					throw Exception( "Output Time less than 0" );
				if( reqSQLtime < 0 )
					throw Exception( "Request SQL Time less than 0" );
				if( reqSQLtimeLoged < 0 )
					throw Exception( "Request SQL Time Loged less than 0" );

				theDataModule->llThreadTable->Insert();

				theDataModule->llThreadTableID->AsFloat = -1;	// for BDE error checking
				theDataModule->llThreadTableSERVER->AsFloat = theDataModule->ServerTableID->AsFloat;
				theDataModule->llThreadTableREQUEST_DATE_TIME->AsDateTime = dateTime;
				theDataModule->llThreadTableSTART_TICK->AsFloat = startTick;
				theDataModule->llThreadTableTHREAD->AsFloat = threadNo;
				theDataModule->llThreadTableFUNC->AsString = (const char*)FunctionAction;
				theDataModule->llThreadTableEXEC_TIME->AsFloat = execTime;
				theDataModule->llThreadTableSQL_TIME->AsFloat = sqlTime;
				theDataModule->llThreadTableSQL_COUNT->AsFloat = sqlCount;
				theDataModule->llThreadTableGENERATE_TIME->AsFloat = generateOutputTime;
				theDataModule->llThreadTableOBJECT_ID->AsFloat = objectId;
				theDataModule->llThreadTablePARENT_ID->AsFloat = parentId;
				theDataModule->llThreadTableMISRC_ARGS->AsString = (const char*)MiscArgs;
				theDataModule->llThreadTableERROR->AsString = (const char*)error;
				theDataModule->llThreadTableREQ_SQL_TIME->AsFloat = reqSQLtime;
				theDataModule->llThreadTableREQ_SQL_TIME_LOGED->AsFloat = reqSQLtimeLoged;
				theDataModule->llThreadTableREQ_SQL_COUNT->AsFloat = reqSQLcount;
				theDataModule->llThreadTableREC_FETCHED->AsFloat = recFetchCount;
				theDataModule->llThreadTableREC_CHANGED->AsFloat = recChangedCount;

				theDataModule->llThreadTable->Post();
			}
		}
		catch( Exception &e )
		{
			// ignore exception but log in error file
			errFile << dateStr << ',' << timeStr << ','
					<< startTickStr << ',' << ThreadNoStr
					<< ',' << UserName
					<< ',' << FunctionAction << ','
					<< ExecTimeStr << ',' << SQLTimeStr
					<< ',' << SQLCountStr << ','
					<< GenerateOutputTimeStr << ','
					<< ObjectIDStr << ',' << ParentIDStr
					<< ',' << MiscArgs << ',' << error
					<< ",\"" << e.Message.c_str() << "\"\n";

			theDataModule->llThreadTable->Cancel();
			errFlag = true;
		}
	}

	return errFlag;
}

//---------------------------------------------------------------------------
void __fastcall llImportThread::Execute()
{
	TSearchRec	  	csvSearch;
	AnsiString	  	logPath, fileName, errorFile,
					sqlCmd, message;

	bool		  	inTransaction = theDataModule->llCheck_DB->InTransaction;
	bool		  	errFlag;
	clock_t		  	startTicks = clock();

	int			  	records, errors;

	int			  	nameLength;
	ArrayOfStrings	csvLine;

	TQuery		  	*analyser;

	TTable *llThreadTable = theDataModule->llThreadTable;
	llThreadTable->Close();

	llThreadTable->Exclusive = true;
	llThreadTable->DisableControls();
	llThreadTable->Open();

	TTable *ServerTable = theDataModule->ServerTable;
	bool ServerTableActive = ServerTable->Active;
	ServerTable->DisableControls();
	ServerTable->Open();
	errors = records = 0;
	while( !ServerTable->Eof && !Terminated )
	{
		logPath = theDataModule->ServerTablePATH->AsString;
		logPath += '\\';
		fileName = logPath;
		fileName += "timings*.csv";

		statusDisplay->ShowServer( theDataModule->ServerTableSERVER_NAME->AsString );

		if( !FindFirst( fileName, faAnyFile, csvSearch ) ) do
		{
			fileName = csvSearch.Name;
			nameLength = fileName.Length();
			if( nameLength > 4 &&
				(
					fileName[nameLength-4] != '0' ||
					fileName[nameLength-5] != '_'
				) &&
				(
					!ignoreErrors ||
					fileName.AnsiPos( "errors.csv" ) == 0
				)
			)
			{
				fileName = logPath;
				fileName += csvSearch.Name;

				statusDisplay->ShowFile( csvSearch.Name );

				if( !inTransaction && !theDataModule->llCheck_DB->InTransaction )
				{
					theDataModule->llCheck_DB->StartTransaction();
				}
				try
				{
					bool	canErrorDelete = true;

					errorFile = fileName;
					errorFile += ".errors.csv";

					std::ofstream	errFile( errorFile.c_str() );
					std::ifstream	csvFile( fileName.c_str() );
					if( csvFile.is_open() && errFile.is_open() )
					{
						unsigned long	position, size;

						csvFile.seekg( 0, std::ios_base::end );
						size = (unsigned long)csvFile.tellg();
						csvFile.seekg( 0 );

						readCSVLine( csvFile, &csvLine );

						errFile << "Date,Time,StartTick,Thread#,User Name,Function.Action,"
							"Exec. Time,SQL Time,SQL Count,GenerateOutput Time,"
							"Object ID,Parent ID,Misc Args,error,import error\n";

						message = "importing";
						statusDisplay->ShowStatus( message );

						while( !Terminated )
						{
							errFlag = CreateNewRecord( csvFile, errFile, csvLine );
							if( csvFile.eof() )
								break;
							if( !errFlag )
								records++;
							else
							{
								errors++;
								canErrorDelete = false;
							}

							position = (unsigned long)csvFile.tellg();
							statusDisplay->ShowStatus(
								theDataModule->ServerTableSERVER_NAME->AsString.c_str(),
								csvSearch.Name.c_str(), position*100 / size,
								position, size,
								records,
								errors,
								"importing",
								startTicks
							);
						}	// while(  !Terminated )
						csvFile.close();
						errFile.close();

						statusDisplay->ShowStatus(
							theDataModule->ServerTableSERVER_NAME->AsString.c_str(),
							csvSearch.Name.c_str(), 100,
							0,0,
							records,
							errors,
							!Terminated ? "commiting" : "terminating (please wait)",
							startTicks
						);

						if( !inTransaction && theDataModule->llCheck_DB->InTransaction )
							if( !Terminated )
								theDataModule->llCheck_DB->Commit();
							else
								theDataModule->llCheck_DB->Rollback();

						if( !Terminated )
							remove(fileName.c_str());
						if( canErrorDelete || ignoreErrors )
							remove( errorFile.c_str() );
					}	// if( csvFile.is_open() )
				}	// try
				catch( Exception &e )
				{
					message = "Fatal Error: terminating ";
					message += e.Message;

					statusDisplay->ShowStatus( message );

					if( !inTransaction && theDataModule->llCheck_DB->InTransaction )
						theDataModule->llCheck_DB->Rollback();

					message = "Fatal Error: terminated ";
					message += e.Message;
					statusDisplay->ShowStatus( message );

					isRunning = false;

					throw;
				}
				catch( ... )
				{
					message = "Fatal Error: terminating (please wait)";

					statusDisplay->ShowStatus( message );

					if( !inTransaction && theDataModule->llCheck_DB->InTransaction )
						theDataModule->llCheck_DB->Rollback();

					message = "Fatal Error: terminated  (any error)";
					statusDisplay->ShowStatus( message );

					isRunning = false;

					throw;
				}
			}	// if( nameLength > 4 && ...

		} while( !FindNext( csvSearch )  && !Terminated );

		if( summarize && !Terminated )
		{
			statusDisplay->ShowStatus(
				theDataModule->ServerTableSERVER_NAME->AsString.c_str(),
				"-", 0,0,0,
				records,
				errors,
				"summarizing",
				startTicks
			);

			try
			{
				theDataModule->SummarizeServer->ParamByName( "DaysToKeep" )->AsInteger = daysToKeep;
				theDataModule->SummarizeServer->ParamByName( "theServer" )->AsInteger = theDataModule->ServerTableID->AsInteger;
				theDataModule->SummarizeServer->ExecProc();
			}
			catch( Exception &e )
			{
				message = "Fatal Error: terminated ";
				message += e.Message;
				statusDisplay->ShowStatus( message );

				isRunning = false;
				throw;
			}
		}
		ServerTable->Next();
	}	// while( !ServerTable->Eof && !Terminated )
	ServerTable->Close();
	ServerTable->EnableControls();
	if( ServerTableActive )
		ServerTable->Open();

	llThreadTable->Close();
	llThreadTable->EnableControls();
	llThreadTable->Exclusive = false;

	statusDisplay->ShowServer( "Oracle DB" );
	statusDisplay->ShowStatus(
		"-", "-",
		0, 0, 0,
		records, errors,
		"Updating functions table (please wait)",
		startTicks
	);
	if( records > 0  && !Terminated )
	{
		try
		{
			theDataModule->updateLLFunctionsTable();
		}
		catch( Exception &e )
		{
			message = "Fatal Error: terminated ";
			message += e.Message;
			statusDisplay->ShowStatus( message );

			isRunning = false;
			throw;
		}
	}

	analyser = new TQuery( NULL );
	if( analyser )
	{
		analyser->DatabaseName = "llCheck_DB";

		theDataModule->llAnalyzerTables->Open();
		while( !theDataModule->llAnalyzerTables->Eof && !Terminated )
		{
			message = "Analysing ";
			message += theDataModule->llAnalyzerTablesTYPE->AsString;
			message += ' ';
			message += theDataModule->llAnalyzerTablesOBJECT_NAME->AsString;

			statusDisplay->ShowStatus( message );

			sqlCmd = "analyze ";
			sqlCmd +=  theDataModule->llAnalyzerTablesTYPE->AsString;
			sqlCmd += ' ';
			sqlCmd +=  theDataModule->llAnalyzerTablesOBJECT_NAME->AsString;
			sqlCmd += " compute statistics";
			analyser->SQL->Clear();
			analyser->SQL->Add( sqlCmd );
			analyser->ExecSQL();

			theDataModule->llAnalyzerTables->Next();
		}
		theDataModule->llAnalyzerTables->Close();

		if( !Terminated )
		{
			message = "Precalc charts";
			statusDisplay->ShowStatus( message );

			theDataModule->calcLLChart->ExecProc();
		}

		theDataModule->llAnalyserCharts->Open();
		while( !theDataModule->llAnalyserCharts->Eof && !Terminated )
		{
			message = "Analysing ";
			message += theDataModule->llAnalyserChartsTYPE->AsString;
			message += ' ';
			message += theDataModule->llAnalyserChartsOBJECT_NAME->AsString;

			statusDisplay->ShowStatus( message );

			sqlCmd = "analyze ";
			sqlCmd +=  theDataModule->llAnalyserChartsTYPE->AsString;
			sqlCmd += ' ';
			sqlCmd +=  theDataModule->llAnalyserChartsOBJECT_NAME->AsString;
			sqlCmd += " compute statistics";
			analyser->SQL->Clear();
			analyser->SQL->Add( sqlCmd );
			analyser->ExecSQL();

			theDataModule->llAnalyserCharts->Next();
		}
		theDataModule->llAnalyserCharts->Close();
	}
	statusDisplay->ShowStatus( "Finish" );

	llThreadTable->Open();

	isRunning = false;
}
//---------------------------------------------------------------------------

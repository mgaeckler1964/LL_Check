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

#include <gak/ci_string.h>
#include <gak/array.h>
#include <gak/numericString.h>

#pragma hdrstop

#include "DataUnit.h"
#include "webImportThrd.h"
#include "ImportStatus.h"

using namespace gak;

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

#define	LOG_DATE_FIELD			0
#define	LOG_TIME_FIELD			1
#define LOG_METHOD_FIELD		2
#define LOG_URL_FIELD			3
#define LOG_QUERY_FIELD			4
#define LOG_COOKIES_FIELD		5
#define LOG_AGENT_FIELD			6
#define LOG_STATUS_FIELD		7
#define LOG_SUB_STATUS_FIELD	8
#define LOG_WIN_STATUS_FIELD	9
#define LOG_SENT_FIELD			10
#define LOG_RECEIVED_FIELD		11
#define LOG_EXEC_TIME_FIELD		12

#define LOG_NUM_FIELDS			13




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

__fastcall webImportThread::webImportThread(
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
void webImportThread::initFieldDefinition( size_t *fieldDefs )
{
	for( size_t i=0; i<LOG_NUM_FIELDS; i++ )
		fieldDefs[i] = -1;
}
//---------------------------------------------------------------------------
size_t webImportThread::readFieldDefinition( STRING &logLine, size_t *fieldDefs )
{
	size_t numFields;

	if( logLine.beginsWithI( "#Fields: " ) )
	{
		ArrayOfStrings	fieldNames;

		logLine += (size_t)9;

		fieldNames.createElements( logLine, " " );
		initFieldDefinition( fieldDefs );

		for( size_t i=0; i<fieldNames.size(); i++ )
		{
			CI_STRING	fieldName = fieldNames[i];
			if( fieldName == "date" )
				fieldDefs[LOG_DATE_FIELD] = i;
			else if( fieldName == "time" )
				fieldDefs[LOG_TIME_FIELD] = i;
			else if( fieldName == "cs-method" )
				fieldDefs[LOG_METHOD_FIELD] = i;
			else if( fieldName == "cs-uri-stem" )
				fieldDefs[LOG_URL_FIELD] = i;
			else if( fieldName == "cs-uri-query" )
				fieldDefs[LOG_QUERY_FIELD] = i;
			else if( fieldName == "cs(Cookie)" )
				fieldDefs[LOG_COOKIES_FIELD] = i;
			else if( fieldName == "cs(User-Agent)" )
				fieldDefs[LOG_AGENT_FIELD] = i;
			else if( fieldName == "sc-status" )
				fieldDefs[LOG_STATUS_FIELD] = i;
			else if( fieldName == "sc-substatus" )
				fieldDefs[LOG_SUB_STATUS_FIELD] = i;
			else if( fieldName == "sc-win32-status" )
				fieldDefs[LOG_WIN_STATUS_FIELD] = i;
			else if( fieldName == "sc-bytes" )
				fieldDefs[LOG_SENT_FIELD] = i;
			else if( fieldName == "cs-bytes" )
				fieldDefs[LOG_RECEIVED_FIELD] = i;
			else if( fieldName == "time-taken" )
				fieldDefs[LOG_EXEC_TIME_FIELD] = i;
		}
	}

	numFields=0;
	for( size_t i=0; i<LOG_NUM_FIELDS; i++ )
		if( fieldDefs[i] != -1 )
			numFields++;

	return numFields;
}
//---------------------------------------------------------------------------
bool webImportThread::CreateNewRecord(
	STRING &logLine, std::ofstream &errFile, const size_t *fieldDefs
)
{
	bool		  	errFlag = false;

	STRING		  	dateStr, timeStr, methodStr, urlStr, queryStr, cookiesStr,
					agentStr, statusStr, subStatusStr, winStatusStr, sentStr,
					receivedStr, execTimeStr;
	ArrayOfStrings	record;

	TDateTime	  	dateTime;
	unsigned long 	execTime, bytesSent, bytesReceived;
	unsigned int  	day, month, year, hour, minute, second;
	int			  	status, subStatus, winStatus;

	record.createElements( logLine, " " );

	if( fieldDefs[LOG_DATE_FIELD] != -1 )
		dateStr = record[fieldDefs[LOG_DATE_FIELD]];
	if( fieldDefs[LOG_TIME_FIELD] != -1 )
		timeStr = record[fieldDefs[LOG_TIME_FIELD]];
	if( fieldDefs[LOG_METHOD_FIELD] != -1 )
		methodStr = record[fieldDefs[LOG_METHOD_FIELD]];
	if( fieldDefs[LOG_URL_FIELD] != -1 )
		urlStr = record[fieldDefs[LOG_URL_FIELD]];
	if( fieldDefs[LOG_QUERY_FIELD] != -1 )
		queryStr = record[fieldDefs[LOG_QUERY_FIELD]];
	if( fieldDefs[LOG_COOKIES_FIELD] != -1 )
		cookiesStr = record[fieldDefs[LOG_COOKIES_FIELD]];
	if( fieldDefs[LOG_AGENT_FIELD] != -1 )
		agentStr = record[fieldDefs[LOG_AGENT_FIELD]];
	if( fieldDefs[LOG_STATUS_FIELD] != -1 )
		statusStr = record[fieldDefs[LOG_STATUS_FIELD]];
	if( fieldDefs[LOG_SUB_STATUS_FIELD] != -1 )
		subStatusStr = record[fieldDefs[LOG_SUB_STATUS_FIELD]];
	if( fieldDefs[LOG_WIN_STATUS_FIELD] != -1 )
		winStatusStr = record[fieldDefs[LOG_WIN_STATUS_FIELD]];
	if( fieldDefs[LOG_SENT_FIELD] != -1 )
		sentStr = record[fieldDefs[LOG_SENT_FIELD]];
	if( fieldDefs[LOG_RECEIVED_FIELD] != -1 )
		receivedStr = record[fieldDefs[LOG_RECEIVED_FIELD]];
	if( fieldDefs[LOG_EXEC_TIME_FIELD] != -1 )
		execTimeStr = record[fieldDefs[LOG_EXEC_TIME_FIELD]];

	try
	{
		sscanf( dateStr, "%u-%u-%u", &year, &month, &day );
		sscanf( timeStr, "%u:%u:%u", &hour, &minute, &second );
		dateTime = EncodeDate( (Word)year, (Word)month, (Word)day ) + EncodeTime( (Word)hour, (Word)minute, (Word)second, 0 );

		status = statusStr.getValueN<unsigned>();
		subStatus = subStatusStr.getValueN<unsigned>();
		winStatus = winStatusStr.getValueN<unsigned>();
		bytesSent = sentStr.getValueN<unsigned>();
		bytesReceived = receivedStr.getValueN<unsigned>();
		execTime = execTimeStr.getValueN<unsigned>();


		theDataModule->webThreadTable->Insert();

		theDataModule->webThreadTableID->AsFloat = -1;	// for BDE error checking
		theDataModule->webThreadTableSERVER->AsFloat = theDataModule->WebServerTableID->AsFloat;
		theDataModule->webThreadTableREQUEST_DATE_TIME->AsDateTime = dateTime;
		theDataModule->webThreadTableHTTP_METHOD->AsString = (const char*)methodStr;
		theDataModule->webThreadTableHTTP_URL->AsString = (const char*)urlStr.cut( 255 );
		theDataModule->webThreadTableHTTP_QUERY->AsString = (const char*)queryStr.cut( 255 );
		theDataModule->webThreadTableHTTP_COOKIES->AsString = (const char*)cookiesStr.cut( 255 );
		theDataModule->webThreadTableHTTP_AGENT->AsString = (const char*)agentStr.cut( 255 );

		theDataModule->webThreadTableHTTP_STATUS->AsInteger = status;
		theDataModule->webThreadTableHTTP_SUB_STATUS->AsInteger = subStatus;
		theDataModule->webThreadTableHTTP_WIN_STATUS->AsInteger = winStatus;

		theDataModule->webThreadTableBYTES_RECEIVED->AsInteger = bytesReceived;
		theDataModule->webThreadTableBYTES_SENT->AsInteger = bytesSent;

		theDataModule->webThreadTableEXEC_TIME->AsInteger = execTime;


		theDataModule->webThreadTable->Post();
	}
	catch( Exception &e )
	{
		// ignore exception but log in error file
		errFile << logLine
				<< " \"" << e.Message.c_str() << "\"\n";

		theDataModule->webThreadTable->Cancel();
		errFlag = true;
	}

	return errFlag;
}

//---------------------------------------------------------------------------
void __fastcall webImportThread::Execute()
{
	size_t				fieldDefs[LOG_NUM_FIELDS], numFields;

	TSearchRec			logSearch;
	AnsiString			logPath, fileName, errorFile, tmpFile,
						sqlCmd, message;

	bool				inTransaction = theDataModule->llCheck_DB->InTransaction;
	bool				errFlag;
	clock_t				startTicks = clock();

	int					records, errors;

	STRING				logLine;

	TQuery				*analyser;

	TTable *webThreadTable = theDataModule->webThreadTable;
	webThreadTable->Close();

	webThreadTable->Exclusive = true;
	webThreadTable->DisableControls();
	webThreadTable->Open();

	TTable *WebServerTable = theDataModule->WebServerTable;
	bool webServerTableActive = WebServerTable->Active;
	WebServerTable->DisableControls();
	WebServerTable->Open();
	errors = records = 0;

	while( !WebServerTable->Eof && !Terminated )
	{
		logPath = theDataModule->WebServerTablePATH->AsString;
		logPath += '\\';
		fileName = logPath;
		fileName += "*.log";

		statusDisplay->ShowServer( theDataModule->WebServerTableSERVER_NAME->AsString );

		if( !FindFirst( fileName, faAnyFile, logSearch ) ) do
		{
			fileName = logPath;
			fileName += logSearch.Name;

			statusDisplay->ShowFile( logSearch.Name );

			if( !inTransaction && !theDataModule->llCheck_DB->InTransaction )
				theDataModule->llCheck_DB->StartTransaction();

			try
			{
				bool	canErrorDelete = true;

				errorFile = fileName;
				errorFile += ".errors.csv";

				tmpFile = fileName;
				tmpFile += ".tmp";

				rename( fileName.c_str(), tmpFile.c_str() );

				std::ofstream	errFile( errorFile.c_str() );
				std::ifstream	logFile( tmpFile.c_str() );
				if( logFile.is_open() && errFile.is_open() )
				{
					unsigned long	position, size;

					logFile.seekg( 0, std::ios_base::end );
					size = (unsigned long)logFile.tellg();
					logFile.seekg( 0 );

					errFile << "Date,Time,StartTick,Thread#,User Name,Function.Action,"
						"Exec. Time,SQL Time,SQL Count,GenerateOutput Time,"
						"Object ID,Parent ID,Misc Args,error,import error\n";

					message = "importing";
					statusDisplay->ShowStatus( message );

					initFieldDefinition( fieldDefs );
					numFields = 0;

					while( !Terminated )
					{
						logFile >> logLine;
						if( logFile.eof() )
							break;
						if( logLine[0] == '#' )
							numFields = readFieldDefinition( logLine, fieldDefs );
						else if( numFields )
						{
							errFlag = CreateNewRecord( logLine, errFile, fieldDefs );
							if( !errFlag )
								records++;
							else
							{
								errors++;
								canErrorDelete = false;
							}

							position = (unsigned long)logFile.tellg();
							statusDisplay->ShowStatus(
								theDataModule->WebServerTableSERVER_NAME->AsString.c_str(),
								logSearch.Name.c_str(), position*100 / size,
								position, size,
								records,
								errors,
								"importing",
								startTicks
							);
						}

						if( logFile.eof() )
							break;
					}	// while(  !Terminated )
					logFile.close();

					statusDisplay->ShowStatus(
						theDataModule->WebServerTableSERVER_NAME->AsString.c_str(),
						logSearch.Name.c_str(), 100,
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

					if( !Terminated && numFields )
						remove(tmpFile.c_str());
				}	// if( logFile.is_open() )
				if( logFile.is_open() )
					logFile.close();
				if( errFile.is_open() )
					errFile.close();
				if( canErrorDelete || ignoreErrors )
					remove( errorFile.c_str() );
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

		} while( !FindNext( logSearch )  && !Terminated );

		if( summarize && !Terminated )
		{
			statusDisplay->ShowStatus(
				theDataModule->WebServerTableSERVER_NAME->AsString.c_str(),
				"-", 0,0,0,
				records,
				errors,
				"summarizing",
				startTicks
			);

			try
			{
				theDataModule->WebSummarizeServer->ParamByName( "DaysToKeep" )->AsInteger = daysToKeep;
				theDataModule->WebSummarizeServer->ParamByName( "theServer" )->AsInteger = theDataModule->WebServerTableID->AsInteger;
				theDataModule->WebSummarizeServer->ExecProc();
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
		WebServerTable->Next();
	}	// while( !WebServerTable->Eof && !Terminated )
	WebServerTable->Close();
	WebServerTable->EnableControls();
	if( webServerTableActive )
		WebServerTable->Open();

	webThreadTable->Close();
	webThreadTable->EnableControls();
	webThreadTable->Exclusive = false;

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
			theDataModule->updateWebFunctionsTable();
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

		theDataModule->webAnalyzerTables->Open();
		while( !theDataModule->webAnalyzerTables->Eof && !Terminated )
		{
			message = "Analysing ";
			message += theDataModule->webAnalyzerTablesTYPE->AsString;
			message += ' ';
			message += theDataModule->webAnalyzerTablesOBJECT_NAME->AsString;

			statusDisplay->ShowStatus( message );

			sqlCmd = "analyze ";
			sqlCmd +=  theDataModule->webAnalyzerTablesTYPE->AsString;
			sqlCmd += ' ';
			sqlCmd +=  theDataModule->webAnalyzerTablesOBJECT_NAME->AsString;
			sqlCmd += " compute statistics";
			analyser->SQL->Clear();
			analyser->SQL->Add( sqlCmd );
			analyser->ExecSQL();

			theDataModule->webAnalyzerTables->Next();
		}
		theDataModule->webAnalyzerTables->Close();

		if( !Terminated )
		{
			message = "Precalc charts";
			statusDisplay->ShowStatus( message );

			theDataModule->calcWebChart->ExecProc();
		}

		theDataModule->webAnalyserCharts->Open();
		while( !theDataModule->webAnalyserCharts->Eof && !Terminated )
		{
			message = "Analysing ";
			message += theDataModule->webAnalyserChartsTYPE->AsString;
			message += ' ';
			message += theDataModule->webAnalyserChartsOBJECT_NAME->AsString;

			statusDisplay->ShowStatus( message );

			sqlCmd = "analyze ";
			sqlCmd +=  theDataModule->webAnalyserChartsTYPE->AsString;
			sqlCmd += ' ';
			sqlCmd +=  theDataModule->webAnalyserChartsOBJECT_NAME->AsString;
			sqlCmd += " compute statistics";
			analyser->SQL->Clear();
			analyser->SQL->Add( sqlCmd );
			analyser->ExecSQL();

			theDataModule->webAnalyserCharts->Next();
		}
		theDataModule->webAnalyserCharts->Close();
	}
	statusDisplay->ShowStatus( "Finish" );

	isRunning = false;
}
//---------------------------------------------------------------------------

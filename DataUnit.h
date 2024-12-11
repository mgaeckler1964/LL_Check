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

#ifndef DataUnitH
#define DataUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TtheDataModule : public TDataModule
{
__published:	// IDE-managed Components
	TTable *ServerTable;
	TTable *llThreadTable;
	TFloatField *llThreadTableID;
	TFloatField *llThreadTableSERVER;
	TDateTimeField *llThreadTableREQUEST_DATE_TIME;
	TFloatField *llThreadTableSTART_TICK;
	TFloatField *llThreadTableTHREAD;
	TStringField *llThreadTableFUNC;
	TFloatField *llThreadTableEXEC_TIME;
	TFloatField *llThreadTableSQL_TIME;
	TFloatField *llThreadTableSQL_COUNT;
	TFloatField *llThreadTableGENERATE_TIME;
	TFloatField *llThreadTableOBJECT_ID;
	TFloatField *llThreadTablePARENT_ID;
	TStringField *llThreadTableMISRC_ARGS;
	TStringField *llThreadTableERROR;
	TFloatField *ServerTableID;
	TStringField *ServerTableSERVER_NAME;
	TMemoField *ServerTablePATH;
	TTable *HttpTable;
	TFloatField *HttpTableID;
	TMemoField *HttpTableHTTP_URL;
	TMemoField *HttpTableHTTP_COOKIES;
	TDateTimeField *HttpTableREQUEST_DATE_TIME;
	TFloatField *HttpTableLOOP_COUNT;
	TFloatField *HttpTableUSER_COUNT;
	TFloatField *HttpTableAVG_TIME;
	TDatabase *llCheck_DB;
	TTable *llFunctionsTable;
	TQuery *updateLLFunctionsQuery;
	TStoredProc *SummarizeServer;
	TQuery *llAnalyzerTables;
	TStringField *llAnalyzerTablesTYPE;
	TStringField *llAnalyzerTablesOBJECT_NAME;
	TStoredProc *calcLLChart;
	TQuery *llAnalyserCharts;
	TStringField *llAnalyserChartsTYPE;
	TStringField *llAnalyserChartsOBJECT_NAME;
	TStringField *HttpTablePROXY_SERVER;
	TFloatField *HttpTablePROXY_PORT;
	TStringField *HttpTableCOMPLETE_FLAG;
	TStringField *HttpTableLINK_CHECK;
	TFloatField *HttpTableTOTAL_SIZE;
	TFloatField *HttpTableNUM_FILES;
	TFloatField *HttpTableMAX_FILES;
	TFloatField *llThreadTableREQ_SQL_TIME;
	TFloatField *llThreadTableREQ_SQL_TIME_LOGED;
	TFloatField *llThreadTableREQ_SQL_COUNT;
	TFloatField *llThreadTableREC_FETCHED;
	TFloatField *llThreadTableREC_CHANGED;
	TTable *WebServerTable;
	TFloatField *WebServerTableID;
	TStringField *WebServerTableSERVER_NAME;
	TMemoField *WebServerTablePATH;
	TTable *webThreadTable;
	TFloatField *webThreadTableID;
	TFloatField *webThreadTableSERVER;
	TDateTimeField *webThreadTableREQUEST_DATE_TIME;
	TStringField *webThreadTableHTTP_METHOD;
	TFloatField *webThreadTableHTTP_STATUS;
	TFloatField *webThreadTableHTTP_SUB_STATUS;
	TFloatField *webThreadTableHTTP_WIN_STATUS;
	TFloatField *webThreadTableBYTES_RECEIVED;
	TFloatField *webThreadTableBYTES_SENT;
	TFloatField *webThreadTableEXEC_TIME;
	TStringField *webThreadTableHTTP_URL;
	TStringField *webThreadTableHTTP_QUERY;
	TStringField *webThreadTableHTTP_COOKIES;
	TStringField *webThreadTableHTTP_AGENT;
	TFloatField *webThreadTableEXEC_SECS;
	TStoredProc *WebSummarizeServer;
	TTable *webFunctionsTable;
	TStringField *llFunctionsTableFUNC;
	TFloatField *llFunctionsTableOBJECT_ID;
	TStringField *webFunctionsTableHTTP_URL;
	TStringField *webFunctionsTableHTTP_QUERY;
	TQuery *updateWebFunctionsQuery;
	TStoredProc *calcWebChart;
	TQuery *webAnalyzerTables;
	TStringField *webAnalyzerTablesTYPE;
	TStringField *webAnalyzerTablesOBJECT_NAME;
	TQuery *webAnalyserCharts;
	TStringField *webAnalyserChartsTYPE;
	TStringField *webAnalyserChartsOBJECT_NAME;
	TStringField *webThreadTableSERVER_NAME;
	TTable *webSummarizeTable;
	TFloatField *webSummarizeTableSERVER;
	TDateTimeField *webSummarizeTableREQUEST_DATE_TIME;
	TFloatField *webSummarizeTableHOUR;
	TStringField *webSummarizeTableHTTP_URL;
	TStringField *webSummarizeTableHTTP_QUERY;
	TFloatField *webSummarizeTableEXEC_TIME;
	TFloatField *webSummarizeTableNUM_REQUESTS;
	TStringField *webSummarizeTableSERVER_NAME;
	TStringField *llThreadTableSERVER_NAME;
	TTable *llSummarizeTable;
	TFloatField *llSummarizeTableSERVER;
	TDateTimeField *llSummarizeTableREQUEST_DATE_TIME;
	TFloatField *llSummarizeTableHOUR;
	TStringField *llSummarizeTableFUNC;
	TFloatField *llSummarizeTableOBJECT_ID;
	TFloatField *llSummarizeTableEXEC_TIME;
	TFloatField *llSummarizeTableSQL_TIME;
	TFloatField *llSummarizeTableREQ_SQL_TIME;
	TFloatField *llSummarizeTableREQ_SQL_TIME_LOGED;
	TFloatField *llSummarizeTableREQ_SQL_COUNT;
	TFloatField *llSummarizeTableREC_FETCHED;
	TFloatField *llSummarizeTableREC_CHANGED;
	TFloatField *llSummarizeTableNUM_REQUESTS;
	TFloatField *llSummarizeTableGENERATE_TIME;
	TStringField *llSummarizeTableSERVER_NAME;
	void __fastcall ServerTableBeforeDelete(TDataSet *DataSet);
	void __fastcall webThreadTableCalcFields(TDataSet *DataSet);
	void __fastcall WebServerTableBeforeDelete(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TtheDataModule(TComponent* Owner);
	void updateLLFunctionsTable( void );
	void updateWebFunctionsTable( void );
	void openDatabase( const char *appName );
	void deleteOldEntries( void );
};
//---------------------------------------------------------------------------
extern PACKAGE TtheDataModule *theDataModule;
//---------------------------------------------------------------------------
#endif

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

#ifndef HttpRecurringFrmH
#define HttpRecurringFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class THttpRecurringForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBNavigator *DBNavigator;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TTable *TableHttpRecurring;
	TDataSource *DataSourceHttpRecurring;
	TMemoField *TableHttpRecurringHTTP_URL;
	TMemoField *TableHttpRecurringHTTP_COOKIES;
	TStringField *TableHttpRecurringPROXY_SERVER;
	TFloatField *TableHttpRecurringPROXY_PORT;
	TFloatField *TableHttpRecurringINTERVAL;
	TDateTimeField *TableHttpRecurringNEXT_START;
	TDBEdit *DBEditProxy;
	TLabel *Label4;
	TDBEdit *DBEditProxyPort;
	TDBGrid *DBGrid;
	TStringField *TableHttpRecurringSHORT_URL;
	TDBMemo *DBMemoUrl;
	TDBMemo *DBMemoCookies;
	TDBRadioGroup *DBRadioGroupInterval;
	TFloatField *TableHttpRecurringMAX_TIME;
	TStringField *TableHttpRecurringE_MAIL_ALERT;
	TStringField *TableHttpRecurringSMTP_SERVER;
	TFloatField *TableHttpRecurringSMTP_PORT;
	TLabel *Label5;
	TLabel *Label6;
	TDBEdit *DBEditSmtp;
	TLabel *Label7;
	TDBEdit *DBEditSmtpPort;
	TDBEdit *DBEditEmail;
	TLabel *Label8;
	TDBEdit *DBEditMaxTime;
	TFloatField *TableHttpRecurringLAST_TIME;
	TFloatField *TableHttpRecurringLAST_STATUS;
	TStringField *TableHttpRecurringSMTP_USER;
	TLabel *Label9;
	TDBEdit *DBEditSMTP_USER;
	TFloatField *TableHttpRecurringID;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TableHttpRecurringCalcFields(TDataSet *DataSet);
	void __fastcall DBGridDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, TGridDrawState State);
private:	// User declarations
public:		// User declarations
	__fastcall THttpRecurringForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THttpRecurringForm *HttpRecurringForm;
//---------------------------------------------------------------------------
#endif

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

#ifndef httpTimesFrmH
#define httpTimesFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class ThttpTimesForm : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TPanel *Panel1;
	TDataSource *DataSource;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGridTimes;
	TQuery *httpTimesQuery;
	TDateTimeField *httpTimesQueryREQUEST_DATE_TIME;
	TStringField *httpTimesQueryURL;
	TStringField *httpTimesQueryCOOKIES;
	TFloatField *httpTimesQueryLOOP_COUNT;
	TFloatField *httpTimesQueryUSER_COUNT;
	TFloatField *httpTimesQueryAVG_TIME;
	TButton *RefreshButton;
	TStringField *httpTimesQueryPROXY_SERVER;
	TFloatField *httpTimesQueryPROXY_PORT;
	TStringField *httpTimesQueryCOMPLETE_FLAG;
	TFloatField *httpTimesQueryTOTAL_SIZE;
	TFloatField *httpTimesQueryNUM_FILES;
	TFloatField *httpTimesQueryID;
	TQuery *delUrlQuery;
	TMemoField *httpTimesQueryHTTP_URL;
	TButton *ButtonDelUrl;
	TRadioButton *RadioButtonSortURL;
	TRadioButton *RadioButtonSortDate;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RefreshButtonClick(TObject *Sender);
	void __fastcall DBGridTimesDblClick(TObject *Sender);
	void __fastcall ButtonDelUrlClick(TObject *Sender);
	void __fastcall ChangeSort(TObject *Sender);
private:	// Anwender-Deklarationen
public:		// Anwender-Deklarationen
	__fastcall ThttpTimesForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE ThttpTimesForm *httpTimesForm;
//---------------------------------------------------------------------------
#endif

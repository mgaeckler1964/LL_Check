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

#ifndef llExportFrmH
#define llExportFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TllExportForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *PathEdit;
	TLabel *Label2;
	TListBox *ServerListBox;
	TButton *StartStopButton;
	TButton *CancelCloseButton;
	TQuery *ServerQuery;
	TQuery *TimingsQuery;
	TDateTimeField *TimingsQueryREQUEST_DATE_TIME;
	TFloatField *TimingsQuerySTART_TICK;
	TFloatField *TimingsQueryTHREAD;
	TStringField *TimingsQueryFUNC;
	TFloatField *TimingsQueryEXEC_TIME;
	TFloatField *TimingsQuerySQL_TIME;
	TFloatField *TimingsQuerySQL_COUNT;
	TFloatField *TimingsQueryGENERATE_TIME;
	TFloatField *TimingsQueryOBJECT_ID;
	TFloatField *TimingsQueryPARENT_ID;
	TStringField *TimingsQueryMISRC_ARGS;
	TStringField *TimingsQueryERROR;
	TStringField *TimingsQuerySERVER_NAME;
	TQuery *CountQuery;
	TFloatField *CountQueryCOUNTER;
	TProgressBar *ProgressBar;
	TLabel *StatusLabel;
	TTimer *threadTimer;
	void __fastcall CancelCloseButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall EnableDisableOK(TObject *Sender);
	void __fastcall StartStopButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall threadTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TllExportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TllExportForm *llExportForm;
//---------------------------------------------------------------------------
#endif

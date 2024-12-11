/*
		Project:		LL_Check
		Module:			
		Description:	
		Author:			Martin G�ckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2024 Martin G�ckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin G�ckler, Austria, Linz ``AS IS''
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

#ifndef llImportFrmH
#define llImportFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "llImportThrd.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TllImportForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *FileLabel;
	TLabel *Label3;
	TLabel *RequestsLabel;
	TButton *CancelCloseButton;
	TButton *StartStopButton;
	TLabel *Label5;
	TLabel *ServerLabel;
	TLabel *Label2;
	TLabel *errorLabel;
	TLabel *StatusLabel;
	TLabel *Label7;
	TLabel *Label4;
	TLabel *TimeLabel;
	TCheckBox *summarizeCheckBox;
	TLabel *Label6;
	TEdit *DaysToKeepEdit;
	TUpDown *DaysToKeep;
	TTimer *threadTimer;
	TCheckBox *CheckBoxIgnoreErrors;
	void __fastcall StartStopButtonClick(TObject *Sender);
	void __fastcall CancelCloseButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall threadTimerTimer(TObject *Sender);
private:	// User declarations
	llImportThread	*theThread;
public:		// User declarations
	__fastcall TllImportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TllImportForm *llImportForm;
//---------------------------------------------------------------------------
#endif

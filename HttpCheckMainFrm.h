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
#ifndef HttpCheckMainFrmH
#define HttpCheckMainFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBTables.hpp>
#include <Menus.hpp>
#include <Db.hpp>
//---------------------------------------------------------------------------
class THttpCheckMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *File1;
	TMenuItem *Exit1;
	TMenuItem *View1;
	TMenuItem *HTTP1;
	TMenuItem *Windows1;
	TMenuItem *ArrangeVertical1;
	TMenuItem *ArrangeHorizontal1;
	TMenuItem *N3;
	TMenuItem *HTTPTimes;
	TMenuItem *HTTPCharts;
	TMenuItem *Cascade1;
	TMenuItem *Info1;
	TMenuItem *HTTPAutochecks;
	TMenuItem *N1;
	TMenuItem *WebTests;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall HTTP1Click(TObject *Sender);
	void __fastcall HTTPTimesClick(TObject *Sender);
	void __fastcall HTTPChartsClick(TObject *Sender);
	void __fastcall ArrangeVertical1Click(TObject *Sender);
	void __fastcall ArrangeHorizontal1Click(TObject *Sender);
	void __fastcall Cascade1Click(TObject *Sender);
	void __fastcall Info1Click(TObject *Sender);
	void __fastcall HTTPAutochecksClick(TObject *Sender);
	void __fastcall WebTestsClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall THttpCheckMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THttpCheckMainForm *HttpCheckMainForm;
//---------------------------------------------------------------------------
#endif

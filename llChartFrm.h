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
#ifndef llChartFrmH
#define llChartFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>

#include <gak/array.h>

//---------------------------------------------------------------------------
class TLLChartForm : public TForm
{
__published:	// IDE-managed Components
	TChart *theChart;
	TPanel *PanelControl;
	TQuery *funcQuery;
	TDateTimePicker *theDatePicker;
	TComboBox *ModeComboBox;
	TComboBox *serverComboBox;
	TQuery *serverQuery;
	TButton *CalcButton;
	TUpDown *roundUpDown;
	TEdit *roundEdit;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *ServerLabel;
	TLabel *funcLabel;
	TLabel *RoundLabel;
	TDateTimePicker *endDatePicker;
	TDBEdit *funcDBEdit;
	TDataSource *funcSource;
	TButton *SelectRequestButton;
	TLabel *LabelMinRequests;
	TEdit *EditMinRequests;
	TUpDown *UpDownMinRequests;
	TPanel *PanelSizer;
	TScrollBar *ScrollBar;
	TTrackBar *TrackBar;
	TCheckBox *CheckBoxSizer;
	TCheckBox *CheckBoxLegend;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CalcButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ModeComboBoxChange(TObject *Sender);
	void __fastcall SelectRequestButtonClick(TObject *Sender);
	void __fastcall TrackBarChange(TObject *Sender);
	void __fastcall ScrollBarChange(TObject *Sender);
	void __fastcall CheckBoxSizerClick(TObject *Sender);
	void __fastcall CheckBoxLegendClick(TObject *Sender);
private:	// User declarations
	void reloadData( void );
	void enableDisableControls( void );
	bool ignoreObjId;
	gak::Array<TLineSeries*> series;
public:		// User declarations
	__fastcall TLLChartForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLLChartForm *LLChartForm;
//---------------------------------------------------------------------------
#endif

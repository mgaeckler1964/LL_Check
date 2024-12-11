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

#include <vcl.h>
#include <vcl/registry.hpp>
#pragma hdrstop

#include "llImportFrm.h"
#include "importLLstatus.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TllImportForm *llImportForm = NULL;
extern const char *registryKey;

//---------------------------------------------------------------------------
__fastcall TllImportForm::TllImportForm(TComponent* Owner)
	: TForm(Owner)
{
	theThread = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TllImportForm::FormShow(TObject *)
{
	StartStopButton->Caption = "Start";
	CancelCloseButton->Enabled = true;
	CancelCloseButton->Caption = "Cancel";

	TRegistry *registry = new TRegistry;
	if( registry->OpenKeyReadOnly( registryKey ) )
	{
		if( registry->ValueExists( "IgnoreErrors" ) )
			CheckBoxIgnoreErrors->Checked = registry->ReadBool( "IgnoreErrors" );
		if( registry->ValueExists( "summarize" ) )
			summarizeCheckBox->Checked = registry->ReadBool( "summarize" );
		if( registry->ValueExists( "DaysToKeep" ) )
			DaysToKeep->Position = (short)registry->ReadInteger( "DaysToKeep" );

		registry->CloseKey();
	}
}
//---------------------------------------------------------------------------
void __fastcall TllImportForm::StartStopButtonClick(TObject *)
{
	if( !theThread )
	{
		static ImportLLStatus	statusDisplay;

		TRegistry	*registry = new TRegistry;
		if( registry->OpenKey( registryKey, true ) )
		{
			registry->WriteBool( "IgnoreErrors", CheckBoxIgnoreErrors->Checked );
			registry->WriteBool( "summarize", summarizeCheckBox->Checked );
			registry->WriteInteger( "DaysToKeep", DaysToKeep->Position );

			registry->CloseKey();
		}
		delete registry;

		theThread = new llImportThread(
			false, CheckBoxIgnoreErrors->Checked, summarizeCheckBox->Checked,
			DaysToKeep->Position,
			&statusDisplay
		);
		StartStopButton->Caption = "Stop";
		CancelCloseButton->Caption = "Close";
		CancelCloseButton->Enabled = false;
		threadTimer->Enabled = true;
	}
	else
		theThread->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TllImportForm::CancelCloseButtonClick(TObject *)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TllImportForm::FormCloseQuery(TObject *, bool &CanClose)
{
	CanClose = theThread ? false : true;
}

//---------------------------------------------------------------------------
void __fastcall TllImportForm::FormClose(TObject *,
	  TCloseAction &Action)
{
	if( theThread )
		Action = caNone;
}
//---------------------------------------------------------------------------

void __fastcall TllImportForm::threadTimerTimer(TObject *)
{
	if( theThread && !theThread->IsRunning() )
	{
		delete theThread;
		theThread = NULL;
	}
	if( !theThread )
	{
		StartStopButton->Caption = "Start";
		CancelCloseButton->Enabled = true;
		threadTimer->Enabled = false;
	}
}
//---------------------------------------------------------------------------




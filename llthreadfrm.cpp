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
#include <stdio.h>

#include <dir.h>
#include <vcl.h>
#include <vcl/registry.hpp>
#pragma hdrstop

#include "llthreadfrm.h"
#include "llImportFrm.h"
#include "llExportFrm.h"
#include "DataUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TLLthreadForm *LLthreadForm = NULL;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TLLthreadForm::TLLthreadForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLLthreadForm::FormShow(TObject *)
{
	theDataSource->DataSet->Open();
}
//---------------------------------------------------------------------------


void __fastcall TLLthreadForm::SortComboBoxChange(TObject *)
{
	AnsiString	newIndex;

	if( SortComboBox->ItemIndex == 0 )
		newIndex = "REQUEST_DATE_IDX";
	else if( SortComboBox->ItemIndex == 1 )
		newIndex = "FUNC_IDX";
	else if( SortComboBox->ItemIndex == 2 )
		newIndex = "TIME_IDX";

	theDataModule->llThreadTable->IndexName = newIndex;
}
//---------------------------------------------------------------------------

void __fastcall TLLthreadForm::FormClose(TObject *,
	  TCloseAction &Action)
{
	Action = caFree;
	theDataSource->DataSet->Close();
	LLthreadForm = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TLLthreadForm::ButtonImportClick(TObject *)
{
	llImportForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TLLthreadForm::ButtonExportClick(TObject *)
{
	llExportForm->ShowModal();
}
//---------------------------------------------------------------------------


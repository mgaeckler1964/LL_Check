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

#ifndef HtmlBrowseFrmH
#define HtmlBrowseFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
namespace gak
{
namespace html
{
	class Document;
}
}

class THtmlBrowseForm : public TForm
{
__published:	// IDE-managed Components
	TTreeView *TreeViewHTML;
	TMemo *MemoValue;
	void __fastcall TreeViewHTMLDblClick(TObject *Sender);
	void __fastcall TreeViewHTMLChange(TObject *Sender, TTreeNode *Node);
private:	// User declarations
	gak::xml::Element	*selected;
	gak::STRING			selAttribute;
	void buildTree( TTreeNode *parent, gak::xml::Element *xmlElem );
public:		// User declarations
	__fastcall THtmlBrowseForm(TComponent* Owner);
	gak::html::Document	*lastDoc;
	gak::STRING			lastURL;

	void setHTMLdocument( gak::html::Document *theDoc );

	gak::xml::Element *getSelected( void ) const
	{
		return selected;
	}
	const gak::STRING &getSelAttribute( void ) const
	{
		return selAttribute;
	}
};
//---------------------------------------------------------------------------
extern PACKAGE THtmlBrowseForm *HtmlBrowseForm;
//---------------------------------------------------------------------------
#endif

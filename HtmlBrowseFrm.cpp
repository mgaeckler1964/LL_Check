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

#include <gak/html.h>

#pragma hdrstop

#include "HtmlBrowseFrm.h"
//---------------------------------------------------------------------------
using namespace gak;
using namespace xml;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THtmlBrowseForm *HtmlBrowseForm;
//---------------------------------------------------------------------------
__fastcall THtmlBrowseForm::THtmlBrowseForm(TComponent* Owner)
	: TForm(Owner)
{
	lastDoc = NULL;
}
//---------------------------------------------------------------------------
void THtmlBrowseForm::buildTree( TTreeNode *parent, Element *xmlElem )
{
	TTreeNode	*newNode, *attrNode;
	STRING		tag, attrName;

	for( size_t i=0; i<xmlElem->getNumObjects(); i++ )
	{
		Element *theElem = xmlElem->getElement( i );
		tag = theElem->getTag();
		if( !tag.isEmpty()  )
		{
			newNode = TreeViewHTML->Items->AddChild(
				parent, (const char *)tag
			);
			newNode->Data = theElem;
			for( size_t i=0; i<theElem->getNumAttributes(); i++ )
			{
				attrName = theElem->getAttributeName( i );
				if( !attrName.isEmpty() )
				{
					attrName = STRING( '@' ) + attrName;
					attrNode = TreeViewHTML->Items->AddChild(
						newNode, (const char *)attrName
					);
					attrNode->Data = theElem;
				}
			}

			buildTree( newNode, theElem );
		}
	}
}
//---------------------------------------------------------------------------
void THtmlBrowseForm::setHTMLdocument( html::Document *theDoc )
{
	STRING url = theDoc->getFilename();

	if( lastDoc != theDoc || lastURL != url )
	{
		lastDoc = theDoc;
		lastURL = url;

		selected = NULL;

		TreeViewHTML->Items->BeginUpdate();
		TreeViewHTML->Items->Clear();
		TTreeNode *node = TreeViewHTML->Items->Add(
			NULL, static_cast<const char *>(url)
		);
		node->Data = theDoc;

		buildTree( node, theDoc );

		node->Expand(true);
		TreeViewHTML->TopItem = node;

		TreeViewHTML->Items->EndUpdate();
	}
}
//---------------------------------------------------------------------------

void __fastcall THtmlBrowseForm::TreeViewHTMLDblClick(TObject *)
{
	if( TreeViewHTML->Selected && TreeViewHTML->Selected->Data )
	{
		selected = static_cast<Element*>(TreeViewHTML->Selected->Data);
		if( TreeViewHTML->Selected->Parent
		&& static_cast<Element*>(TreeViewHTML->Selected->Parent->Data) == selected )
			selAttribute = TreeViewHTML->Selected->Text.c_str();
		else
			selAttribute = (const char *)NULL;

		ModalResult = mrOk;
	}
}
//---------------------------------------------------------------------------

void __fastcall THtmlBrowseForm::TreeViewHTMLChange(TObject *,
	  TTreeNode *Node)
{

	Element *selected = static_cast<Element*>(Node->Data);

	STRING	value =
		( Node->Parent && Node->Parent->Data == selected )
		? selected->getAttribute( Node->Text.c_str() +1 )
		: selected->getValue( PLAIN_MODE )
	;

	MemoValue->Text = (const char *)value;	
}
//---------------------------------------------------------------------------


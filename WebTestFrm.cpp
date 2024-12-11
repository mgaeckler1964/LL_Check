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

#include <fstream>

#include <vcl.h>

#include <gak/array.h>

#pragma hdrstop

#include "WebTestFrm.h"
#include "HtmlBrowseFrm.h"
#include "TestResultFrm.h"
//---------------------------------------------------------------------------
using namespace gak;
using namespace xml;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWebTestForm *WebTestForm;
//---------------------------------------------------------------------------
__fastcall TWebTestForm::TWebTestForm(TComponent* Owner)
	: TForm(Owner)
{
	currentStep = NULL;
	rootNode = NULL;
	theDocument = NULL;
}
//---------------------------------------------------------------------------
void WebAutoTest::toBinaryStream( std::ostream &target )
{
	TestSignature	sig = { "CRESDWebTest", 0x01020304, 1 };

	target.write( (const char *)&sig, sizeof( sig ) );

	baseURL.toBinaryStream( target );
	baseURLs.toBinaryStream( target );
	testCases.toBinaryStream( target );
}
void WebAutoTest::fromBinaryStream( std::istream &source )
{
	TestSignature	sig;

	source.read( (char *)&sig, sizeof( sig ) );

	if( strcmp( sig.signature, "CRESDWebTest" )
	|| sig.magic != 0x01020304
	|| sig.version != 1 )
		return;

	baseURL.fromBinaryStream( source );
	baseURLs.fromBinaryStream( source );
	testCases.fromBinaryStream( source );
}

//---------------------------------------------------------------------------
void __fastcall TWebTestForm::FormClose(TObject *, TCloseAction &Action)
{
	Action = caFree;	
}
//---------------------------------------------------------------------------
void __fastcall TWebTestForm::FormCreate(TObject *)
{
	StringGridParameter->Cells[0][0] = "Parameter";
	StringGridParameter->Cells[1][0] = "Value";

	StringGridValues->Cells[0][0] = "Element";
	StringGridValues->Cells[1][0] = "Value";
	StringGridValues->Cells[2][0] = "Result";
}
//---------------------------------------------------------------------------
void __fastcall TWebTestForm::FormResize(TObject *)
{
	StringGridParameter->DefaultColWidth = StringGridParameter->ClientWidth/2 - 10;
	StringGridValues->DefaultColWidth = StringGridValues->ClientWidth/2 - 45;
	StringGridValues->ColWidths[2] = 70;
}
//---------------------------------------------------------------------------
void __fastcall TWebTestForm::FormShow(TObject *Sender)
{
	FormResize( Sender );
	SpeedButtonNewClick( Sender );
}
//---------------------------------------------------------------------------
void __fastcall TWebTestForm::SpeedButtonNewClick(TObject *)
{
	theTest.clear();
	TreeView->Items->Clear();
	rootNode = TreeView->Items->Add( NULL, "http://localhost/" );
	theTest.setBaseURL( "http://localhost/" );
	ComboBoxBaseURL->Text = "http://localhost/";
}
//---------------------------------------------------------------------------


void __fastcall TWebTestForm::ComboBoxBaseURLChange(TObject *)
{
	theTest.setBaseURL( ComboBoxBaseURL->Text.c_str() );
	rootNode->Text = ComboBoxBaseURL->Text.c_str();
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::SpeedButtonSaveClick(TObject *)
{
	SaveDialog->FileName = (const char *)fileName;
	if( SaveDialog->Execute() )
	{
		fileName = SaveDialog->FileName.c_str();

		std::ofstream	outs( fileName, std::ios_base::binary|std::ios_base::trunc );

		if( outs.is_open() )
		{
			theTest.toBinaryStream( outs );
			outs.close();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TWebTestForm::ButtonNewCaseClick(TObject *Sender )
{
	TTreeNode 	*newNode = TreeView->Items->AddChild( rootNode, "New Case" );
	size_t		newIndex = theTest.newCase( "New Case" );
	newNode->Data = (void*)newIndex;
	rootNode->Expand( false );
	TreeView->Selected = newNode;
	TreeView->SetFocus();

	ButtonNewStepClick( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::ButtonNewStepClick(TObject * )
{
	TTreeNode	*selected = TreeView->Selected;
	int			level = selected->Level;
	if( level )
	{
		if( level > 1 )
			selected = selected->Parent;

		size_t		caseIndex = (size_t)selected->Data;
		TestCase	&theCase = theTest.getCase( caseIndex );

		TTreeNode 	*newNode = TreeView->Items->AddChild( selected, "New Step" );
		size_t		newIndex = theCase.newStep( "New Step" );
		newNode->Data = (void*)newIndex;

		selected->Expand( false );
		TreeView->Selected = newNode;
		TreeView->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::TreeViewEdited(TObject *,
      TTreeNode *Node, AnsiString &S)
{
	if( Node->Level == 0 )
	{
		ComboBoxBaseURL->Text = S;
		// theTest.setBaseURL( S.c_str() );
	}
	else if( Node->Level == 1 )
	{
		TestCase	&theCase = theTest.getCase( (size_t)Node->Data );
		theCase.setName( S.c_str() );
	}
	else if( Node->Level == 2 )
	{
		TestCase	&theCase = theTest.getCase( (size_t)Node->Parent->Data );
		TestStep	&theStep = theCase.getStep( (size_t)Node->Data );
		theStep.setName( S.c_str() );
	}
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::TreeViewChange(TObject *,
      TTreeNode *Node)
{
	if( Node->Level <= 1 )
	{
		ComboBoxStepURL->Text = "";
		ComboBoxStepURL->Enabled = false;

		RadioButtonGet->Enabled = false;
		RadioButtonPost->Enabled = false;

		StringGridParameter->RowCount = 2;
		StringGridParameter->Cells[0][1] = "";
		StringGridParameter->Cells[1][1] = "";
		StringGridParameter->Enabled = false;

		CheckBoxStatus->Enabled = false;

		ComboBoxContentType->Text = "";
		ComboBoxContentType->Enabled = false;

		StringGridValues->RowCount = 2;
		StringGridValues->Cells[0][1] = "";
		StringGridValues->Cells[1][1] = "";
		StringGridValues->Cells[2][1] = "";
		StringGridValues->Enabled = false;

		ButtonRunStep->Enabled = false;

		currentStep = NULL;
	}
	else if( Node->Level == 2 )
	{
		size_t i, j;
		currentStep = NULL;

		TestCase	&theCase = theTest.getCase( (size_t)Node->Parent->Data );
		TestStep	&theStep = theCase.getStep( (size_t)Node->Data );

		ComboBoxStepURL->Text = (const char *)theStep.getURL();
		ComboBoxStepURL->Enabled = true;

		if( theStep.getMethod() == TestStep::REQUEST_GET )
			RadioButtonGet->Checked = true;
		else
			RadioButtonPost->Checked = true;

		RadioButtonGet->Enabled = true;
		RadioButtonPost->Enabled = true;

		size_t	numParameter = theStep.getNumParameter();
		StringGridParameter->RowCount = numParameter+2;
		for( i=0, j=1; i<numParameter; i++, j++ )
		{
			StringGridParameter->Cells[0][j] = (const char *)theStep.getParameterName( i );
			StringGridParameter->Cells[1][j] = (const char *)theStep.getParameterValue( i );
		}
		StringGridParameter->Cells[0][j] = "";
		StringGridParameter->Cells[1][j] = "";

		StringGridParameter->Enabled = true;

		CheckBoxStatus->Checked = theStep.getCheckStatus();
		CheckBoxStatus->Enabled = true;

		ComboBoxContentType->Text = (const char *)theStep.getType();
		ComboBoxContentType->Enabled = true;

		size_t	numElements = theStep.getNumExpectedElements();
		StringGridValues->RowCount = numElements+2;
		for( i=0, j=1; i<numElements; i++, j++ )
		{
			StringGridValues->Cells[0][j] = (const char *)theStep.getExpectedElement( i );
			StringGridValues->Cells[1][j] = (const char *)theStep.getElementValue( i );
			StringGridValues->Cells[2][j] = (const char *)theStep.getElementStatus( i );
		}
		StringGridValues->Cells[0][j] = "";
		StringGridValues->Cells[1][j] = "";
		StringGridValues->Cells[2][j] = "";

		StringGridValues->Enabled = true;

		ButtonRunStep->Enabled = true;

		currentStep = &theStep;
	}

	ButtonNewStep->Enabled =  (Node->Level >= 1);
	ButtonBrowseHtml->Enabled = currentStep && theDocument;

}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::ComboBoxStepURLChange(TObject *)
{
	if( currentStep )
	{
		STRING	newURL = ComboBoxStepURL->Text.c_str();
		if( newURL.beginsWith( "form: " ) )
		{
			STRING	action, name, value;
			newURL += (size_t)6;

			for(
				XmlArray::const_iterator it = forms.cbegin(),
					endIT = forms.cend();
				it != endIT;
				++it
			)
			{
				const Element *form = *it;
				action = form->getAttribute( "ACTION" );
				if( action == newURL )
				{
					XmlArray	inputs;
					form->getAllElements( &inputs, "INPUT" );
					size_t	numParameter = inputs.size();
					StringGridParameter->RowCount = numParameter+2;
					for( std::size_t iIdx=0, p=0, j=1; iIdx<numParameter; iIdx++ )
					{
						Element *input = inputs[iIdx];

						name = input->getAttribute( "NAME" );
						value = input->getAttribute( "VALUE" );

						if( !name.isEmpty() )
						{
							currentStep->setParameterName( p, name );
							currentStep->setParameterValue( p++, value );

							StringGridParameter->Cells[0][j] = static_cast<const char *>(name);
							StringGridParameter->Cells[1][j++] = static_cast<const char *>(value);
						}
					}
/*v*/				break;
				}
			}
		}

		currentStep->setURL( newURL );
	}
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::ChangeRequestMethod(TObject *)
{
	if( currentStep )
	{
		if( RadioButtonGet->Checked )
			currentStep->setMethod( TestStep::REQUEST_GET );
		else
			currentStep->setMethod( TestStep::REQUEST_POST );
	}
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::CheckBoxStatusClick(TObject *)
{
	if( currentStep )
		currentStep->setCheckStatus( CheckBoxStatus->Checked );
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::ComboBoxContentTypeChange(TObject *)
{
	if( currentStep )
		currentStep->setType( ComboBoxContentType->Text.c_str() );
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::StringGridParameterSetEditText(
	  TObject *, int ACol, int ARow, const AnsiString Value)
{
	if( currentStep && ARow )
	{
		size_t	paramIndex = ARow-1;
		if( ACol == 0 )
			currentStep->setParameterName( paramIndex, Value.c_str() );
		else
			currentStep->setParameterValue( paramIndex, Value.c_str() );

		if( ARow +1 >= StringGridParameter->RowCount )
			StringGridParameter->RowCount = ARow + 2;
	}
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::StringGridValuesSetEditText(TObject *,
	  int ACol, int ARow, const AnsiString Value)
{
	if( currentStep && ARow )
	{
		size_t	elementIndex = ARow-1;
		if( ACol == 0 )
			currentStep->setExpectedElement( elementIndex, Value.c_str() );
		else
			currentStep->setElementValue( elementIndex, Value.c_str() );

		if( ARow +1 >= StringGridValues->RowCount )
			StringGridValues->RowCount = ARow + 2;
	}
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::SpeedButtonOpenClick(TObject *)
{
	OpenDialog->FileName = (const char *)fileName;
	if( OpenDialog->Execute() )
	{
		fileName = OpenDialog->FileName.c_str();

		TTreeNode		*caseNode, *stepNode;
		std::ifstream	in( fileName, std::ios_base::binary );

		if( in.is_open() )
		{
			theTest.clear();
			TreeView->Items->BeginUpdate();
			TreeView->Items->Clear();
			currentStep = NULL;
			rootNode = NULL;

			theTest.fromBinaryStream( in );
			in.close();

			const STRING	&baseURL = theTest.getBaseURL();
			rootNode = TreeView->Items->Add( NULL, (const char *)baseURL );
			ComboBoxBaseURL->Text = (const char *)baseURL;

			for( size_t i=0; i<theTest.getNumCases(); i++ )
			{
				TestCase	&theCase = theTest.getCase( i );
				caseNode = TreeView->Items->AddChild( rootNode, (const char *)theCase.getName() );
				caseNode->Data = (void *)i;
				for( size_t i=0; i<theCase.getNumSteps(); i++ )
				{
					TestStep	&theStep = theCase.getStep( i );
					stepNode = TreeView->Items->AddChild( caseNode, (const char *)theStep.getName() );
					stepNode->Data = (void *)i;
				}
			}

			rootNode->Expand( true );
			TreeView->TopItem = rootNode;

			TreeView->Items->EndUpdate();
		}
	}
}
//---------------------------------------------------------------------------
STRING TWebTestForm::RunStep( TestStep *currentStep )
{
	STRING	queryString;
	STRING	baseURL = theTest.getBaseURL();
	STRING	url = currentStep->getURL();
	STRING	newURL = net::HTTPrequest::makeFullPath( baseURL, url );
	STRING	location;

	if( currentStep->getNumParameter() )
	{
		for( size_t i=0; i<currentStep->getNumParameter(); i++ )
		{
			if( !queryString.isEmpty() )
				queryString += '&';
			queryString += currentStep->getParameterName( i )
				+ '=' + currentStep->getParameterValue( i );
		}

		if( currentStep->getMethod() == TestStep::REQUEST_GET )
		{
			if( url.searchChar( '?' ) == -1 )
				newURL += '?';
			newURL += queryString;
			queryString = (const char *)NULL;
		}
	}

	while( true )
	{
		if( !queryString.isEmpty() )
			httpConnection.Post( newURL, "application/x-www-form-urlencoded", queryString, queryString.strlen() );
		else
			httpConnection.Get( newURL );

		location = httpConnection.getLocation();
		if( location.isEmpty() )
/*v*/			break;

		newURL = net::HTTPrequest::makeFullPath( newURL, location );
	}
	currentStep->setHttpStatusFound( httpConnection.getHttpStatusText() );
	currentStep->setStatusOK( httpConnection.getHttpStatusCode() == 200 );
	currentStep->setTypeFound( httpConnection.getContentType() );

	if( theDocument )
	{
		delete theDocument;
		theDocument = NULL;
	}
	theDocument = httpConnection.getHtmlDocument();
	if( theDocument )
	{
		// do first tests
		XmlArray	elements;
		STRING		status, elementPath, expectedValue, foundValue, attribute;
		bool		contentStatus = true;
		bool		elementStatus;
		for( std::size_t i=0; i<currentStep->getNumExpectedElements(); i++ )
		{
			elementStatus = false;
			elementPath = currentStep->getExpectedElement( i );

			STRING	attribute = theDocument->locateElements( elementPath, &elements, false );
			if( !elements.size() )
			{
				status = "Not Found";
			}
			else
			{
				expectedValue = currentStep->getElementValue( i );
				status = "Bad Value";
				for(
					XmlArray::const_iterator it = elements.cbegin(),
						endIT = elements.cend();
					it != endIT;
					++it
				)
				{
					const Element	*elementFound  = *it;
					foundValue = attribute.isEmpty()
						? elementFound->getValue( PLAIN_MODE )
						: elementFound->getAttribute( attribute )
					;
					if( foundValue == expectedValue )
					{
						elementStatus = true;
						status = "OK";
						break;
					}
				}
			}
			currentStep->setElementStatus( i, status );
			if( !elementStatus )
				contentStatus = false;
		}

		currentStep->setContentStatus( contentStatus );
	}

	return newURL;
}

void __fastcall TWebTestForm::ButtonRunStepClick(TObject *Sender )
{
	ButtonBrowseHtml->Enabled = false;

	if( currentStep )
	{
		STRING newURL = RunStep( currentStep );

		STRING status = STRING("Status: ") + httpConnection.getHttpStatusText();
		LabelStatus->Caption = (const char *)status;

		if( theDocument )
		{
			XmlArray	anchors;
			STRING		href, nextURL;

			STRING		baseURL = theTest.getBaseURL();
			STRING		url = currentStep->getURL();

			theDocument->getAllElements( &anchors, "A" );
			ComboBoxStepURL->Items->Clear();
			ComboBoxStepURL->Items->Add( (const char *)url );
			for(
				XmlArray::const_iterator it = anchors.cbegin(),
					endIT = anchors.cend();
				it != endIT;
				++it
			)
			{
				const Element *anchor = *it;
				href = anchor->getAttribute( "HREF" );
				if( !href.isEmpty() )
				{
					nextURL = net::HTTPrequest::makeFullPath( newURL, href );
					if( nextURL.beginsWith( baseURL ) )
					{
						nextURL += baseURL.strlen();
						if( !nextURL.isEmpty() )
							ComboBoxStepURL->Items->Add( (const char *)nextURL );
					}
				}
			}
			theDocument->getAllElements( &forms, "FORM" );
			for(
				XmlArray::const_iterator it = forms.cbegin(),
					endIT = forms.cend();
				it != endIT;
				++it
			)
			{
				Element *form = *it;
				href = form->getAttribute( "ACTION" );
				if( !href.isEmpty() )
				{
					nextURL = net::HTTPrequest::makeFullPath( newURL, href );
					if( nextURL.beginsWith( baseURL ) )
					{
						nextURL += baseURL.strlen();
						if( !nextURL.isEmpty() )
						{
							form->setStringAttribute( "ACTION", nextURL );
							nextURL = STRING("form: ") + nextURL;
							ComboBoxStepURL->Items->Add( (const char *)nextURL );
						}
					}
				}
			}
			ButtonBrowseHtml->Enabled = true;
		}

		if( !ComboBoxContentType->Text.Length() )
			currentStep->setType( httpConnection.getContentType() );

		TreeViewChange( Sender, TreeView->Selected );
	}
}
//---------------------------------------------------------------------------


void __fastcall TWebTestForm::StringGridParameterKeyUp(TObject *,
	  WORD &Key, TShiftState Shift)
{
	int Row = StringGridParameter->Row;
	if( Key == VK_DELETE
	&& Shift.Contains( ssCtrl )
	&& Row > 0
	&& currentStep )
	{
		currentStep->deleteParameter( Row-1 );

		size_t RowCount = StringGridParameter->RowCount;
		for( size_t i=Row, j=Row+1; j<RowCount; i++, j++ )
		{
			StringGridParameter->Cells[0][i] =StringGridParameter->Cells[0][j];
			StringGridParameter->Cells[1][i] =StringGridParameter->Cells[1][j];
		}
		if( RowCount > 2 )
			StringGridParameter->RowCount = RowCount-1;
		Key = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TWebTestForm::StringGridValuesKeyUp(TObject *,
	  WORD &Key, TShiftState Shift)
{
	int Row = StringGridValues->Row;
	if( Key == VK_DELETE
	&& Shift.Contains( ssCtrl )
	&& Row > 0
	&& currentStep )
	{
		currentStep->deleteResult( Row-1 );

		size_t RowCount = StringGridValues->RowCount;
		for( size_t i=Row, j=Row+1; j<RowCount; i++, j++ )
		{
			StringGridValues->Cells[0][i] = StringGridValues->Cells[0][j];
			StringGridValues->Cells[1][i] = StringGridValues->Cells[1][j];
			StringGridValues->Cells[2][i] = StringGridValues->Cells[2][j];
		}
		if( RowCount > 2 )
			StringGridValues->RowCount = RowCount-1;
		Key = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::FormDestroy(TObject *)
{
	if( theDocument )
	{
		delete theDocument;
		theDocument = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::ButtonBrowseHtmlClick(TObject *)
{
	if( currentStep && theDocument )
	{
		HtmlBrowseForm->setHTMLdocument( theDocument );
		if( HtmlBrowseForm->ShowModal() == mrOk )
		{
			Element *selected = HtmlBrowseForm->getSelected();
			STRING	path = selected->getPath( false );
			STRING	value;

			STRING selAttribute = HtmlBrowseForm->getSelAttribute();
			if( !selAttribute.isEmpty() )
			{
				path += STRING('/') + selAttribute;
				value = selected->getAttribute( selAttribute+(size_t)1 );
			}
			else
				value = selected->getValue( PLAIN_MODE );
			size_t idx = currentStep->getNumExpectedElements();

			currentStep->setExpectedElement( idx, path );
			currentStep->setElementValue( idx, value );

			idx++;
			StringGridValues->Cells[0][idx] = (const char *)path;
			StringGridValues->Cells[1][idx] = (const char *)value;
			StringGridValues->Cells[2][idx] = "";
			idx++;
			StringGridValues->RowCount = idx+1;
			StringGridValues->Cells[0][idx] = "";
			StringGridValues->Cells[1][idx] = "";
			StringGridValues->Cells[2][idx] = "";
		}
	}	
}
//---------------------------------------------------------------------------

void __fastcall TWebTestForm::SpeedButtonRunTestsClick(TObject *)
{
	STRING	status;
	int		RowCount = 1;
	size_t	row=1;

	TestResultForm->StringGridResult->RowCount = RowCount;

	httpConnection.setCookies( "" );

	for( size_t i=0; i<theTest.getNumCases(); i++ )
	{
		TestCase &theCase = theTest.getCase( i );
		for( size_t i=0; i<theCase.getNumSteps(); i++, row++ )
		{
			TestStep &theStep = theCase.getStep( i );
			RunStep( &theStep );

			if( theStep.getCheckStatus() && !theStep.getStatusOK() )
				status = theStep.getHttpStatus();
			else if( !theStep.testContentType() )
				status = STRING( "Bad Content-Type " ) + theStep.getTypeFound();
			else if( !theStep.getContentStatus() )
				status = "Bad Content";
			else
				status = "OK";

			RowCount++;
			TestResultForm->StringGridResult->RowCount = RowCount;
			TestResultForm->StringGridResult->Cells[0][row] = (const char *)theCase.getName();
			TestResultForm->StringGridResult->Cells[1][row] = (const char *)theStep.getName();
			TestResultForm->StringGridResult->Cells[2][row] = (const char *)status;

		}
	}

	TestResultForm->StringGridResult->FixedRows = 1;
	TestResultForm->ShowModal();
}
//---------------------------------------------------------------------------


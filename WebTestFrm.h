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

#ifndef WebTestFrmH
#define WebTestFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>

#include <gak/http.h>

//---------------------------------------------------------------------------
struct TestSignature
{
	char	signature[13];
	int		magic, version;
};

//---------------------------------------------------------------------------
class TestValue
{
	protected:
	gak::STRING	element, value;

	public:
	void setName( const gak::STRING &name )
	{
		element = name;
	}
	const gak::STRING &getName( void ) const
	{
		return element;
	}
	void setValue( const gak::STRING &value )
	{
		this->value = value;
	}
	const gak::STRING &getValue( void ) const
	{
		return value;
	}
	void toBinaryStream( std::ostream &target ) const
	{
		element.toBinaryStream( target );
		value.toBinaryStream( target );
	}
	void fromBinaryStream( std::istream &source )
	{
		element.fromBinaryStream( source );
		value.fromBinaryStream( source );
	}
};
//---------------------------------------------------------------------------
class TestResult : public TestValue
{
	gak::STRING	status;

	public:
	void setStatus( const gak::STRING &status )
	{
		this->status = status;
	}
	const gak::STRING &getStatus( void ) const
	{
		return status;
	}
	void setElementPath( const gak::STRING &element )
	{
		this->element = element;
	}
	const gak::STRING &getElementPath( void ) const
	{
		return element;
	}
};
//---------------------------------------------------------------------------
class TestStep
{
	public:
	enum Method { REQUEST_GET, REQUEST_POST };

	private:
	gak::STRING				name;

	gak::STRING				url;
	Method					requestMethod;

	gak::Array<TestValue>	parameter;

	bool					checkHttpStatus;
	gak::STRING				expectedType;
	gak::Array<TestResult>	expectedResult;

	gak::STRING				httpStatusFound;
	gak::STRING				typeFound;
	bool					statusOK, contentStatus;

	public:
	TestStep()
	{
		requestMethod = REQUEST_GET;
		contentStatus = checkHttpStatus = statusOK = false;
	}
	void setName( const gak::STRING &newName )
	{
		name = newName;
	}
	const gak::STRING &getName( void ) const
	{
		return name;
	}
	void toBinaryStream( std::ostream &target ) const
	{
		name.toBinaryStream( target );
		url.toBinaryStream( target );

		target.write((const char*)&requestMethod, sizeof(requestMethod) );
		target.write((const char*)&checkHttpStatus, sizeof(checkHttpStatus) );

		parameter.toBinaryStream( target );
		expectedType.toBinaryStream( target );
		expectedResult.toBinaryStream( target );
	}
	void fromBinaryStream( std::istream &source )
	{
		name.fromBinaryStream( source );
		url.fromBinaryStream( source );

		source.read((char*)&requestMethod, sizeof(requestMethod) );
		source.read((char*)&checkHttpStatus, sizeof(checkHttpStatus) );

		parameter.fromBinaryStream( source );
		expectedType.fromBinaryStream( source );
		expectedResult.fromBinaryStream( source );
	}

	void setURL( const gak::STRING &url )
	{
		this->url = url;
	}
	const gak::STRING &getURL( void ) const
	{
		return url;
	}
	void setMethod( Method method )
	{
		requestMethod = method;
	}
	Method getMethod( void ) const
	{
		return requestMethod;
	}

	void setCheckStatus( bool newStatus )
	{
		checkHttpStatus = newStatus;
	}
	bool getCheckStatus( void )
	{
		return checkHttpStatus;
	}

	void setType( const gak::STRING &expectedType )
	{
		this->expectedType = expectedType;
	}
	const gak::STRING &getType( void ) const
	{
		return expectedType;
	}
	size_t getNumParameter( void ) const
	{
		return parameter.size();
	}
	void setParameterName( size_t idx, const gak::STRING &name )
	{
		TestValue	&parameter = this->parameter[idx];
		parameter.setName( name );
	}
	const gak::STRING &getParameterName( size_t idx )
	{
		TestValue	&parameter = this->parameter[idx];
		return parameter.getName();
	}
	void setParameterValue( size_t idx, const gak::STRING &value )
	{
		TestValue	&parameter = this->parameter[idx];
		parameter.setValue( value );
	}
	const gak::STRING &getParameterValue( size_t idx )
	{
		TestValue	&parameter = this->parameter[idx];
		return parameter.getValue();
	}
	void deleteParameter( size_t idx )
	{
		parameter.removeElementAt( idx );
	}


	size_t getNumExpectedElements( void ) const
	{
		return expectedResult.size();
	}
	void setExpectedElement( size_t idx, const gak::STRING &path )
	{
		TestResult	&element = this->expectedResult[idx];
		element.setElementPath( path );
	}
	const gak::STRING &getExpectedElement( size_t idx )
	{
		TestResult	&element = this->expectedResult[idx];
		return element.getElementPath();
	}
	void setElementValue( size_t idx, const gak::STRING &value )
	{
		TestResult	&element = this->expectedResult[idx];
		element.setValue( value );
	}
	const gak::STRING &getElementValue( size_t idx )
	{
		TestResult	&element = this->expectedResult[idx];
		return element.getValue();
	}
	void setElementStatus( size_t idx, const gak::STRING &status )
	{
		TestResult	&element = this->expectedResult[idx];
		element.setStatus( status );
	}
	const gak::STRING &getElementStatus( std::size_t idx )
	{
		TestResult	&element = this->expectedResult[idx];
		return element.getStatus();
	}
	void deleteResult( size_t idx )
	{
		expectedResult.removeElementAt( idx );
	}

	void setTypeFound( const gak::STRING &contentType )
	{
		typeFound = contentType;
	}
	const gak::STRING &getTypeFound( void ) const
	{
		return typeFound;
	}
	bool testContentType( void ) const
	{
		if( expectedType.isEmpty() || expectedType == typeFound )
			return true;
		else
			return false;
	}
	void setHttpStatusFound( const gak::STRING &statusText )
	{
		httpStatusFound = statusText;
	}
	void setStatusOK( bool httpStatus )
	{
		statusOK = httpStatus;
	}
	bool getStatusOK( void ) const
	{
		return statusOK;
	}
	const gak::STRING &getHttpStatus( void ) const
	{
		return httpStatusFound;
	}

	void setContentStatus( bool contentStatus )
	{
		this->contentStatus = contentStatus;
	}
	bool getContentStatus( void ) const
	{
		return contentStatus;
	}
};
//---------------------------------------------------------------------------
class TestCase
{
	gak::STRING				name;

	gak::Array<TestStep>	testSteps;

	public:
	void toBinaryStream( std::ostream &target ) const
	{
		name.toBinaryStream( target );
		testSteps.toBinaryStream( target );
	}
	void fromBinaryStream( std::istream &source )
	{
		name.fromBinaryStream( source );
		testSteps.fromBinaryStream( source );
	}
	void setName( const gak::STRING &newName )
	{
		name = newName;
	}
	const gak::STRING &getName( void ) const
	{
		return name;
	}
	size_t getNumSteps( void ) const
	{
		return testSteps.size();
	}
	size_t newStep( const gak::STRING &newName )
	{
		size_t newIndex = testSteps.size();
		TestStep	&newStep = testSteps[newIndex];

		newStep.setName( newName );

		return newIndex;
	}
	TestStep &getStep( size_t index )
	{
		return testSteps[index];
	}
};
//---------------------------------------------------------------------------
class WebAutoTest
{
	gak::STRING				baseURL;

	gak::ArrayOfStrings		baseURLs;
	gak::Array<TestCase>	testCases;

	public:
	void clear( void )
	{
		baseURL = (const char *)NULL;
		baseURLs.clear();
		testCases.clear();
	}
	void setBaseURL( const char *baseURL )
	{
		this->baseURL = baseURL;
	}
	const gak::STRING getBaseURL( void ) const
	{
		return baseURL;
	}

	void toBinaryStream( std::ostream &target );
	void fromBinaryStream( std::istream &source );

	size_t getNumCases( void ) const
	{
		return testCases.size();
	}
	size_t newCase( const gak::STRING &newName )
	{
		size_t		newIndex = testCases.size();
		TestCase	&newCase = testCases[newIndex];

		newCase.setName( newName );

		return newIndex;
	}
	TestCase &getCase( size_t index )
	{
		return testCases[index];
	}
};
//---------------------------------------------------------------------------
class TWebTestForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *SpeedButtonNew;
	TSpeedButton *SpeedButtonOpen;
	TSpeedButton *SpeedButtonSave;
	TTreeView *TreeView;
	TLabel *Label1;
	TComboBox *ComboBoxBaseURL;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TButton *ButtonNewCase;
	TButton *ButtonNewStep;
	TGroupBox *GroupBoxRequest;
	TSplitter *Splitter2;
	TGroupBox *GroupBoxResult;
	TLabel *Label2;
	TComboBox *ComboBoxStepURL;
	TLabel *Label3;
	TRadioButton *RadioButtonGet;
	TRadioButton *RadioButtonPost;
	TLabel *Label4;
	TStringGrid *StringGridParameter;
	TLabel *Label5;
	TCheckBox *CheckBoxStatus;
	TLabel *Label6;
	TComboBox *ComboBoxContentType;
	TLabel *Label7;
	TStringGrid *StringGridValues;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TButton *ButtonRunStep;
	TLabel *LabelStatus;
	TButton *ButtonBrowseHtml;
	TSpeedButton *SpeedButtonRunTests;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SpeedButtonNewClick(TObject *Sender);
	void __fastcall ComboBoxBaseURLChange(TObject *Sender);
	void __fastcall SpeedButtonSaveClick(TObject *Sender);
	void __fastcall ButtonNewCaseClick(TObject *Sender);
	void __fastcall ButtonNewStepClick(TObject *Sender);
	void __fastcall TreeViewEdited(TObject *Sender, TTreeNode *Node,
          AnsiString &S);
	void __fastcall TreeViewChange(TObject *Sender, TTreeNode *Node);
	void __fastcall ComboBoxStepURLChange(TObject *Sender);
	void __fastcall ChangeRequestMethod(TObject *Sender);
	void __fastcall CheckBoxStatusClick(TObject *Sender);
	void __fastcall ComboBoxContentTypeChange(TObject *Sender);
	void __fastcall StringGridParameterSetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
	void __fastcall StringGridValuesSetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
	void __fastcall SpeedButtonOpenClick(TObject *Sender);
	void __fastcall ButtonRunStepClick(TObject *Sender);
	void __fastcall StringGridParameterKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall StringGridValuesKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ButtonBrowseHtmlClick(TObject *Sender);
	void __fastcall SpeedButtonRunTestsClick(TObject *Sender);
private:	// User declarations
	WebAutoTest				theTest;
	TTreeNode				*rootNode;
	TestStep				*currentStep;
	gak::STRING				fileName;

	gak::net::HTTPrequest	httpConnection;
	gak::xml::XmlArray		forms;
	gak::html::Document		*theDocument;

	gak::STRING RunStep( TestStep *currentStep );

public:		// User declarations
	__fastcall TWebTestForm(TComponent* Owner);
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern PACKAGE TWebTestForm *WebTestForm;
//---------------------------------------------------------------------------
#endif

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
#pragma hdrstop
USERES("ll_check.res");
USEFORM("webThreadFrm.cpp", WebThreadForm);
USEFORM("webStatFrm.cpp", webStatForm);
USEFORM("httpChartFrm.cpp", httpChartForm);
USEFORM("httpFrm.cpp", httpForm);
USEFORM("webServerFrm.cpp", webServerForm);
USEFORM("DataUnit.cpp", theDataModule); /* TDataModule: File Type */
USEFORM("httpTimesFrm.cpp", httpTimesForm);
USEFORM("webChartFrm.cpp", WebChartForm);
USEUNIT("webImportThrd.cpp");
USEFORM("webImportFrm.cpp", webImportForm);
USEFORM("webSummarizedFrm.cpp", webSummarizedForm);
USEFORM("webFuncSelFrm.cpp", webFuncSelForm);
USEFORM("llExportFrm.cpp", llExportForm);
USEFORM("webStatChartFrm.cpp", WebStatChartForm);
USEFORM("AboutFrm.cpp", AboutBox);
USEFORM("httpAutoCheckFrm.cpp", httpAutoCheckForm);
USELIB("..\..\Object\gaklib\gaklib_bcb.lib");
USEFORM("HttpRecurringFrm.cpp", HttpRecurringForm);
USEFORM("CheckMainFrm.cpp", CheckMainForm);
USEFORM("httpLoginFrm.cpp", httpLoginForm);
USEFORM("DeleteFrm.cpp", DeleteDateForm);
USEFORM("llServerFrm.cpp", llServerForm);
USEFORM("llthreadfrm.cpp", LLthreadForm);
USEFORM("llImportFrm.cpp", llImportForm);
USEUNIT("llImportThrd.cpp");
USEFORM("llStatFrm.cpp", llStatForm);
USEFORM("llStatChartFrm.cpp", LLStatChartForm);
USEFORM("llSummarizedFrm.cpp", llSummarizedForm);
USEFORM("llChartFrm.cpp", LLChartForm);
USEFORM("llFuncSelFrm.cpp", llFuncSelForm);
USEUNIT("importLLStatus.cpp");
USEUNIT("importWebStatus.cpp");
USEFORM("WebTestFrm.cpp", WebTestForm);
USEFORM("HtmlBrowseFrm.cpp", HtmlBrowseForm);
USELIB("..\..\Object\winlib\winlibBCB.lib");
USEFORM("TestResultFrm.cpp", TestResultForm);
//---------------------------------------------------------------------------
extern const char *registryKey = "Software\\CRESD\\LivelinkCheck";
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR , int)
{
	try
	{
		Application->Initialize();
		Application->Title = "LL Check";
		Application->CreateForm(__classid(TCheckMainForm), &CheckMainForm);
		Application->CreateForm(__classid(TwebServerForm), &webServerForm);
		Application->CreateForm(__classid(TtheDataModule), &theDataModule);
		Application->CreateForm(__classid(TwebImportForm), &webImportForm);
		Application->CreateForm(__classid(TwebFuncSelForm), &webFuncSelForm);
		Application->CreateForm(__classid(TllExportForm), &llExportForm);
		Application->CreateForm(__classid(TWebStatChartForm), &WebStatChartForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(ThttpAutoCheckForm), &httpAutoCheckForm);
		Application->CreateForm(__classid(ThttpLoginForm), &httpLoginForm);
		Application->CreateForm(__classid(TDeleteDateForm), &DeleteDateForm);
		Application->CreateForm(__classid(TllServerForm), &llServerForm);
		Application->CreateForm(__classid(TllImportForm), &llImportForm);
		Application->CreateForm(__classid(TLLStatChartForm), &LLStatChartForm);
		Application->CreateForm(__classid(TllFuncSelForm), &llFuncSelForm);
		Application->CreateForm(__classid(THtmlBrowseForm), &HtmlBrowseForm);
		Application->CreateForm(__classid(TTestResultForm), &TestResultForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------




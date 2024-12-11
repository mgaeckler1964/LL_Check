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

#include <gak/logfile.h>

#pragma hdrstop
USERES("http_check.res");
USEFORM("httpChartFrm.cpp", httpChartForm);
USEFORM("HttpCheckMainFrm.cpp", HttpCheckMainForm);
USEFORM("httpFrm.cpp", httpForm);
USEFORM("DataUnit.cpp", theDataModule); /* TDataModule: File Type */
USEFORM("httpLoginFrm.cpp", httpLoginForm);
USEFORM("httpTimesFrm.cpp", httpTimesForm);
USEUNIT("..\WINLIB\WINLIB.CPP");
USEFORM("AboutFrm.cpp", AboutBox);
USEFORM("httpAutoCheckFrm.cpp", httpAutoCheckForm);
USELIB("..\..\Object\gaklib\gaklib_bcb.lib");
USEFORM("HttpRecurringFrm.cpp", HttpRecurringForm);
USEFORM("WebTestFrm.cpp", WebTestForm);
USEFORM("HtmlBrowseFrm.cpp", HtmlBrowseForm);
USEFORM("TestResultFrm.cpp", TestResultForm);
//---------------------------------------------------------------------------
extern const char *registryKey = "Software\\CRESD\\HttpCheck";
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR , int)
{
	doEnterFunction("WinMain");

	try
	{
		doLogPosition();
		Application->Initialize();
		Application->Title = "HTTP Check";
		doLogPosition();
		Application->CreateForm(__classid(THttpCheckMainForm), &HttpCheckMainForm);
		Application->CreateForm(__classid(ThttpLoginForm), &httpLoginForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(ThttpAutoCheckForm), &httpAutoCheckForm);
		Application->CreateForm(__classid(THtmlBrowseForm), &HtmlBrowseForm);
		Application->CreateForm(__classid(TTestResultForm), &TestResultForm);
		doLogPosition();
		Application->Run();
		doLogPosition();
	}
	catch (Exception &exception)
	{
		doLogPosition();
		Application->ShowException(&exception);
		doLogPosition();
	}
	return 0;
}
//---------------------------------------------------------------------------









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
#ifndef httpFrmH
#define httpFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------

#include <gak/httpProfiler.h>

//---------------------------------------------------------------------------
class ThttpForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *CommandPanel;
	TButton *GetButton;
	TButton *LoginButton;
	TLabel *Label5;
	TEdit *LoopsEdit;
	TUpDown *LoopCount;
	TEdit *UserCountEdit;
	TUpDown *UserCount;
	TEdit *TimeEdit;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *CookieEdit;
	TLabel *Label9;
	TButton *GetLocationButton;
	TCheckBox *Complete;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TMemo *HeadMemo;
	TMemo *MemoStatus;
	TMemo *BodyMemo;
	TLabel *Label1;
	TEdit *ProxyServer;
	TEdit *ProxyPort;
	TCheckBox *CheckBoxAnchors;
	TLabel *Label2;
	TEdit *DelayEdit;
	TUpDown *Delay;
	TComboBox *UrlEdit;
	TButton *HeadButton;
	TButton *AutoCheckButton;
	TCheckBox *CheckBoxCache;
	TLabel *Label3;
	TEdit *EditUserName;
	TEdit *EditPassword;
	TTabSheet *TabSheetError;
	TMemo *MemoErrors;
	TCheckBox *CheckBoxExternal;
	void __fastcall GetButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LoginButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall GetLocationButtonClick(TObject *Sender);
	void __fastcall enableDisableAnchors(TObject *Sender);
	void __fastcall AutoCheckButtonClick(TObject *Sender);
private:	// User declarations

	gak::net::HTTPprofiler	*httpConnection;

	size_t getHTTPresult(
		bool getRequest, const char *url,
		bool includes, bool anchorTags, bool noExternalLinks,
		bool clearExpiredOnly
	);
	double doConnection(
		bool getRequest,
		int totalUserCount, int loops, int delay,
		bool complete, bool anchorTags, bool noExternalLinks,
		bool clearExpiredOnly, 
		const gak::STRING &url,
		const gak::STRING &proxyServer, int proxyPort,
		const gak::STRING &cookies,
		const gak::STRING &userName, const gak::STRING &password
	);
	void doConnection( bool getRequest=true );

public:		// User declarations
	__fastcall ThttpForm(TComponent* Owner);
	__fastcall ~ThttpForm();
};
//---------------------------------------------------------------------------
extern PACKAGE ThttpForm *httpForm;
//---------------------------------------------------------------------------
#endif

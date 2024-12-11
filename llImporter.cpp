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

#include "importConsoleStatus.h"
#include "llImportThrd.h"
#include "DataUnit.h"

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
	const char	*daysToKeep = NULL;
	bool		ignoreErrors = false;

	if( argc>3 )
	{
		std::cerr << "usage: " << argv[0] << "[-i] [daysToKeep]\n";
	}
	else if( argc == 2 && argv[1][1] == '?' )
	{
		std::cout << "usage: " << argv[0] << "[-i] [daysToKeep]\n\n"
			 << "options: -i: ignore any errors\n";
	}
	else
	{
		ImportConsoleStatus	statusDisplay;
		if( argc >=2 )
		{
			if( !strcmp( argv[1], "-i" ) )
			{
				ignoreErrors = true;
				daysToKeep = argv[2];
			}
			else
				daysToKeep = argv[1];
		}
		if( !daysToKeep || !*daysToKeep )
			daysToKeep = "0";

		theDataModule = new TtheDataModule( NULL );

		theDataModule->openDatabase( "LL_IMPORT" );

		llImportThread *theThread = new llImportThread(
			false, ignoreErrors,
			atoi(daysToKeep) > 0, atoi(daysToKeep),
			&statusDisplay
		);

		theThread->WaitFor();

		theDataModule->llCheck_DB->Close();
	}

	return 0;
}
//---------------------------------------------------------------------------


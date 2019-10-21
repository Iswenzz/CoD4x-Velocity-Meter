#include "UI.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;

[STAThread]
int Main(array<String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew COD4::UI());
	return 0;
}

#include "MainForm.h"
#include "Box.h"
#include "Utils.h"

using namespace Bladestick::Drawing;
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^> ^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Bladestick::MainForm form;
	Application::Run(%form);
}

System::Void Bladestick::MainForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//Some debugging here
	zb->setSize(canvas->Width, canvas->Height);
	zb->clear();
	Random ^ rnd = gcnew Random();
	Geometry::Box ^ box = gcnew Geometry::Box(gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), Color::Orange);
	box->update();
	box->draw(zb);
	zb->render(g);
	return System::Void();
}

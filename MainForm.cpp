#include "MainForm.h"
#include "Box.h"

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
	zb->clearArea(ZBuffer::MAX_WIDTH, ZBuffer::MAX_HEIGHT);
	Random ^ rnd = gcnew Random();
	Geometry::Box ^ box = gcnew Geometry::Box(gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0), gcnew Geometry::Point(rnd->NextDouble() * canvas->Width, rnd->NextDouble() * canvas->Height, 0));
	box->update();
	box->draw(zb);
	zb->render(g, canvas->Width, canvas->Height);
	return System::Void();
}

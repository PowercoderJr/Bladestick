#include "MainForm.h"
#include "Utils.h"
#include "Matrix.h"
#include "Scene.h"

using namespace Bladestick::Drawing;
using namespace Bladestick;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Threading;
using namespace System;

[STAThreadAttribute]
void Main(array<String^> ^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MainForm form;
	Application::Run(%form);
}

MainForm::MainForm(void)
{
	InitializeComponent();
	scene = gcnew Drawing::Scene();
	autoApplyParamsChb->Checked = false;
	autoApplyInputs = false;
	selectionDependedControls = gcnew array<Control ^>(27)
	{
		deleteObjBtn, objPosX, objPosY, objPosZ,
			objRotX, objRotY, objRotZ,
			objScaleX, objScaleY, objScaleZ,
			color1Btn, color2Btn, color3Btn,
			handleLengthInput,
			handleRingsCountInput,
			handleEdgesCountInput,
			inBladeRadiusInput,
			exBladeRadiusInput,
			bladeThicknessInput,
			bladeEdgesCountInput,
			primarySpikeLengthInput,
			primarySpikeAngleInput,
			secondarySpikeLengthInput,
			secondarySpikeAngleInput,
			secondarySpikesCountInput,
			applyParamsBtn,
			setDefaultParamsBtn
	};
	setDefaultParamsBtn_Click(this, nullptr);
	this->color1Btn->Click += gcnew EventHandler(this, &MainForm::onObjParamChanged);
	this->color2Btn->Click += gcnew EventHandler(this, &MainForm::onObjParamChanged);
	this->color3Btn->Click += gcnew EventHandler(this, &MainForm::onObjParamChanged);
	this->secondarySpikesCountInput->ValueChanged += gcnew EventHandler(this, &MainForm::onObjParamChanged);
	this->fovInput->ValueChanged += gcnew EventHandler(this, &MainForm::onFrustumChanged);
	this->canvas->MouseWheel += gcnew MouseEventHandler(this, &MainForm::canvas_MouseWheel);
	this->canvas->KeyPress += gcnew KeyPressEventHandler(this, &MainForm::canvas_KeyPress);

	objectsListBox->DataSource = scene->objects;
	updateObjComboBoxes();
	objControllerPanel->Dock = ::DockStyle::Fill;
	cameraControllerPanel->Dock = ::DockStyle::Fill;
	renderControllerPanel->Dock = ::DockStyle::Fill;

	controllerPanelSwitch_Click(пультУправленияОбъектамиToolStripMenuItem, nullptr);
	g = canvas->CreateGraphics();

	redrawScene();
	autoApplyParamsChb->Checked = true;
	autoApplyInputs = true;

	isLMBDown = isRMBDown = false;
	isCursorShown = true;
}

Void MainForm::canvas_MouseWheel(Object ^ sender, MouseEventArgs ^ e)
{
	static const double SPEED = 50;
	if (e->Delta > 0 && (scene->camera->target - scene->camera->position)->getMagnitude() <= (SPEED + 1)) return;
	
	scene->camera->position -= scene->camera->backDir->scale(SPEED * Math::Sign(e->Delta));
	updateCameraTransformInputs();
	redrawScene();
}

Void MainForm::canvas_MouseClick(Object ^ sender, MouseEventArgs ^ e)
{
	canvas->Select();
}

Void MainForm::canvas_MouseDown(Object ^ sender, MouseEventArgs ^ e)
{
	if (e->Button == ::MouseButtons::Left || e->Button == ::MouseButtons::Right)
	{
		if (e->Button == ::MouseButtons::Left)
			isLMBDown = true;
		else if (e->Button == ::MouseButtons::Right)
			isRMBDown = true;

		pastMouseX = this->Cursor->Position.X;
		pastMouseY = this->Cursor->Position.Y;

		if (isCursorShown)
		{
			isCursorShown = false;
			System::Windows::Forms::Cursor::Hide();
		}
	}
}

Void MainForm::canvas_MouseMove(Object ^ sender, MouseEventArgs ^ e)
{
	if (isLMBDown || isRMBDown)
	{
		const int dx = this->Cursor->Position.X - pastMouseX;
		const int dy = - (this->Cursor->Position.Y - pastMouseY);

		const double DIST = (scene->camera->target - scene->camera->position)->getMagnitude();
		double currYaw = Vector3D::getAngleBetween(scene->camera->rightDir, Vector3D::RIGHT) + degToRad(90);
		if (scene->camera->target->x < scene->camera->position->x)
			currYaw = Math::PI - currYaw;
		double currPitch = Vector3D::getAngleBetween(scene->camera->upDir, Vector3D::UP);
		if (scene->camera->target->y < scene->camera->position->y)
			currPitch = -currPitch;

		const double SPEED = Math::PI / DIST;
		const double PITCH_RESTRICT = degToRad(89);
		if (isLMBDown)
		{
			double newYaw = -Math::PI + currYaw + dx * SPEED;
			double newPitch = currPitch + dy * SPEED;
			if (newPitch < -PITCH_RESTRICT)
				newPitch = -PITCH_RESTRICT;
			else if (newPitch > PITCH_RESTRICT)
				newPitch = PITCH_RESTRICT;
			Vector3D ^ buf = (gcnew Vector3D(Math::Cos(newYaw) * Math::Cos(newPitch),
				Math::Sin(newPitch), Math::Sin(newYaw) * Math::Cos(newPitch)))->
				normalized()->scale(DIST, DIST, DIST);
			scene->camera->target = scene->camera->position + buf;
		}
		else if (isRMBDown)
		{
			double newYaw = currYaw + dx * SPEED;
			double newPitch = -(currPitch + dy * SPEED);
			if (newPitch < -PITCH_RESTRICT)
				newPitch = -PITCH_RESTRICT;
			else if (newPitch > PITCH_RESTRICT)
				newPitch = PITCH_RESTRICT;
			Vector3D ^ buf = (gcnew Vector3D(Math::Cos(newYaw) * Math::Cos(newPitch),
				Math::Sin(newPitch), Math::Sin(newYaw) * Math::Cos(newPitch)))->
				normalized()->scale(DIST, DIST, DIST);
			scene->camera->position = scene->camera->target + buf;
		}

		this->Cursor->Position = Point(pastMouseX, pastMouseY);
		scene->camera->updateDirs();
		updateCameraTransformInputs();
		redrawScene();
	}
}

Void MainForm::canvas_MouseUp(Object ^ sender, MouseEventArgs ^ e)
{
	if (e->Button == ::MouseButtons::Left || e->Button == ::MouseButtons::Right)
	{
		if (e->Button == ::MouseButtons::Left)
			isLMBDown = false;
		else if (e->Button == ::MouseButtons::Right)
			isRMBDown = false;

		if (!(isLMBDown || isRMBDown))
		{
			System::Windows::Forms::Cursor::Show();
			isCursorShown = true;
		}
	}
}

Void MainForm::canvas_KeyPress(Object ^ sender, KeyPressEventArgs ^ e)
{
	bool modified = false;
	const double SPEED = 5.0;
	Vector3D ^ buf;
	char input = Char::ToUpper(e->KeyChar);
	List<char> ^ moving = gcnew List<char>(gcnew array<char>(12) { 'W', 'A', 'S', 'D', 'J', 'K', '8', '4', '2', '6', '+', '-' });
	if (moving->Contains(input))
	{
		switch (input)
		{
		case 'W':case '8':
			buf = scene->camera->upDir->scale(SPEED, SPEED, SPEED);
			break;
		case 'A':case '4':
			buf = scene->camera->rightDir->scale(-SPEED, -SPEED, -SPEED);
			break;
		case 'S':case '2':
			buf = scene->camera->upDir->scale(-SPEED, -SPEED, -SPEED);
			break;
		case 'D':case '6':
			buf = scene->camera->rightDir->scale(SPEED, SPEED, SPEED);
			break;
		case 'J':case '+':
			buf = scene->camera->backDir->scale(-SPEED, -SPEED, -SPEED);
			break;
		case 'K':case '-':
			buf = scene->camera->backDir->scale(SPEED, SPEED, SPEED);
			break;
		}
		scene->camera->position += buf;
		scene->camera->target += buf;
		modified = true;
	}
	else if (input == 'F')
	{
		buf = scene->camera->position->clone();
		scene->camera->position = scene->camera->target->clone();
		scene->camera->target = buf;
		modified = true;
	}

	if (modified)
	{
		scene->camera->updateDirs();
		updateCameraTransformInputs();
		redrawScene();
	}
}

Void MainForm::objectsListBox_DoubleClick(Object ^ sender, EventArgs ^ e)
{
	if (objectsListBox->SelectedItems->Count > 0)
	{
		Vector3D ^ objPos = safe_cast<SceneObject ^>(objectsListBox->SelectedItems[0])->offset->clone();

		if (cmpDoubles(objPos->x, scene->camera->position->x) == 0 && cmpDoubles(objPos->z, scene->camera->position->z) == 0)
			objPos = objPos->subtract(0, 0, 1);
		//MessageBox::Show("Координаты камеры и цели не должны совпадать", "Операция отклонена", ::MessageBoxButtons::OK, ::MessageBoxIcon::Exclamation);	

		scene->camera->target = objPos;
		scene->camera->updateDirs();
		updateCameraTransformInputs();
		redrawScene();
	}
}

Void MainForm::сохранитьToolStripMenuItem_Click(Object ^ sender, EventArgs ^ e)
{
	StreamWriter ^ fs;
	if (saveFileDialog->ShowDialog(this) == ::DialogResult::OK)
	{
		try
		{
			fs = gcnew StreamWriter(saveFileDialog->FileName);
			scene->saveToStream(fs);
			fs->Flush();
		}
		finally
		{
			fs->Close();
		}
	}
}

Void MainForm::загрузитьToolStripMenuItem_Click(Object ^ sender, EventArgs ^ e)
{
	FileStream ^ fs;
	if (openFileDialog->ShowDialog(this) == ::DialogResult::OK)
	{
		bool currAutoApplyInputs = autoApplyInputs;
		autoApplyInputs = false;
		try
		{
			fs = gcnew FileStream(openFileDialog->FileName, ::FileMode::Open);
			objectsListBox->ClearSelected();
			scene->loadFromStream(fs);
			scene->camera->updateDirs();
			updateCameraTransformInputs();
			updateObjComboBoxes();
			pProjectionRb->Checked = !scene->camera->perspective;
			cProjectionRb->Checked = scene->camera->perspective;
			nearPlaneInput->Value = Convert::ToDecimal(scene->camera->near);
			farPlaneInput->Value = Convert::ToDecimal(scene->camera->far);
			fovInput->Value = scene->camera->fov;
			sceneBgColorBtn->BackColor = scene->bgColor;
			edgesColorBtn->BackColor = scene->edgeColor;
			redrawScene();
		}
		catch (...)
		{
			MessageBox::Show(this, "Во время загрузки сцены произошла ошибка", "Ошибка", ::MessageBoxButtons::OK, ::MessageBoxIcon::Error);
		}
		finally
		{
			fs->Close();
			autoApplyInputs = currAutoApplyInputs;
		}
	}
}

Void MainForm::onDrawMethodChanged(Object ^ sender, EventArgs ^ e)
{
	if (autoApplyInputs)
		redrawScene();
}

Void MainForm::onProjectionTypeChanged(Object ^ sender, EventArgs ^ e)
{
	if (!((RadioButton ^)sender)->Checked) return;

	if (sender == pProjectionRb)
		scene->camera->perspective = false;
	else if (sender == cProjectionRb)
		scene->camera->perspective = true;

	if (autoApplyInputs)
		redrawScene();
}

Void MainForm::onFrustumChanged(Object ^ sender, EventArgs ^ e)
{
	if (sender == nearPlaneInput)
		scene->camera->near = Convert::ToDouble(nearPlaneInput->Value);
	else if (sender == farPlaneInput)
		scene->camera->far = Convert::ToDouble(farPlaneInput->Value);
	else if (sender == fovInput)
		scene->camera->fov = fovInput->Value;

	redrawScene();
}

Void MainForm::onPaletteBtnClicked(Object ^ sender, EventArgs ^ e)
{
	if (colorDialog->ShowDialog() == ::DialogResult::OK)
	{
		safe_cast<Button ^>(sender)->BackColor = colorDialog->Color;
		if (sender == sceneBgColorBtn)
			scene->bgColor = colorDialog->Color;
		else if (sender == edgesColorBtn)
			scene->edgeColor = colorDialog->Color;


		if (autoApplyInputs)
			redrawScene();
	}
}

Void MainForm::onFovInputValueChanged(Object ^ sender, EventArgs ^ e)
{
	fovLabel->Text = "" + fovInput->Value;
}

void MainForm::redrawScene()
{
	scene->setSize(canvas->Width, canvas->Height);
	scene->clear();
	char drawFlags = 0;
	if (drawEdgesChb->Checked)
		drawFlags |= DRAW_EDGES;
	if (drawFillChb->Checked)
		drawFlags |= DRAW_FILL;
	if (useRandomPaletteChb->Checked)
		drawFlags |= USE_RND_COLORS;
	if (simulateLightChb->Checked)
		drawFlags |= SIMULATE_LIGHT;
	scene->drawObjectsToBuffer(drawFlags);
	scene->render(g);
}

void MainForm::applyObjTransform(Object ^ sender)
{
	if (objectsListBox->SelectedItems->Count == 0)
		return;

	if (sender == objPosX)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->offset->x = Convert::ToDouble(objPosX->Value);
	else if (sender == objPosY)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->offset->y = Convert::ToDouble(objPosY->Value);
	else if (sender == objPosZ)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->offset->z = Convert::ToDouble(objPosZ->Value);
	else if (sender == objRotX)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->rotation->x = Convert::ToDouble(objRotX->Value);
	else if (sender == objRotY)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->rotation->y = Convert::ToDouble(objRotY->Value);
	else if (sender == objRotZ)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->rotation->z = Convert::ToDouble(objRotZ->Value);
	else if (sender == objScaleX)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->scaling->x = Convert::ToDouble(objScaleX->Value);
	else if (sender == objScaleY)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->scaling->y = Convert::ToDouble(objScaleY->Value);
	else if (sender == objScaleZ)
		for each (SceneObject ^ so in objectsListBox->SelectedItems)
			so->scaling->z = Convert::ToDouble(objScaleZ->Value);

	for each (SceneObject ^ so in objectsListBox->SelectedItems)
		so->transform();
}

void MainForm::applyObjParams()
{
	if (objectsListBox->SelectedItems->Count == 0)
		return;

	SceneObject ^ newSO = SceneObject::buildBladestick(Convert::ToDouble(handleLengthInput->Value),
		Convert::ToInt32(handleRingsCountInput->Value),
		Convert::ToInt32(handleEdgesCountInput->Value),
		Convert::ToDouble(inBladeRadiusInput->Value),
		Convert::ToDouble(exBladeRadiusInput->Value),
		Convert::ToInt32(bladeEdgesCountInput->Value),
		Convert::ToDouble(bladeThicknessInput->Value),
		Convert::ToDouble(primarySpikeLengthInput->Value),
		Convert::ToDouble(primarySpikeAngleInput->Value),
		Convert::ToDouble(secondarySpikeLengthInput->Value),
		Convert::ToDouble(secondarySpikeAngleInput->Value),
		Convert::ToInt32(secondarySpikesCountInput->Value * 4),
		gcnew array<Color>(3) { color1Btn->BackColor, color2Btn->BackColor, color3Btn->BackColor });

	SceneObject ^ so = safe_cast<SceneObject ^>(objectsListBox->SelectedItems[0]);
	so->vertices = newSO->vertices;
	so->indices = newSO->indices;
	so->normals = newSO->normals;
	so->colors = newSO->colors;
	so->transform();
}

bool MainForm::applyCameraTransform(Object ^ sender)
{
	double newPosX = scene->camera->position->x;
	double newPosY = scene->camera->position->y;
	double newPosZ = scene->camera->position->z;
	double newTargetX = scene->camera->target->x;
	double newTargetY = scene->camera->target->y;
	double newTargetZ = scene->camera->target->z;

	if (sender == cameraPosX)
		newPosX = Convert::ToDouble(cameraPosX->Value);
	else if (sender == cameraPosY)
		newPosY = Convert::ToDouble(cameraPosY->Value);
	else if (sender == cameraPosZ)
		newPosZ = Convert::ToDouble(cameraPosZ->Value);
	else if (sender == cameraTargetX)
		newTargetX = Convert::ToDouble(cameraTargetX->Value);
	else if (sender == cameraTargetY)
		newTargetY = Convert::ToDouble(cameraTargetY->Value);
	else if (sender == cameraTargetZ)
		newTargetZ = Convert::ToDouble(cameraTargetZ->Value);
	else if (sender == cameraYaw || sender == cameraPitch)
	{
		double dist = (scene->camera->target - scene->camera->position)->getMagnitude();
		double yaw = degToRad(Convert::ToDouble(cameraYaw->Value) - 90);
		double pitch = degToRad(Convert::ToDouble(cameraPitch->Value));
		double ox = Math::Cos(yaw) * Math::Cos(pitch) * dist;
		double oy = Math::Sin(pitch) * dist;
		double oz = Math::Sin(yaw) * Math::Cos(pitch) * dist;
		newTargetX = scene->camera->position->x + ox;
		newTargetY = scene->camera->position->y + oy;
		newTargetZ = scene->camera->position->z + oz;
	}

	if (cmpDoubles(newPosX, newTargetX) == 0 && cmpDoubles(newPosZ, newTargetZ) == 0)
		return false;
	else
	{
		scene->camera->position->x = newPosX;
		scene->camera->position->y = newPosY;
		scene->camera->position->z = newPosZ;
		scene->camera->target->x = newTargetX;
		scene->camera->target->y = newTargetY;
		scene->camera->target->z = newTargetZ;
		return true;
	}
	return true;
}

void MainForm::updateObjComboBoxes()
{
	SceneObject ^ tmp1 = nullptr;
	if (placeCameraRelativeCb->SelectedIndex > -1)
		tmp1 = safe_cast<SceneObject ^>(placeCameraRelativeCb->SelectedItem);
	BindingList<SceneObject ^> ^ list1 = gcnew BindingList<SceneObject ^>(scene->objects);
	placeCameraRelativeCb->DataSource = list1;
	if (tmp1 != nullptr && list1->Contains(tmp1))
		placeCameraRelativeCb->SelectedItem = tmp1;
	else
	{
		placeCameraRelativeCb->SelectedIndex = -1;
		placeCameraRelativeCb->Text = "";
		placeCameraRelativeBtn->Enabled = false;
		cameraRelativePosX->Enabled = false;
		cameraRelativePosY->Enabled = false;
		cameraRelativePosZ->Enabled = false;
	}

	SceneObject ^ tmp2 = nullptr;
	if (cameraLookAtCb->SelectedIndex > -1)
		tmp2 = safe_cast<SceneObject ^>(cameraLookAtCb->SelectedItem);
	BindingList<SceneObject ^> ^ list2 = gcnew BindingList<SceneObject ^>(scene->objects);
	cameraLookAtCb->DataSource = list2;
	if (tmp2 != nullptr && list2->Contains(tmp2))
		cameraLookAtCb->SelectedItem = tmp2;
	else
	{
		cameraLookAtCb->SelectedIndex = -1;
		cameraLookAtCb->Text = "";
		cameraLookAtBtn->Enabled = false;
	}
}

void MainForm::updateCameraTransformInputs()
{
	bool currAutoApplyInputs = autoApplyInputs;
	autoApplyInputs = false;

	cameraPosX->Value = Convert::ToDecimal(scene->camera->position->x);
	cameraPosY->Value = Convert::ToDecimal(scene->camera->position->y);
	cameraPosZ->Value = Convert::ToDecimal(scene->camera->position->z);

	cameraTargetX->Value = Convert::ToDecimal(scene->camera->target->x);
	cameraTargetY->Value = Convert::ToDecimal(scene->camera->target->y);
	cameraTargetZ->Value = Convert::ToDecimal(scene->camera->target->z);

	double yaw = radToDeg(Vector3D::getAngleBetween(scene->camera->rightDir, Vector3D::RIGHT));
	yaw = scene->camera->target->x < scene->camera->position->x ? -yaw : yaw;
	double pitch = radToDeg(Vector3D::getAngleBetween(scene->camera->upDir, Vector3D::UP));
	pitch = scene->camera->target->y < scene->camera->position->y ? -pitch : pitch;
	cameraYaw->Value = Convert::ToDecimal(yaw);
	cameraPitch->Value = Convert::ToDecimal(pitch);

	autoApplyInputs = currAutoApplyInputs;
}

Void MainForm::secondarySpikesCountInput_ValueChanged(Object ^ sender, EventArgs ^ e)
{
	secondarySpikesCountLabel->Text = "" + (secondarySpikesCountInput->Value * 4);
}

Void MainForm::createObjBtn_Click(Object ^ sender, EventArgs ^ e)
{
	SceneObject ^ so = SceneObject::buildBladestick(
		SceneObject::DEFAULT_HANDLE_LENGTH,
		SceneObject::DEFAULT_HANDLE_RINGS_COUNT,
		SceneObject::DEFAULT_HANDLE_EDGES_COUNT,
		SceneObject::DEFAULT_IN_BLADE_RADIUS,
		SceneObject::DEFAULT_EX_BLADE_RADIUS,
		SceneObject::DEFAULT_BLADE_EDGES_COUNT,
		SceneObject::DEFAULT_BLADE_THICKNESS,
		SceneObject::DEFAULT_PRIMARY_SPIKE_LENGTH,
		SceneObject::DEFAULT_PRIMARY_SPIKE_ANGLE,
		SceneObject::DEFAULT_SECONDARY_SPIKE_LENGTH,
		SceneObject::DEFAULT_SECONDARY_SPIKE_ANGLE,
		SceneObject::DEFAULT_SECONDARY_SPIKES_COUNT,
		gcnew array<Color>(3) { SceneObject::DEFAULT_COLOR_1, SceneObject::DEFAULT_COLOR_2, SceneObject::DEFAULT_COLOR_3}
	);
	so->name = "Объект #" + ++scene->objTotalCount;
	scene->objects->Add(so);
	objectsListBox->ClearSelected();
	objectsListBox->SelectedItem = so;

	updateObjComboBoxes();
	redrawScene();
}

Void MainForm::deleteObjBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (objectsListBox->SelectedItems->Count == 0)
		return;

	String ^ question = objectsListBox->SelectedItems->Count > 1 ?
		"Удалить выделенные объекты (" + objectsListBox->SelectedItems->Count + " шт.)?" :
		"Удалить " + ((SceneObject ^)objectsListBox->SelectedItem)->name + "?";
	if (MessageBox::Show(this, question, "Подтвердите операцию", MessageBoxButtons::YesNo, ::MessageBoxIcon::Question) == ::DialogResult::Yes)
	{
		Collections::Generic::List<SceneObject ^> ^ items = gcnew Collections::Generic::List<SceneObject ^>(objectsListBox->SelectedItems->Count);
		for (int i = 0; i < objectsListBox->SelectedItems->Count; ++i)
			items->Add(scene->objects[objectsListBox->SelectedIndices[i]]);
		for (int i = 0; i < items->Count; ++i)
			scene->objects->Remove(items[i]);
		objectsListBox->ClearSelected();
		updateObjComboBoxes();

		redrawScene();
	}
}

Void MainForm::clearObjBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (scene->objects->Count == 0) return;

	if (MessageBox::Show(this, "Очистить список объектов?", "Подтвердите операцию", MessageBoxButtons::YesNo, ::MessageBoxIcon::Question) == ::DialogResult::Yes)
	{
		scene->objects->Clear();
		updateObjComboBoxes();

		redrawScene();
	}
}

Void MainForm::colorBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (colorDialog->ShowDialog() == ::DialogResult::OK)
		safe_cast<Button ^>(sender)->BackColor = colorDialog->Color;
}

Void MainForm::onObjTransformationKeyPress(Object ^ sender, KeyPressEventArgs ^ e)
{
	if ((char)(e->KeyChar) == (char)Keys::Enter && autoApplyInputs) //Enter
	{
		applyObjTransform(sender);
		redrawScene();
	}
}

Void MainForm::canvas_Resize(Object ^ sender, EventArgs ^ e)
{
	g = canvas->CreateGraphics();
	redrawScene();
}

Void MainForm::обновитьToolStripMenuItem_Click(Object ^ sender, EventArgs ^ e)
{
	redrawScene();
}

Void MainForm::пересоздатьToolStripMenuItem_Click(Object ^ sender, EventArgs ^ e)
{

	if (MessageBox::Show(this, "Пересоздать сцену? Все объекты будут удалены, а камера будет установлена в исходное положение.", "Подтвердите операцию", MessageBoxButtons::YesNo, ::MessageBoxIcon::Question) == ::DialogResult::Yes)
	{
		scene->objects->Clear();
		updateObjComboBoxes();
		scene->camera->position = gcnew Vector3D(0, 0, 1000);
		scene->camera->target = gcnew Vector3D(0, 0, 0);
		scene->camera->updateDirs();
		updateCameraTransformInputs();

		redrawScene();
	}
}

Void MainForm::controllerPanelSwitch_Click(Object ^ sender, EventArgs ^ e)
{
	/*static*/ array<Panel ^> ^ controllerPanels = gcnew array<Panel ^>(3) 
		{ objControllerPanel, cameraControllerPanel, renderControllerPanel };

	int index = Convert::ToInt32(safe_cast<ToolStripMenuItem ^>(sender)->Tag);
	controllerPanels[index]->BringToFront();
	controllerPanels[index]->Visible = true;
}

Void MainForm::placeCameraRelativeCb_SelectedValueChanged(Object ^ sender, EventArgs ^ e)
{
	bool isAnySelected = placeCameraRelativeCb->SelectedIndex > -1;
	placeCameraRelativeBtn->Enabled = isAnySelected;
	cameraRelativePosX->Enabled = isAnySelected;
	cameraRelativePosY->Enabled = isAnySelected;
	cameraRelativePosZ->Enabled = isAnySelected;
}

Void MainForm::cameraLookAtCb_SelectedValueChanged(Object ^ sender, EventArgs ^ e)
{
	cameraLookAtBtn->Enabled = cameraLookAtCb->SelectedIndex > -1;
}

Void MainForm::placeCameraRelativeBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (placeCameraRelativeCb->SelectedIndex > -1)
	{
		Vector3D ^ objPos = safe_cast<SceneObject ^>(placeCameraRelativeCb->SelectedItem)->offset;
		Vector3D ^ offset = gcnew Vector3D(Convert::ToDouble(cameraRelativePosX->Value),
			Convert::ToDouble(cameraRelativePosY->Value), Convert::ToDouble(cameraRelativePosZ->Value));
		Vector3D ^ newCameraPos = objPos + offset;

		if (cmpDoubles(newCameraPos->x, scene->camera->target->x) == 0 && cmpDoubles(newCameraPos->z, scene->camera->target->z) == 0)
			newCameraPos = newCameraPos->add(0, 0, 1);
			//MessageBox::Show("Координаты камеры и цели не должны совпадать", "Операция отклонена", ::MessageBoxButtons::OK, ::MessageBoxIcon::Exclamation);
		
		scene->camera->position = newCameraPos;
		scene->camera->updateDirs();
		updateCameraTransformInputs();
		redrawScene();
	}
	else
	{
		MessageBox::Show("Выберите объект из списка", "Операция отклонена", ::MessageBoxButtons::OK, ::MessageBoxIcon::Exclamation);
	}
}

Void MainForm::cameraLookAtBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (cameraLookAtCb->SelectedIndex > -1)
	{
		Vector3D ^ objPos = safe_cast<SceneObject ^>(cameraLookAtCb->SelectedItem)->offset->clone();

		if (cmpDoubles(objPos->x, scene->camera->position->x) == 0 && cmpDoubles(objPos->z, scene->camera->position->z) == 0)
			objPos = objPos->subtract(0, 0, 1);
			//MessageBox::Show("Координаты камеры и цели не должны совпадать", "Операция отклонена", ::MessageBoxButtons::OK, ::MessageBoxIcon::Exclamation);	

		scene->camera->target = objPos;
		scene->camera->updateDirs();
		updateCameraTransformInputs();
		redrawScene();
	}
	else
	{
		MessageBox::Show("Выберите объект из списка", "Операция отклонена", ::MessageBoxButtons::OK, ::MessageBoxIcon::Exclamation);
	}
}

Void MainForm::onCameraTransformationChanged(Object ^ sender, EventArgs ^ e)
{
	if (autoApplyInputs)
	{
		if (applyCameraTransform(sender))
		{
			scene->camera->updateDirs();
			redrawScene();
		}
		else
			MessageBox::Show("Недопустимые параметры камеры", "Операция отклонена", ::MessageBoxButtons::OK, ::MessageBoxIcon::Exclamation);
		updateCameraTransformInputs();
	}
}

Void MainForm::onObjTransformationChanged(Object ^ sender, EventArgs ^ e)
{
	if (autoApplyInputs)
	{
		applyObjTransform(sender);
		redrawScene();
	}
}

Void MainForm::onObjParamChanged(Object ^ sender, EventArgs ^ e)
{
	if (autoApplyParamsChb->Checked)
	{
		applyObjParams();
		redrawScene();
	}
}

Void MainForm::objectsListBox_SelectedValueChanged(Object ^ sender, EventArgs ^ e)
{
	bool isAnySelected = objectsListBox->SelectedItems->Count > 0;
	for each (Control ^ control in selectionDependedControls)
		control->Enabled = isAnySelected;

	if (isAnySelected)
	{
		bool currAutoApplyInputs = autoApplyInputs;
		autoApplyInputs = false;
		
		SceneObject ^ obj = safe_cast<SceneObject ^>(objectsListBox->SelectedItems[0]);
		objPosX->Value = Convert::ToDecimal(obj->offset->x);
		objPosY->Value = Convert::ToDecimal(obj->offset->y);
		objPosZ->Value = Convert::ToDecimal(obj->offset->z);
		objRotX->Value = Convert::ToDecimal(obj->rotation->x);
		objRotY->Value = Convert::ToDecimal(obj->rotation->y);
		objRotZ->Value = Convert::ToDecimal(obj->rotation->z);
		objScaleX->Value = Convert::ToDecimal(obj->scaling->x);
		objScaleY->Value = Convert::ToDecimal(obj->scaling->y);
		objScaleZ->Value = Convert::ToDecimal(obj->scaling->z);

		autoApplyInputs = currAutoApplyInputs;

		objTransformGroup->Text = "Преобразования (" + obj->name + (objectsListBox->SelectedItems->Count > 1 ? " + ещё " + (objectsListBox->SelectedItems->Count - 1) + "шт." : "") + ")";
	}
	else
	{
		objTransformGroup->Text = "Преобразования (выберите объект)";
	}
}

Void MainForm::applyBtn_Click(Object ^ sender, EventArgs ^ e)
{
	applyObjParams();
	redrawScene();
}

Void MainForm::setDefaultParamsBtn_Click(Object ^ sender, EventArgs ^ e)
{
	bool autoApplyChecked = autoApplyParamsChb->Checked;
	autoApplyParamsChb->Checked = false;

	handleLengthInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_HANDLE_LENGTH);
	handleRingsCountInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_HANDLE_RINGS_COUNT);
	handleEdgesCountInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_HANDLE_EDGES_COUNT);
	inBladeRadiusInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_IN_BLADE_RADIUS);
	exBladeRadiusInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_EX_BLADE_RADIUS);
	bladeEdgesCountInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_BLADE_EDGES_COUNT);
	bladeThicknessInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_BLADE_THICKNESS);
	primarySpikeLengthInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_PRIMARY_SPIKE_LENGTH);
	primarySpikeAngleInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_PRIMARY_SPIKE_ANGLE);
	secondarySpikeLengthInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_SECONDARY_SPIKE_LENGTH);
	secondarySpikeAngleInput->Value = Convert::ToDecimal(SceneObject::DEFAULT_SECONDARY_SPIKE_ANGLE);
	secondarySpikesCountInput->Value = SceneObject::DEFAULT_SECONDARY_SPIKES_COUNT / 4;
	color1Btn->BackColor = SceneObject::DEFAULT_COLOR_1;
	color2Btn->BackColor = SceneObject::DEFAULT_COLOR_2;
	color3Btn->BackColor = SceneObject::DEFAULT_COLOR_3;
	
	autoApplyParamsChb->Checked = autoApplyChecked;
	if (autoApplyParamsChb->Checked)
	{
		applyObjParams();
		redrawScene();
	}
}

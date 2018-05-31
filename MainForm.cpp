#include "MainForm.h"
#include "Utils.h"
#include "Matrix.h"
#include "Scene.h"

using namespace Bladestick::Drawing;
using namespace Bladestick;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
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
	autoApplyTransform = true;
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
	this->color1Btn->Click += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
	this->color2Btn->Click += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
	this->color3Btn->Click += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
	this->secondarySpikesCountInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onObjParamChanged);
	this->fovInput->ValueChanged += gcnew System::EventHandler(this, &MainForm::onFrustumChanged);

	objectsListBox->DataSource = scene->objects;
	updateObjComboBoxes();
	objControllerPanel->Dock = ::DockStyle::Fill;
	cameraControllerPanel->Dock = ::DockStyle::Fill;
	renderControllerPanel->Dock = ::DockStyle::Fill;
	controllerPanelSwitch_Click(пультУправленияОбъектамиToolStripMenuItem, nullptr);
	g = canvas->CreateGraphics();
	redrawScene();
}

Void MainForm::MainForm_KeyPress(Object ^ sender, KeyPressEventArgs ^ e)
{
	//TODO
}

Void MainForm::onDrawMethodChanged(Object ^ sender, EventArgs ^ e)
{
	redrawScene();
}

Void MainForm::onProjectionTypeChanged(Object ^ sender, EventArgs ^ e)
{
	if (!((RadioButton ^)sender)->Checked) return;

	if (sender == pProjectionRb)
		scene->camera->perspective = false;
	else if (sender == cProjectionRb)
		scene->camera->perspective = true;

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
	}

	redrawScene();
}

Void MainForm::onFovInputValueChanged(Object ^ sender, EventArgs ^ e)
{
	fovLabel->Text = "" + fovInput->Value;
}

void MainForm::redrawScene()
{
	scene->setSize(canvas->Width, canvas->Height);
	scene->clear();
	//TODO: передавать аргументы в зависимости от настроек отрисовки
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
	if (!autoApplyTransform || objectsListBox->SelectedItems->Count == 0)
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

	redrawScene();
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

	redrawScene();
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
	cameraPosX->Value = Convert::ToDecimal(scene->camera->position->x);
	cameraPosY->Value = Convert::ToDecimal(scene->camera->position->y);
	cameraPosZ->Value = Convert::ToDecimal(scene->camera->position->z);

	cameraTargetX->Value = Convert::ToDecimal(scene->camera->target->x);
	cameraTargetY->Value = Convert::ToDecimal(scene->camera->target->y);
	cameraTargetZ->Value = Convert::ToDecimal(scene->camera->target->z);

	double yaw = radToDeg(Vector3D::getAngleBetween(scene->camera->rightDir, gcnew Vector3D(1, 0, 0)));
	yaw = scene->camera->target->x < scene->camera->position->x ? -yaw : yaw;
	double pitch = radToDeg(Vector3D::getAngleBetween(scene->camera->upDir, gcnew Vector3D(0, 1, 0)));
	pitch = scene->camera->target->y < scene->camera->position->y ? -pitch : pitch;
	cameraYaw->Value = Convert::ToDecimal(yaw);
	cameraPitch->Value = Convert::ToDecimal(pitch);
	//cameraRoll->Value = NEEDED?;
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
	if (MessageBox::Show(this, question, "Подтвердите операцию", MessageBoxButtons::YesNo) == ::DialogResult::Yes)
	{
		Collections::Generic::List<SceneObject ^> ^ items = gcnew Collections::Generic::List<SceneObject ^>(objectsListBox->SelectedItems->Count);
		for (int i = 0; i < objectsListBox->SelectedItems->Count; ++i)
			items->Add(scene->objects[objectsListBox->SelectedIndices[i]]);
		for (int i = 0; i < items->Count; ++i)
			scene->objects->Remove(items[i]);
		objectsListBox->ClearSelected();
		updateObjComboBoxes();
	}

	redrawScene();
}

Void MainForm::clearObjBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (scene->objects->Count == 0) return;

	if (MessageBox::Show(this, "Очистить список объектов?", "Подтвердите операцию", MessageBoxButtons::YesNo) == ::DialogResult::Yes)
	{
		scene->objects->Clear();
		updateObjComboBoxes();
	}

	redrawScene();
}

Void MainForm::colorBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (colorDialog->ShowDialog() == ::DialogResult::OK)
		safe_cast<Button ^>(sender)->BackColor = colorDialog->Color;
}

Void MainForm::onObjTransformationKeyPress(Object ^ sender, KeyPressEventArgs ^ e)
{
	if (e->KeyChar == 13 && autoApplyTransform) //Enter
		applyObjTransform(sender);		
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

Void MainForm::controllerPanelSwitch_Click(Object ^ sender, EventArgs ^ e)
{
	/*static*/ array<Panel ^> ^ controllerPanels = gcnew array<Panel ^>(3) 
		{ objControllerPanel, cameraControllerPanel, renderControllerPanel };

	for each (Panel ^ item in controllerPanels)
		item->SendToBack();

	int index = Convert::ToInt32(safe_cast<ToolStripMenuItem ^>(sender)->Tag);
	controllerPanels[index]->BringToFront();
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

		if (!newCameraPos->Equals(scene->camera->target))
		{
			scene->camera->position = newCameraPos;
			scene->camera->updateDirs();
			updateCameraTransformInputs();
			redrawScene();
		}
		else
		{
			MessageBox::Show("Координаты камеры и цели не должны совпадать", "Операция отклонена");
		}
	}
	else
	{
		MessageBox::Show("Выберите объект из списка", "Операция отклонена");
	}
}

Void MainForm::cameraLookAtBtn_Click(Object ^ sender, EventArgs ^ e)
{
	if (cameraLookAtCb->SelectedIndex > -1)
	{
		Vector3D ^ objPos = safe_cast<SceneObject ^>(cameraLookAtCb->SelectedItem)->offset;

		if (!objPos->Equals(scene->camera->position))
		{
			scene->camera->target = objPos;
			scene->camera->updateDirs();
			updateCameraTransformInputs();
			redrawScene();
		}
		else
		{
			MessageBox::Show("Координаты камеры и цели не должны совпадать", "Операция отклонена");
		}
	}
	else
	{
		MessageBox::Show("Выберите объект из списка", "Операция отклонена");
	}
}

Void MainForm::onCameraTransformationChanged(Object ^ sender, EventArgs ^ e)
{
	if (sender == cameraPosX)
		scene->camera->position->x = Convert::ToDouble(cameraPosX->Value);
	else if (sender == cameraPosY)
		scene->camera->position->y = Convert::ToDouble(cameraPosY->Value);
	else if (sender == cameraPosZ)
		scene->camera->position->z = Convert::ToDouble(cameraPosZ->Value);
	else if (sender == cameraTargetX)
		scene->camera->target->x = Convert::ToDouble(cameraTargetX->Value);
	else if (sender == cameraTargetY)
		scene->camera->target->y = Convert::ToDouble(cameraTargetY->Value);
	else if (sender == cameraTargetZ)
		scene->camera->target->z = Convert::ToDouble(cameraTargetZ->Value);
	/*TODO
	else if (sender == cameraRotX)
		
	else if (sender == cameraRotY)
		
	else if (sender == cameraRotZ)
	*/

	scene->camera->updateDirs();
	updateCameraTransformInputs();
	redrawScene();
}

Void MainForm::onObjTransformationChanged(Object ^ sender, EventArgs ^ e)
{
	if (autoApplyTransform)
		applyObjTransform(sender);
}

Void MainForm::onObjParamChanged(Object ^ sender, EventArgs ^ e)
{
	if (autoApplyParamsChb->Checked)
		applyObjParams();
}

Void MainForm::objectsListBox_SelectedValueChanged(Object ^ sender, EventArgs ^ e)
{
	bool isAnySelected = objectsListBox->SelectedItems->Count > 0;
	for each (Control ^ control in selectionDependedControls)
		control->Enabled = isAnySelected;

	if (isAnySelected)
	{
		bool currAutoApplyTransform = autoApplyTransform;
		autoApplyTransform = false;
		
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

		autoApplyTransform = currAutoApplyTransform;

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
		applyObjParams();
}

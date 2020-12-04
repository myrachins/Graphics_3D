#pragma once

#include "CanvasUtils.h"
#include "SceneFigures.h"

#include <msclr\marshal_cppstd.h>
#include <optional>

namespace Graphics3D {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	using Figures3D::Figure;
	using Figures3D::SceneFigures;

	using CanvasUtils::AutoPtr;
	using CanvasUtils::ApplicationSettings;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form {

	public:
		MyForm(void) {
			InitializeComponent();
			bm = gcnew Bitmap(pictureBox->Width, pictureBox->Height);
			scene_figures.Reset(std::make_unique<SceneFigures>(pictureBox->Width, pictureBox->Height));
			pictureBox->Image = bm;

			figureComboBox->SelectedIndex = 0;
			rotateComboBox->SelectedIndex = 0;
			shiftComboBox->SelectedIndex = 0;
			scaleComboBox->SelectedIndex = 0;
			projectionComboBox->SelectedIndex = 0;
			figuresVisibilityComboBox->SelectedIndex = 0;

			colorButton->BackColor = ApplicationSettings::GetDefaultColor();
			focusDistanceTextBox->Text = ApplicationSettings::GetFocusDistance().ToString();
			figureSizeTextBox->Text = ApplicationSettings::GetFiguresDefaultSize().ToString();

			ClearImage();
			SetEnabledForActions(false);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm() {
			if (components) {
				delete components;
			}
			scene_figures.Reset();
		}
	private: System::Windows::Forms::PictureBox^  pictureBox;

	private: System::Windows::Forms::GroupBox^  rotateGroupBox;
	private: System::Windows::Forms::Button^  minusAngleButton;
	private: System::Windows::Forms::Button^  plusAngleButton;
	private: System::Windows::Forms::ComboBox^  rotateComboBox;

	protected:
		Bitmap^ bm;
		AutoPtr<SceneFigures> scene_figures;
		double current_focus_distance;

	private: System::Windows::Forms::GroupBox^  utilsGroupBox;
	private: System::Windows::Forms::ComboBox^  projectionComboBox;
	private: System::Windows::Forms::GroupBox^  shiftGroupBox;
	private: System::Windows::Forms::Button^  negativeShiftButton;
	private: System::Windows::Forms::Button^  positiveShiftButton;

	private: System::Windows::Forms::ComboBox^  shiftComboBox;
	private: System::Windows::Forms::GroupBox^  scaleGroupBox;
	private: System::Windows::Forms::Button^  lessScaleButton;
	private: System::Windows::Forms::Button^  moreScaleButton;
	private: System::Windows::Forms::ComboBox^  scaleComboBox;
	private: System::Windows::Forms::Button^  resetButton;
	private: System::Windows::Forms::GroupBox^  projectionGroupBox;
	private: System::Windows::Forms::Label^  ZcLabel;
	private: System::Windows::Forms::TextBox^  focusDistanceTextBox;
	private: System::Windows::Forms::ComboBox^  figureComboBox;
	private: System::Windows::Forms::ComboBox^  figuresVisibilityComboBox;
	private: System::Windows::Forms::MenuStrip^  mainMenu;

	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::Label^  sizeLabel;
	private: System::Windows::Forms::TextBox^  figureSizeTextBox;
	private: System::Windows::Forms::GroupBox^  figuresGroupBox;
	private: System::Windows::Forms::Button^  addFigureButton;

	private: System::Windows::Forms::Button^  clearButton;
	private: System::Windows::Forms::Button^  saveFigureButton;
	private: System::Windows::Forms::GroupBox^  colorGroupBox;
	private: System::Windows::Forms::Button^  colorButton;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->rotateGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->rotateComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->plusAngleButton = (gcnew System::Windows::Forms::Button());
			this->minusAngleButton = (gcnew System::Windows::Forms::Button());
			this->utilsGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->saveFigureButton = (gcnew System::Windows::Forms::Button());
			this->clearButton = (gcnew System::Windows::Forms::Button());
			this->resetButton = (gcnew System::Windows::Forms::Button());
			this->sizeLabel = (gcnew System::Windows::Forms::Label());
			this->figureSizeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->figureComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->projectionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->shiftGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->shiftComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->positiveShiftButton = (gcnew System::Windows::Forms::Button());
			this->negativeShiftButton = (gcnew System::Windows::Forms::Button());
			this->scaleGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->scaleComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->moreScaleButton = (gcnew System::Windows::Forms::Button());
			this->lessScaleButton = (gcnew System::Windows::Forms::Button());
			this->projectionGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->figuresVisibilityComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ZcLabel = (gcnew System::Windows::Forms::Label());
			this->focusDistanceTextBox = (gcnew System::Windows::Forms::TextBox());
			this->mainMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->figuresGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->addFigureButton = (gcnew System::Windows::Forms::Button());
			this->colorGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->colorButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->rotateGroupBox->SuspendLayout();
			this->utilsGroupBox->SuspendLayout();
			this->shiftGroupBox->SuspendLayout();
			this->scaleGroupBox->SuspendLayout();
			this->projectionGroupBox->SuspendLayout();
			this->mainMenu->SuspendLayout();
			this->figuresGroupBox->SuspendLayout();
			this->colorGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(12, 83);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1514, 587);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			// 
			// rotateGroupBox
			// 
			this->rotateGroupBox->Controls->Add(this->rotateComboBox);
			this->rotateGroupBox->Controls->Add(this->plusAngleButton);
			this->rotateGroupBox->Controls->Add(this->minusAngleButton);
			this->rotateGroupBox->Location = System::Drawing::Point(12, 27);
			this->rotateGroupBox->Name = L"rotateGroupBox";
			this->rotateGroupBox->Size = System::Drawing::Size(212, 50);
			this->rotateGroupBox->TabIndex = 2;
			this->rotateGroupBox->TabStop = false;
			this->rotateGroupBox->Text = L"Rotate";
			// 
			// rotateComboBox
			// 
			this->rotateComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->rotateComboBox->FormattingEnabled = true;
			this->rotateComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"X", L"Y", L"Z" });
			this->rotateComboBox->Location = System::Drawing::Point(168, 21);
			this->rotateComboBox->Name = L"rotateComboBox";
			this->rotateComboBox->Size = System::Drawing::Size(35, 21);
			this->rotateComboBox->TabIndex = 2;
			// 
			// plusAngleButton
			// 
			this->plusAngleButton->Location = System::Drawing::Point(87, 19);
			this->plusAngleButton->Name = L"plusAngleButton";
			this->plusAngleButton->Size = System::Drawing::Size(75, 23);
			this->plusAngleButton->TabIndex = 1;
			this->plusAngleButton->Text = L"Plus angle";
			this->plusAngleButton->UseVisualStyleBackColor = true;
			this->plusAngleButton->Click += gcnew System::EventHandler(this, &MyForm::plusAngleButton_Click);
			// 
			// minusAngleButton
			// 
			this->minusAngleButton->Location = System::Drawing::Point(6, 19);
			this->minusAngleButton->Name = L"minusAngleButton";
			this->minusAngleButton->Size = System::Drawing::Size(75, 23);
			this->minusAngleButton->TabIndex = 0;
			this->minusAngleButton->Text = L"Minus angle";
			this->minusAngleButton->UseVisualStyleBackColor = true;
			this->minusAngleButton->Click += gcnew System::EventHandler(this, &MyForm::minusAngleButton_Click);
			// 
			// utilsGroupBox
			// 
			this->utilsGroupBox->Controls->Add(this->saveFigureButton);
			this->utilsGroupBox->Controls->Add(this->clearButton);
			this->utilsGroupBox->Controls->Add(this->resetButton);
			this->utilsGroupBox->Location = System::Drawing::Point(1269, 27);
			this->utilsGroupBox->Name = L"utilsGroupBox";
			this->utilsGroupBox->Size = System::Drawing::Size(257, 50);
			this->utilsGroupBox->TabIndex = 3;
			this->utilsGroupBox->TabStop = false;
			this->utilsGroupBox->Text = L"Utils";
			// 
			// saveFigureButton
			// 
			this->saveFigureButton->Location = System::Drawing::Point(90, 16);
			this->saveFigureButton->Name = L"saveFigureButton";
			this->saveFigureButton->Size = System::Drawing::Size(75, 23);
			this->saveFigureButton->TabIndex = 3;
			this->saveFigureButton->Text = L"Save figure";
			this->saveFigureButton->UseVisualStyleBackColor = true;
			this->saveFigureButton->Click += gcnew System::EventHandler(this, &MyForm::saveFigureButton_Click);
			// 
			// clearButton
			// 
			this->clearButton->Location = System::Drawing::Point(171, 16);
			this->clearButton->Name = L"clearButton";
			this->clearButton->Size = System::Drawing::Size(75, 23);
			this->clearButton->TabIndex = 2;
			this->clearButton->Text = L"Clear";
			this->clearButton->UseVisualStyleBackColor = true;
			this->clearButton->Click += gcnew System::EventHandler(this, &MyForm::clearButton_Click);
			// 
			// resetButton
			// 
			this->resetButton->Location = System::Drawing::Point(9, 16);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(75, 23);
			this->resetButton->TabIndex = 1;
			this->resetButton->Text = L"Reset";
			this->resetButton->UseVisualStyleBackColor = true;
			this->resetButton->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);
			// 
			// sizeLabel
			// 
			this->sizeLabel->AutoSize = true;
			this->sizeLabel->Location = System::Drawing::Point(6, 23);
			this->sizeLabel->Name = L"sizeLabel";
			this->sizeLabel->Size = System::Drawing::Size(30, 13);
			this->sizeLabel->TabIndex = 4;
			this->sizeLabel->Text = L"Size:";
			// 
			// figureSizeTextBox
			// 
			this->figureSizeTextBox->Location = System::Drawing::Point(42, 19);
			this->figureSizeTextBox->Name = L"figureSizeTextBox";
			this->figureSizeTextBox->Size = System::Drawing::Size(36, 20);
			this->figureSizeTextBox->TabIndex = 3;
			this->figureSizeTextBox->TextChanged += gcnew System::EventHandler(this, &MyForm::figureSizeTextBox_TextChanged);
			// 
			// figureComboBox
			// 
			this->figureComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->figureComboBox->FormattingEnabled = true;
			this->figureComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"Hexahedron", L"Tetrahedron", L"Octahedron",
					L"Icosahedron", L"Dodecahedron", L"Sphere", L"Torus", L"Garlic", L"From file"
			});
			this->figureComboBox->Location = System::Drawing::Point(84, 18);
			this->figureComboBox->Name = L"figureComboBox";
			this->figureComboBox->Size = System::Drawing::Size(92, 21);
			this->figureComboBox->TabIndex = 2;
			// 
			// projectionComboBox
			// 
			this->projectionComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->projectionComboBox->FormattingEnabled = true;
			this->projectionComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Perspective", L"Orthogonal" });
			this->projectionComboBox->Location = System::Drawing::Point(76, 18);
			this->projectionComboBox->Name = L"projectionComboBox";
			this->projectionComboBox->Size = System::Drawing::Size(89, 21);
			this->projectionComboBox->TabIndex = 0;
			this->projectionComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::projectionComboBox_SelectedIndexChanged);
			// 
			// shiftGroupBox
			// 
			this->shiftGroupBox->Controls->Add(this->shiftComboBox);
			this->shiftGroupBox->Controls->Add(this->positiveShiftButton);
			this->shiftGroupBox->Controls->Add(this->negativeShiftButton);
			this->shiftGroupBox->Location = System::Drawing::Point(230, 27);
			this->shiftGroupBox->Name = L"shiftGroupBox";
			this->shiftGroupBox->Size = System::Drawing::Size(209, 50);
			this->shiftGroupBox->TabIndex = 4;
			this->shiftGroupBox->TabStop = false;
			this->shiftGroupBox->Text = L"Shift";
			// 
			// shiftComboBox
			// 
			this->shiftComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->shiftComboBox->FormattingEnabled = true;
			this->shiftComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"X", L"Y", L"Z" });
			this->shiftComboBox->Location = System::Drawing::Point(170, 20);
			this->shiftComboBox->Name = L"shiftComboBox";
			this->shiftComboBox->Size = System::Drawing::Size(33, 21);
			this->shiftComboBox->TabIndex = 2;
			// 
			// positiveShiftButton
			// 
			this->positiveShiftButton->Location = System::Drawing::Point(88, 18);
			this->positiveShiftButton->Name = L"positiveShiftButton";
			this->positiveShiftButton->Size = System::Drawing::Size(75, 23);
			this->positiveShiftButton->TabIndex = 1;
			this->positiveShiftButton->Text = L"Positive";
			this->positiveShiftButton->UseVisualStyleBackColor = true;
			this->positiveShiftButton->Click += gcnew System::EventHandler(this, &MyForm::positiveShiftButton_Click);
			// 
			// negativeShiftButton
			// 
			this->negativeShiftButton->Location = System::Drawing::Point(7, 18);
			this->negativeShiftButton->Name = L"negativeShiftButton";
			this->negativeShiftButton->Size = System::Drawing::Size(75, 23);
			this->negativeShiftButton->TabIndex = 0;
			this->negativeShiftButton->Text = L"Negative shift";
			this->negativeShiftButton->UseVisualStyleBackColor = true;
			this->negativeShiftButton->Click += gcnew System::EventHandler(this, &MyForm::negativeShiftButton_Click);
			// 
			// scaleGroupBox
			// 
			this->scaleGroupBox->Controls->Add(this->scaleComboBox);
			this->scaleGroupBox->Controls->Add(this->moreScaleButton);
			this->scaleGroupBox->Controls->Add(this->lessScaleButton);
			this->scaleGroupBox->Location = System::Drawing::Point(445, 27);
			this->scaleGroupBox->Name = L"scaleGroupBox";
			this->scaleGroupBox->Size = System::Drawing::Size(215, 50);
			this->scaleGroupBox->TabIndex = 5;
			this->scaleGroupBox->TabStop = false;
			this->scaleGroupBox->Text = L"Scale";
			// 
			// scaleComboBox
			// 
			this->scaleComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->scaleComboBox->FormattingEnabled = true;
			this->scaleComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"All", L"X", L"Y", L"Z" });
			this->scaleComboBox->Location = System::Drawing::Point(170, 19);
			this->scaleComboBox->Name = L"scaleComboBox";
			this->scaleComboBox->Size = System::Drawing::Size(39, 21);
			this->scaleComboBox->TabIndex = 2;
			// 
			// moreScaleButton
			// 
			this->moreScaleButton->Location = System::Drawing::Point(88, 17);
			this->moreScaleButton->Name = L"moreScaleButton";
			this->moreScaleButton->Size = System::Drawing::Size(75, 23);
			this->moreScaleButton->TabIndex = 1;
			this->moreScaleButton->Text = L"More";
			this->moreScaleButton->UseVisualStyleBackColor = true;
			this->moreScaleButton->Click += gcnew System::EventHandler(this, &MyForm::moreScaleButton_Click);
			// 
			// lessScaleButton
			// 
			this->lessScaleButton->Location = System::Drawing::Point(7, 17);
			this->lessScaleButton->Name = L"lessScaleButton";
			this->lessScaleButton->Size = System::Drawing::Size(75, 23);
			this->lessScaleButton->TabIndex = 0;
			this->lessScaleButton->Text = L"Less";
			this->lessScaleButton->UseVisualStyleBackColor = true;
			this->lessScaleButton->Click += gcnew System::EventHandler(this, &MyForm::lessScaleButton_Click);
			// 
			// projectionGroupBox
			// 
			this->projectionGroupBox->Controls->Add(this->figuresVisibilityComboBox);
			this->projectionGroupBox->Controls->Add(this->ZcLabel);
			this->projectionGroupBox->Controls->Add(this->focusDistanceTextBox);
			this->projectionGroupBox->Controls->Add(this->projectionComboBox);
			this->projectionGroupBox->Location = System::Drawing::Point(718, 27);
			this->projectionGroupBox->Name = L"projectionGroupBox";
			this->projectionGroupBox->Size = System::Drawing::Size(272, 50);
			this->projectionGroupBox->TabIndex = 6;
			this->projectionGroupBox->TabStop = false;
			this->projectionGroupBox->Text = L"Projection";
			// 
			// figuresVisibilityComboBox
			// 
			this->figuresVisibilityComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->figuresVisibilityComboBox->FormattingEnabled = true;
			this->figuresVisibilityComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Roberts", L"Z algo", L"Whole figures" });
			this->figuresVisibilityComboBox->Location = System::Drawing::Point(171, 18);
			this->figuresVisibilityComboBox->Name = L"figuresVisibilityComboBox";
			this->figuresVisibilityComboBox->Size = System::Drawing::Size(95, 21);
			this->figuresVisibilityComboBox->TabIndex = 3;
			this->figuresVisibilityComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::figuresVisibilityComboBox_SelectedIndexChanged);
			// 
			// ZcLabel
			// 
			this->ZcLabel->AutoSize = true;
			this->ZcLabel->Location = System::Drawing::Point(6, 22);
			this->ZcLabel->Name = L"ZcLabel";
			this->ZcLabel->Size = System::Drawing::Size(23, 13);
			this->ZcLabel->TabIndex = 2;
			this->ZcLabel->Text = L"Zc:";
			// 
			// focusDistanceTextBox
			// 
			this->focusDistanceTextBox->Location = System::Drawing::Point(32, 19);
			this->focusDistanceTextBox->Name = L"focusDistanceTextBox";
			this->focusDistanceTextBox->Size = System::Drawing::Size(38, 20);
			this->focusDistanceTextBox->TabIndex = 1;
			this->focusDistanceTextBox->TextChanged += gcnew System::EventHandler(this, &MyForm::focusDistanceTextBox_TextChanged);
			// 
			// mainMenu
			// 
			this->mainMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->mainMenu->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->mainMenu->Location = System::Drawing::Point(0, 0);
			this->mainMenu->Name = L"mainMenu";
			this->mainMenu->Size = System::Drawing::Size(1539, 24);
			this->mainMenu->TabIndex = 7;
			this->mainMenu->Text = L"mainMenu";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::aboutToolStripMenuItem_Click);
			// 
			// figuresGroupBox
			// 
			this->figuresGroupBox->Controls->Add(this->addFigureButton);
			this->figuresGroupBox->Controls->Add(this->figureComboBox);
			this->figuresGroupBox->Controls->Add(this->figureSizeTextBox);
			this->figuresGroupBox->Controls->Add(this->sizeLabel);
			this->figuresGroupBox->Location = System::Drawing::Point(996, 27);
			this->figuresGroupBox->Name = L"figuresGroupBox";
			this->figuresGroupBox->Size = System::Drawing::Size(267, 50);
			this->figuresGroupBox->TabIndex = 8;
			this->figuresGroupBox->TabStop = false;
			this->figuresGroupBox->Text = L"Figures";
			// 
			// addFigureButton
			// 
			this->addFigureButton->Location = System::Drawing::Point(182, 17);
			this->addFigureButton->Name = L"addFigureButton";
			this->addFigureButton->Size = System::Drawing::Size(75, 23);
			this->addFigureButton->TabIndex = 5;
			this->addFigureButton->Text = L"Add Figure";
			this->addFigureButton->UseVisualStyleBackColor = true;
			this->addFigureButton->Click += gcnew System::EventHandler(this, &MyForm::addFigureButton_Click);
			// 
			// colorGroupBox
			// 
			this->colorGroupBox->Controls->Add(this->colorButton);
			this->colorGroupBox->Location = System::Drawing::Point(666, 27);
			this->colorGroupBox->Name = L"colorGroupBox";
			this->colorGroupBox->Size = System::Drawing::Size(46, 50);
			this->colorGroupBox->TabIndex = 9;
			this->colorGroupBox->TabStop = false;
			this->colorGroupBox->Text = L"Color";
			// 
			// colorButton
			// 
			this->colorButton->Location = System::Drawing::Point(6, 18);
			this->colorButton->Name = L"colorButton";
			this->colorButton->Size = System::Drawing::Size(34, 23);
			this->colorButton->TabIndex = 0;
			this->colorButton->UseVisualStyleBackColor = true;
			this->colorButton->Click += gcnew System::EventHandler(this, &MyForm::colorButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1539, 682);
			this->Controls->Add(this->colorGroupBox);
			this->Controls->Add(this->figuresGroupBox);
			this->Controls->Add(this->projectionGroupBox);
			this->Controls->Add(this->scaleGroupBox);
			this->Controls->Add(this->utilsGroupBox);
			this->Controls->Add(this->shiftGroupBox);
			this->Controls->Add(this->rotateGroupBox);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->mainMenu);
			this->MainMenuStrip = this->mainMenu;
			this->Name = L"MyForm";
			this->Text = L"Rachinskiy, Task #6";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->rotateGroupBox->ResumeLayout(false);
			this->utilsGroupBox->ResumeLayout(false);
			this->shiftGroupBox->ResumeLayout(false);
			this->scaleGroupBox->ResumeLayout(false);
			this->projectionGroupBox->ResumeLayout(false);
			this->projectionGroupBox->PerformLayout();
			this->mainMenu->ResumeLayout(false);
			this->mainMenu->PerformLayout();
			this->figuresGroupBox->ResumeLayout(false);
			this->figuresGroupBox->PerformLayout();
			this->colorGroupBox->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void minusAngleButton_Click(System::Object^  sender, System::EventArgs^  e) {
			RotateFigure(GetCurrentFigure(), -ApplicationSettings::GetRotateAngle());
		}
		private: System::Void plusAngleButton_Click(System::Object^  sender, System::EventArgs^  e) {
			RotateFigure(GetCurrentFigure(), ApplicationSettings::GetRotateAngle());
		}

		private: System::Void negativeShiftButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ShiftFigure(GetCurrentFigure(), -ApplicationSettings::GetShiftDelta());
		}
		private: System::Void positiveShiftButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ShiftFigure(GetCurrentFigure(), ApplicationSettings::GetShiftDelta());
		}

		private: System::Void lessScaleButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ScaleFigure(GetCurrentFigure(), 1 / ApplicationSettings::GetScale());
		}
		private: System::Void moreScaleButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ScaleFigure(GetCurrentFigure(), ApplicationSettings::GetScale());
		}

		private: System::Void focusDistanceTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			double new_focus_distance = 0;
			if (Double::TryParse(focusDistanceTextBox->Text, new_focus_distance)
				&& new_focus_distance > 0 && new_focus_distance != 1) {
				focusDistanceTextBox->BackColor = Color::White;
				current_focus_distance = new_focus_distance;
				for (Figure& figure : scene_figures->GetFigures()) {
					figure.SetFocusDistance(current_focus_distance);
				}
				UpdateFiguresView();
			} else {
				focusDistanceTextBox->BackColor = Color::Red;
			}
		}

		private: System::Void figureSizeTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			bool is_figure_size_correct = IsFigureSizeCorrect();
			figureSizeTextBox->BackColor = is_figure_size_correct ? Color::White : Color::Red;
			addFigureButton->Enabled = is_figure_size_correct;
		}

		private: System::Void projectionComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			UpdateFiguresView();
		}
		private: System::Void figuresVisibilityComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			UpdateFiguresView();
		}

		private: System::Void clearButton_Click(System::Object^  sender, System::EventArgs^  e) {
			SetEnabledForActions(false);
			scene_figures->GetFigures().clear();
			ClearImage();
		}
		private: System::Void resetButton_Click(System::Object^  sender, System::EventArgs^  e) {
			if (!scene_figures->GetFigures().empty()) {
				std::optional<Figure> new_figure = CreateFigure(ApplicationSettings::GetFiguresDefaultSize());
				if (new_figure) {
					scene_figures->GetFigures().pop_back();
					scene_figures->GetFigures().push_back(*new_figure);
					UpdateFiguresView();
				}
			}
		}
		private: System::Void addFigureButton_Click(System::Object^  sender, System::EventArgs^  e) {
			std::optional<Figure> new_figure = CreateFigure(Double::Parse(figureSizeTextBox->Text));
			if (new_figure) {
				scene_figures->GetFigures().push_back(*new_figure);
				UpdateFiguresView();
				SetEnabledForActions(true);
			}
		}

		private: System::Void colorButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ColorDialog^ color_dialog = gcnew ColorDialog();

			if (color_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				colorButton->BackColor = color_dialog->Color;
				GetCurrentFigure().SetFigureColor(color_dialog->Color);
				UpdateFiguresView();
			}
		}

	protected:
		void ClearImage() {
			Graphics^ g = Graphics::FromImage(bm);
			try {
				g->Clear(Color::White);
			} finally {
				delete g;
			}
			pictureBox->Refresh();
		}

		Figure& GetCurrentFigure() {
			return scene_figures->GetFigures().back();
		}

		std::optional<Figure> CreateFigure(double figure_size) {
			String^ mode = (String^)figureComboBox->SelectedItem;
			Figures3D::FuguresFabric fabric(
				colorButton->BackColor,
				ApplicationSettings::GetCanvasScale(),
				pictureBox->Width / 2, pictureBox->Height / 2,
				current_focus_distance,
				ApplicationSettings::GetCameraDistance());

			if (mode == "Hexahedron") {
				return fabric.CreateHexahedron(figure_size);
			}
			else if (mode == "Tetrahedron") {
				return fabric.CreateTetrahedron(figure_size);
			}
			else if (mode == "Octahedron") {
				return fabric.CreateOctahedron(figure_size);
			}
			else if (mode == "Icosahedron") {
				return fabric.CreateIcosahedron(figure_size);
			}
			else if (mode == "Dodecahedron") {
				return fabric.CreateDodecahedron(figure_size);
			}
			else if (mode == "Sphere") {
				return fabric.CreateSphere(figure_size);
			}
			else if (mode == "Torus") {
				return fabric.CreateTorus(figure_size, figure_size / 2);
			}
			else if (mode == "Garlic") {
				return fabric.CreateGarlic(figure_size);
			}
			else if (mode == "From file") {
				std::optional<std::string> file_name = GetFileNameFromDialog();
				if (!file_name.has_value()) {
					return std::nullopt;
				}
				try {
					return fabric.CreateFromFile(*file_name);
				} catch (const std::runtime_error&) {
					MessageBox::Show("Can't open file", "Error");
					return std::nullopt;
				}
			}
			return std::nullopt;
		}

		void UpdateFiguresView() {
			ClearImage();
			String^ projection_mode = (String^)projectionComboBox->SelectedItem;
			String^ visibility_mode = (String^)figuresVisibilityComboBox->SelectedItem;
			bool is_perspective_mode = projection_mode == "Perspective";
			if (visibility_mode == "Whole figures") {
				if (is_perspective_mode) {
					scene_figures->TakePerspectiveProjection(bm);
				} else {
					scene_figures->TakeOrthogonalProjection(bm);
				}
			} else if (visibility_mode == "Roberts") {
				if (is_perspective_mode) {
					scene_figures->TakePerspectiveProjectionRobertsAlgo(bm);
				} else {
					scene_figures->TakeOrthogonalProjectionRobertsAlgo(bm);
				}
			} else if (visibility_mode == "Z algo") {
				if (is_perspective_mode) {
					scene_figures->TakePerspectiveProjectionZAlgo(bm);
				} else {
					scene_figures->TakeOrthogonalProjectionZAlgo(bm);
				}
			}
			pictureBox->Refresh();
		}

		bool IsFigureSizeCorrect() {
			double new_figure_size = 0;

			return Double::TryParse(figureSizeTextBox->Text, new_figure_size) && new_figure_size > 0;
		}

		void RotateFigure(Figures3D::Figure& figure, double angle) {
			String^ mode = (String^)rotateComboBox->SelectedItem;
			if (mode == "X") {
				figure.RotateX(angle);
			} else if (mode == "Y") {
				figure.RotateY(angle);
			} else if (mode == "Z") {
				figure.RotateZ(angle);
			}
			UpdateFiguresView();
		}

		void ShiftFigure(Figures3D::Figure& figure, double delta) {
			String^ mode = (String^)shiftComboBox->SelectedItem;
			if (mode == "X") {
				figure.Shift(delta, 0, 0);
			} else if (mode == "Y") {
				figure.Shift(0, delta, 0);
			} else if (mode == "Z") {
				figure.Shift(0, 0, delta);
			}
			UpdateFiguresView();
		}

		void ScaleFigure(Figures3D::Figure& figure, double scale) {
			String^ mode = (String^)scaleComboBox->SelectedItem;
			if (mode == "X") {
				figure.Scale(scale, 1, 1, 1);
			} else if (mode == "Y") {
				figure.Scale(1, scale, 1, 1);
			} else if (mode == "Z") {
				figure.Scale(1, 1, scale, 1);
			} else if (mode == "All") {
				figure.Scale(1, 1, 1, scale);
			}
			UpdateFiguresView();
		}

		void SetEnabledForActions(bool enabled) {
			minusAngleButton->Enabled = enabled;
			plusAngleButton->Enabled = enabled;
			rotateComboBox->Enabled = enabled;

			negativeShiftButton->Enabled = enabled;
			positiveShiftButton->Enabled = enabled;
			shiftComboBox->Enabled = enabled;

			lessScaleButton->Enabled = enabled;
			moreScaleButton->Enabled = enabled;
			scaleComboBox->Enabled = enabled;

			focusDistanceTextBox->Enabled = enabled;
			projectionComboBox->Enabled = enabled;
			figuresVisibilityComboBox->Enabled = enabled;

			colorButton->Enabled = enabled;

			resetButton->Enabled = enabled;
			saveFigureButton->Enabled = enabled;
		}

		std::optional<std::string> GetFileNameFromDialog() {
			OpenFileDialog^ open_file_dialog = gcnew OpenFileDialog();
			open_file_dialog->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";

			if (open_file_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				return msclr::interop::marshal_as<std::string>(open_file_dialog->FileName);
			}
			return std::nullopt;
		}

		private: System::Void saveFigureButton_Click(System::Object^  sender, System::EventArgs^  e) {
			SaveFileDialog^ save_file_dialog = gcnew SaveFileDialog();
			save_file_dialog->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";

			try {
				if (save_file_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					GetCurrentFigure().SaveToFile(msclr::interop::marshal_as<std::string>(save_file_dialog->FileName));
				}
			} catch(const std::runtime_error&) {
				MessageBox::Show("Can't write to this file", "Error");
			}
		}

		private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			String^ info = "Info";
			String^ message = "This is homework #6. Date: 26/11/2020.\n"
				"Задание: Платоновы тела\n"
				"Author: Maxim Rachinskiy. OS: Windows 10\n"
				"IDE: VS 2017, C++ 17";

			MessageBox::Show(message, info);
		}
};
}

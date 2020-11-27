#pragma once

#include "Figures.h"
#include "CanvasUtils.h"

namespace Graphics2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
			pictureBox->Image = bm;

			figureComboBox->SelectedIndex = 0;
			rotateComboBox->SelectedIndex = 0;
			shiftComboBox->SelectedIndex = 0;
			scaleComboBox->SelectedIndex = 0;
			projectionComboBox->SelectedIndex = 0;

			ResetFigure();
			UpdateFigureView(*current_figure);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm() {
			if (components) {
				delete components;
			}
			current_figure.Reset();
		}
	private: System::Windows::Forms::PictureBox^  pictureBox;

	private: System::Windows::Forms::GroupBox^  rotateGroupBox;
	private: System::Windows::Forms::Button^  minusAngleButton;
	private: System::Windows::Forms::Button^  plusAngleButton;
	private: System::Windows::Forms::ComboBox^  rotateComboBox;

	protected:
		Bitmap^ bm;
		AutoPtr<Figures3D::Figure> current_figure;

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
			this->figureComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->resetButton = (gcnew System::Windows::Forms::Button());
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
			this->ZcLabel = (gcnew System::Windows::Forms::Label());
			this->focusDistanceTextBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->rotateGroupBox->SuspendLayout();
			this->utilsGroupBox->SuspendLayout();
			this->shiftGroupBox->SuspendLayout();
			this->scaleGroupBox->SuspendLayout();
			this->projectionGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(12, 64);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1028, 469);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			// 
			// rotateGroupBox
			// 
			this->rotateGroupBox->Controls->Add(this->rotateComboBox);
			this->rotateGroupBox->Controls->Add(this->plusAngleButton);
			this->rotateGroupBox->Controls->Add(this->minusAngleButton);
			this->rotateGroupBox->Location = System::Drawing::Point(12, 8);
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
			this->utilsGroupBox->Controls->Add(this->figureComboBox);
			this->utilsGroupBox->Controls->Add(this->resetButton);
			this->utilsGroupBox->Location = System::Drawing::Point(855, 8);
			this->utilsGroupBox->Name = L"utilsGroupBox";
			this->utilsGroupBox->Size = System::Drawing::Size(185, 50);
			this->utilsGroupBox->TabIndex = 3;
			this->utilsGroupBox->TabStop = false;
			this->utilsGroupBox->Text = L"Utils";
			// 
			// figureComboBox
			// 
			this->figureComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->figureComboBox->FormattingEnabled = true;
			this->figureComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Hexahedron", L"Tetrahedron", L"Octahedron",
					L"Icosahedron", L"Dodecahedron", L"Sphere"
			});
			this->figureComboBox->Location = System::Drawing::Point(6, 19);
			this->figureComboBox->Name = L"figureComboBox";
			this->figureComboBox->Size = System::Drawing::Size(92, 21);
			this->figureComboBox->TabIndex = 2;
			this->figureComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::figureComboBox_SelectedIndexChanged);
			// 
			// resetButton
			// 
			this->resetButton->Location = System::Drawing::Point(104, 18);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(75, 23);
			this->resetButton->TabIndex = 1;
			this->resetButton->Text = L"Reset";
			this->resetButton->UseVisualStyleBackColor = true;
			this->resetButton->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);
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
			this->shiftGroupBox->Location = System::Drawing::Point(230, 8);
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
			this->scaleGroupBox->Location = System::Drawing::Point(445, 8);
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
			this->projectionGroupBox->Controls->Add(this->ZcLabel);
			this->projectionGroupBox->Controls->Add(this->focusDistanceTextBox);
			this->projectionGroupBox->Controls->Add(this->projectionComboBox);
			this->projectionGroupBox->Location = System::Drawing::Point(666, 8);
			this->projectionGroupBox->Name = L"projectionGroupBox";
			this->projectionGroupBox->Size = System::Drawing::Size(183, 50);
			this->projectionGroupBox->TabIndex = 6;
			this->projectionGroupBox->TabStop = false;
			this->projectionGroupBox->Text = L"Projection";
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1052, 545);
			this->Controls->Add(this->projectionGroupBox);
			this->Controls->Add(this->scaleGroupBox);
			this->Controls->Add(this->shiftGroupBox);
			this->Controls->Add(this->utilsGroupBox);
			this->Controls->Add(this->rotateGroupBox);
			this->Controls->Add(this->pictureBox);
			this->Name = L"MyForm";
			this->Text = L"Rachinskiy, Task #6";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->rotateGroupBox->ResumeLayout(false);
			this->utilsGroupBox->ResumeLayout(false);
			this->shiftGroupBox->ResumeLayout(false);
			this->scaleGroupBox->ResumeLayout(false);
			this->projectionGroupBox->ResumeLayout(false);
			this->projectionGroupBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		private: System::Void minusAngleButton_Click(System::Object^  sender, System::EventArgs^  e) {
			RotateFigure(*current_figure, -ApplicationSettings::GetRotateAngle());
		}
		private: System::Void plusAngleButton_Click(System::Object^  sender, System::EventArgs^  e) {
			RotateFigure(*current_figure, ApplicationSettings::GetRotateAngle());
		}

		private: System::Void negativeShiftButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ShiftFigure(*current_figure, -ApplicationSettings::GetShiftDelta());
		}
		private: System::Void positiveShiftButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ShiftFigure(*current_figure, ApplicationSettings::GetShiftDelta());
		}

		private: System::Void lessScaleButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ScaleFigure(*current_figure, 1 / ApplicationSettings::GetScale());
		}
		private: System::Void moreScaleButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ScaleFigure(*current_figure, ApplicationSettings::GetScale());
		}

		private: System::Void focusDistanceTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			double new_focus_distance = 0;
			if (Double::TryParse(focusDistanceTextBox->Text, new_focus_distance)
				&& new_focus_distance > 0 && new_focus_distance != 1) {
				current_figure->SetFocusDistance(new_focus_distance);
				focusDistanceTextBox->BackColor = Color::White;
				UpdateFigureView(*current_figure);
			} else {
				focusDistanceTextBox->BackColor = Color::Red;
			}
		}

		private: System::Void projectionComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			UpdateFigureView(*current_figure);
		}
		private: System::Void figureComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			ResetFigure();
			UpdateFigureView(*current_figure);
		}

		private: System::Void resetButton_Click(System::Object^  sender, System::EventArgs^  e) {
			ResetFigure();
			UpdateFigureView(*current_figure);
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

		void ResetFigure() {
			String^ mode = (String^)figureComboBox->SelectedItem;
			Figures3D::FuguresFabric fabric (
				ApplicationSettings::GetCanvasScale(),
				pictureBox->Width / 2, pictureBox->Height / 2,
				ApplicationSettings::GetFocusDistance());

			if (mode == "Hexahedron") {
				current_figure.Reset(fabric.CreateHexahedron(2).release());
			} else if (mode == "Tetrahedron") {
				current_figure.Reset(fabric.CreateTetrahedron(2).release());
			} else if (mode == "Octahedron") {
				current_figure.Reset(fabric.CreateOctahedron(2).release());
			} else if (mode == "Icosahedron") {
				current_figure.Reset(fabric.CreateIcosahedron(2).release());
			} else if (mode == "Dodecahedron") {
				current_figure.Reset(fabric.CreateDodecahedron(2).release());
			} else if (mode == "Sphere") {
				current_figure.Reset(fabric.CreateSphere(2).release());
			}
			focusDistanceTextBox->Text = ApplicationSettings::GetFocusDistance().ToString();
			focusDistanceTextBox->BackColor = Color::White;
		}

		void UpdateFigureView(const Figures3D::Figure& figure) {
			ClearImage();
			String^ mode = (String^)projectionComboBox->SelectedItem;
			if (mode == "Perspective") {
				figure.TakePerspectiveProjection(bm);
			} else if (mode == "Orthogonal") {
				figure.TakeOrthogonalProjection(bm);
			}
			pictureBox->Refresh();
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
			UpdateFigureView(figure);
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
			UpdateFigureView(figure);
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
			UpdateFigureView(figure);
		}
};
}
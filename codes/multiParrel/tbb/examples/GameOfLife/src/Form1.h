//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#pragma once

#include <time.h>
#include "Board.h"
#include "AboutDialog.h"
#include "Evolution.h"

namespace Automata {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

			FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			ClientSize = System::Drawing::Size(1206, 600+m_ribbonHeight+menuStrip1->Height);

			int boardWidth = (ClientRectangle.Width/2-m_sepWidth/2)/Board::squareSize;
			int boardHeight = (ClientRectangle.Height-menuStrip1->Height-m_ribbonHeight)/Board::squareSize;

			m_board1 = gcnew Board(boardWidth, boardHeight, seqGen);
			m_board2 = gcnew Board(boardWidth, boardHeight, parGen);
			
			Controls->Add(m_board1);
			Controls->Add(m_board2);

			m_board1->Location = System::Drawing::Point(2, m_ribbonHeight + menuStrip1->Height);
			m_board2->Location = System::Drawing::Point(2 + boardWidth*Board::squareSize + m_sepWidth/2, m_ribbonHeight + menuStrip1->Height);

			m_seq = gcnew SequentialEvolution(m_board1->m_matrix, m_board1, (HWND) Handle.ToInt32());
			m_par = gcnew ParallelEvolution(m_board2->m_matrix, m_board2, (HWND) Handle.ToInt32());

			m_seqThread = gcnew Thread(gcnew ThreadStart(m_seq, &SequentialEvolution::Run));
			m_parThread = gcnew Thread(gcnew ThreadStart(m_par, &ParallelEvolution::Run));		

			m_suspend = true;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  seedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  runToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pauseToolStripMenuItem;
	private: Board^ m_board1;
	private: Board^ m_board2;
	private: System::Windows::Forms::Label^  Sequential;
	private: System::Windows::Forms::Label^  label1;
	private: static const int m_sepWidth = Board::squareSize;
	private: static const int m_ribbonHeight = 26;
	private: SequentialEvolution^ m_seq;
	private: ParallelEvolution^ m_par;
	private: Thread^ m_seqThread;
	private: Thread^ m_parThread;
	private: System::Windows::Forms::Label^  seqGen;
	private: System::Windows::Forms::Label^  parGen;
	private: bool m_suspend;

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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->seedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pauseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Sequential = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->seqGen = (gcnew System::Windows::Forms::Label());
			this->parGen = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->gameToolStripMenuItem, this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1200, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnExit);
			// 
			// gameToolStripMenuItem
			// 
			this->gameToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->seedToolStripMenuItem, 
				this->runToolStripMenuItem, this->pauseToolStripMenuItem});
			this->gameToolStripMenuItem->Name = L"gameToolStripMenuItem";
			this->gameToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->gameToolStripMenuItem->Text = L"Game";
			// 
			// seedToolStripMenuItem
			// 
			this->seedToolStripMenuItem->Name = L"seedToolStripMenuItem";
			this->seedToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->seedToolStripMenuItem->Text = L"Seed";
			this->seedToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnSeed);
			// 
			// runToolStripMenuItem
			// 
			this->runToolStripMenuItem->Enabled = false;
			this->runToolStripMenuItem->Name = L"runToolStripMenuItem";
			this->runToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->runToolStripMenuItem->Text = L"Run";
			this->runToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnRun);
			// 
			// pauseToolStripMenuItem
			// 
			this->pauseToolStripMenuItem->Enabled = false;
			this->pauseToolStripMenuItem->Name = L"pauseToolStripMenuItem";
			this->pauseToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->pauseToolStripMenuItem->Text = L"Pause";
			this->pauseToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnPauseResume);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->aboutToolStripMenuItem->Text = L"About...";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnAbout);
			// 
			// Sequential
			// 
			this->Sequential->AutoSize = true;
			this->Sequential->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Sequential->Location = System::Drawing::Point(9, 31);
			this->Sequential->Name = L"Sequential";
			this->Sequential->Size = System::Drawing::Size(201, 15);
			this->Sequential->TabIndex = 1;
			this->Sequential->Text = L"Sequential Algorithm      generation:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(610, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(184, 15);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Parallel Algorithm     generation: ";
			// 
			// seqGen
			// 
			this->seqGen->AutoSize = true;
			this->seqGen->Location = System::Drawing::Point(217, 33);
			this->seqGen->Name = L"seqGen";
			this->seqGen->Size = System::Drawing::Size(13, 13);
			this->seqGen->TabIndex = 3;
			this->seqGen->Text = L"0";
			// 
			// parGen
			// 
			this->parGen->AutoSize = true;
			this->parGen->Location = System::Drawing::Point(801, 33);
			this->parGen->Name = L"parGen";
			this->parGen->Size = System::Drawing::Size(13, 13);
			this->parGen->TabIndex = 4;
			this->parGen->Text = L"0";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1200, 600);
			this->Controls->Add(this->parGen);
			this->Controls->Add(this->seqGen);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Sequential);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Game of Life";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion	
	protected: 
		virtual void OnPaint(PaintEventArgs^ e) override
		{
		}

		virtual void OnFormClosing(FormClosingEventArgs^ e) override
		{ 
			// Perform a very ungracious exit, should coordinate the threads
			System::Environment::Exit(0);
		}
	
		void OnExit(System::Object^ sender, System::EventArgs^ e)
		{				
			m_seq->Quit();
			m_par->Quit();

			// Perform a very ungracious exit, should coordinate the threads
			System::Environment::Exit(0);			
		}

		void OnSeed(System::Object^ sender, System::EventArgs^ e)
		{
			this->seedToolStripMenuItem->Enabled = false;
			this->runToolStripMenuItem->Enabled = true;			
			time_t now = time(NULL);
			this->m_board1->seed(now);
			this->m_board2->seed(now);
			this->Invalidate();
		}

		void OnRun(System::Object^ sender, System::EventArgs^ e)
		{	
			this->runToolStripMenuItem->Enabled = false;		
			this->pauseToolStripMenuItem->Enabled = true;
			m_seqThread->Start();
			m_parThread->Start();	
		}

		void OnPauseResume(System::Object^ sender, System::EventArgs^ e)
		{	
			if (m_suspend)
			{
				m_parThread->Suspend();
				m_seqThread->Suspend();				
				this->pauseToolStripMenuItem->Text = L"Resume";
			}
			else
			{
				m_parThread->Resume();
				m_seqThread->Resume();				
				this->pauseToolStripMenuItem->Text = L"Pause";
			}
			m_suspend = !m_suspend;
		}

		void OnAbout(System::Object^ sender, System::EventArgs^ e)
		{		
			AboutDialog^ about = gcnew AboutDialog();
			about->ShowDialog();			
		}
	};
}


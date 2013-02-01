//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#pragma once

#include "Matrix.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace Automata {

	/// <summary>
	/// Summary for MyControl
	/// </summary>
	public ref class Board : public System::Windows::Forms::UserControl
	{
	public:
		Board(int width, int height, Label^ counter);		

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		virtual ~Board()
		{
			if (components)
			{
				delete components;
			}
		}

		void Board::seed(int s);
		
	
	protected: 
		virtual void OnPaint(PaintEventArgs^ e) override;		
		void Board::draw(Graphics^ g);

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
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion

	private: delegate void drawDelegate();
	public:
		// Called from the Evolution thread
		void draw()
		{
			if (this->InvokeRequired)
			{
				drawDelegate^ d = gcnew drawDelegate(this, &Board::draw);
				IAsyncResult^ result = BeginInvoke(d);
				EndInvoke(result);
				return;
			}
			draw(m_graphics);
			Int32 i = System::Int32::Parse(m_counter->Text) + 1;
			m_counter->Text = i.ToString();			
		}
	
	public:
		static const int squareSize = 4;
		Matrix *m_matrix;	

	private:
		SolidBrush^ m_occupiedBrush;
		SolidBrush^ m_freeBrush;
		Graphics^ m_graphics;
		int m_width;
		int m_height;
		Label^ m_counter;
	};

}

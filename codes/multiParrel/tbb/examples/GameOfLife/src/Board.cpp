//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include "StdAfx.h"
#include <cstring>
#include "Board.h"
#include <ctime>
#include <cstdlib>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Automata {

Board::Board(int width, int height, Label^ counter)
: m_width(width), m_height(height), m_counter(counter)
{
	InitializeComponent();
	DoubleBuffered = true;

	// pixel height and width
	this->Width = squareSize*width;
	this->Height = squareSize*height;
	
	m_matrix = new Matrix();
	m_matrix->width = width;
	m_matrix->height = height;
	m_matrix->data = new char[width*height];
	memset(m_matrix->data, 0, width*height);

	m_occupiedBrush = gcnew SolidBrush(Color::Black);
	m_freeBrush = gcnew SolidBrush(Color::LightGray);
	
	m_graphics = CreateGraphics();
}

void 
Board::seed(int s)
{		
	srand(s);
	for (int j=0; j<m_height; j++)
	{
		for (int i=0; i<m_width; i++)
		{		
			int x = rand()/(int)(((unsigned)RAND_MAX + 1) / 100);
			m_matrix->data[i+j*m_width] = x>75? 1: 0;	// 25% occupied
		}
	}
	
	Invalidate();
}

void
Board::draw(Graphics^ g)
{
	::MSG m_msg;
	while (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
	{
		// Check for the WM_QUIT message to exit the loop.
		if (WM_QUIT == m_msg.message)				
			break;
				
		::TranslateMessage(&m_msg);
		::DispatchMessage(&m_msg);				
	}
	
	for (int j=0; j<m_height; j++)
	{
		for (int i=0; i<m_width; i++)
		{	
			SolidBrush^ b = (m_matrix->data[i+j*m_width]==0)? m_freeBrush : m_occupiedBrush;
			g->FillRectangle(b, Drawing::Rectangle(i*squareSize, j*squareSize, squareSize-1, squareSize-1));
		}
	}
}

void 
Board::OnPaint(PaintEventArgs^ e)
{
	draw(e->Graphics);
}

}

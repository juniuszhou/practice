//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

// --------------------------------------------------------------
// Evolution.h
// 
// Header file for evolution classes; evolution classes do looped 
// evolution of patterns in a defined 2 dimensional space

#pragma once
#include "Matrix.h"
#include "Board.h"
#include "Cell.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Threading Building Blocks includes
#include "tbb\task_scheduler_init.h"
#include "tbb\blocked_range.h"
#include "tbb\parallel_for.h"

using namespace tbb;
using namespace System::Threading;

namespace Automata {

// --------------------------------------------------------------------------------
// class Evolution - base class for SequentialEvolution and ParallelEvolution
// --------------------------------------------------------------------------------
public ref class Evolution abstract
{
public:

	// public methods

	// constructor
	Evolution(
			Matrix *m,				// beginning matrix including initial pattern
			Board^ board,			// the board to update 
			HWND messageWindow		// window to which WM_DISPLAY_MATRIX message will be sent
			);

	// destructor
	virtual ~Evolution();

	// ----------------------------------------------------------------------------
	// Run() - begins looped evolution
	//
	virtual void Run() = 0;

	// ----------------------------------------------------------------------------
	// Quit() - tell the thread to terminate
	//
	virtual void Quit() { m_done = true; }
	
	// ----------------------------------------------------------------------------
	// Step() - performs a single evolutionary generation computation on the game
	// matrix
	//
	virtual void Step() = 0;
	
private:
	Evolution(){}	

protected:
	//-----------------------------------------------------------------------------
	// PrepareForCalculation() - moves the previous destination data to the source 
	// data block and zeros out desitnation.
	//
	void PrepareForCalculation();

protected:
	// member data

	Matrix *m_matrix;	// Pointer to initial matrix
	char *m_dest;		// Pointer to calculation destination data	
	Board^ m_board;		// The game board to update
	HWND m_hWnd;		// HWND to receive WM_DISPLAY_MATRIX message
	int m_size;			// size of the matrix data block
	volatile bool m_done;		// a flag used to terminate the thread
};

// --------------------------------------------------------------------------------
// class SequentialEvolution - derived from Evolution - calculate life generations
// serially
// --------------------------------------------------------------------------------
public ref class SequentialEvolution: public Evolution
{
public:
	// constructor
	SequentialEvolution(Matrix *m, Board^ board, HWND messageWindow);
		
	virtual void Run() override;	
	virtual void Step() override;
};

// --------------------------------------------------------------------------------
// class ParallelEvolution - derived from Evolution - calculate life generations
// in parallel using Intel's TBB package
// --------------------------------------------------------------------------------
public ref class ParallelEvolution: public Evolution
{
public:
	// constructor
	ParallelEvolution(Matrix *m, Board^ board, HWND messageWindow);

	// destructor
	~ParallelEvolution();

	virtual void Run() override;
	virtual void Step() override;

private:
	task_scheduler_init* m_pInit;
};

}

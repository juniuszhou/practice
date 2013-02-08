//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

// ----------------------------------------------------------------------------------
// Cell.h - header file for Cell class - used to calculate cell state

#pragma once

#include "matrix.h"

// unmanaged class Cell, used by both managed and unmanaged code
class Cell
{
public:
	Cell(void);
	~Cell(void);

	// ----------------------------------------------------------------------------
	// CalculateState() - Calculates the state (1 or 0) of the position in the
	// destination field based on the state of the position in the source field,
	// along with the states of the surrounding cells in the source field. NOTE:
	// The field wraps both vertically and horizontally, so that if an adjacent 
	// position is off the top row, it is fetched from the bottom row, etc.
	char CalculateState(
						char* source,	// pointer to source data block
						int x,			// logical width of field
						int y,			// logical height of field
						int cellNumber	// number of cell position to examine
		               );

private:

	// cell position enum
	enum cellPosition
	{
		upperLeft,
		upper,
		upperRight,
		right,
		lowerRight,
		lower,
		lowerLeft,
		left
	};

	// ----------------------------------------------------------------------------
	// GetAdjacentCellState() - returns the state (value) of the specified adjacent
	// cell of the current cell "cellNumber"
	char GetAdjacentCellState(
								char* source,	// pointer to source data block
								int x,			// logical width of field
								int y,			// logical height of field
								int cellNumber,	// number of cell position to examine
								cellPosition cp	// which adjacent position
							  );
};

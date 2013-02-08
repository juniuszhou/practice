//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

// --------------------------------------------------------------------------------
// Cell.cpp - implementation file for Cell class - used to calculate cell state

#include "StdAfx.h"
#include "Cell.h"

Cell::Cell(void)
{
}

Cell::~Cell(void)
{
}

// --------------------------------------------------------------------------------
// Cell::CalculateState() - Calculates the state (1 or 0) of the position in the
// destination field based on the state of the position in the source field, along 
// with the states of the surrounding cells in the source field. NOTE: The field 
// wraps both vertically and horizontally, so that if an adjacent position is off 
// the top row, it is fetched from the bottom row, etc.
char Cell::CalculateState(
  						char* source,	// pointer to source data block
						int x,			// logical width of field
						int y,			// logical height of field
						int cellNumber	// number of cell position to examine
)
{
	char total = 0;

	total += GetAdjacentCellState(source, x, y, cellNumber, upperLeft);
	total += GetAdjacentCellState(source, x, y, cellNumber, upper);
	total += GetAdjacentCellState(source, x, y, cellNumber, upperRight);
	total += GetAdjacentCellState(source, x, y, cellNumber, right);
	total += GetAdjacentCellState(source, x, y, cellNumber, lowerRight);
	total += GetAdjacentCellState(source, x, y, cellNumber, lower);
	total += GetAdjacentCellState(source, x, y, cellNumber, lowerLeft);
	total += GetAdjacentCellState(source, x, y, cellNumber, left);

	// if the number of adjacent live cells is < 2 or > 3, the result is a dead 
	// cell regardless of its current state. (A live cell dies of loneliness if it
	// has less than 2 neighbors, and of overcrowding if it has more than 3; a new
	// cell is born in an empty spot only if it has exactly 3 neighbors.
	if (total < 2 || total > 3)
	{
		return 0;
	}

	// if we get here and the cell position holds a living cell, it stays alive
	if (*(source+cellNumber))
	{
		return 1;
	}

	// we have an empty position. If there are only 2 neighbors, the position stays
	// empty.
	if (total == 2)
	{
		return 0;
	}

	// we have an empty position and exactly 3 neighbors. A cell is born.
	return 1;
}

// -------------------------------------------------------------------------------
// Cell::GetAdjacentCellState() - returns the state (value) of the specified 
// adjacent cell of the current cell "cellNumber"
//
char Cell::GetAdjacentCellState(
								char* source,	// pointer to source data block
								int x,			// logical width of field
								int y,			// logical height of field
								int cellNumber,	// number of cell position to examine
								cellPosition cp	// which adjacent position
							   )
{
	char cellState = 0;		// return value

	// set up boundary flags to trigger field-wrap logic
	bool onTopRow = false;
	bool onBottomRow = false;
	bool onLeftColumn = false;
	bool onRightColumn = false;

	// check to see if cell is on top row
	if (cellNumber < x)
	{
		onTopRow = true;
	}

	// check to see if cell is on bottom row
	if ((x*y)-cellNumber <= x)
	{
		onBottomRow = true;
	}

	// check to see if cell is on left column
	if (cellNumber%x == 0)
	{
		onLeftColumn = true;
	}

	// check to see if cell is on right column
	if ((cellNumber+1)%x == 0)
	{
		onRightColumn = true;
	}

	switch (cp)
	{
		case upperLeft:
			if (onTopRow && onLeftColumn)
			{
				return *(source+((x*y)-1));
			}
			if (onTopRow && !onLeftColumn)
			{
				return *(source+(((x*y)-x)+(cellNumber-1)));
			}
			if (onLeftColumn && !onTopRow)
			{
				return *(source+(cellNumber-1));
			}
			return *((source+cellNumber)-(x+1));
			break;

		case upper:
			if (onTopRow)
			{
				return *(source+(((x*y)-x)+cellNumber));
			}
			return *((source+cellNumber)-x);
			break;

		case upperRight:
			if (onTopRow && onRightColumn)
			{
				return *(source+((x*y)-x));
			}
			if (onTopRow && !onRightColumn)
			{
				return *(source+(((x*y)-x)+(cellNumber+1)));
			}
			if (onRightColumn && !onTopRow)
			{
				return *(source+((cellNumber-(x*2))+1));
			}
			return *(source+(cellNumber-(x-1)));
			break;

		case right:
			if (onRightColumn)
			{
				return *(source+(cellNumber-(x-1)));
			}
			return *(source+(cellNumber+1));
			break;

		case lowerRight:
			if (onBottomRow && onRightColumn)
			{
				return *source;
			}
			if (onBottomRow && !onRightColumn)
			{
				return *(source+((cellNumber-((x*y)-x))+1));
			}
			if (onRightColumn && !onBottomRow)
			{
				return *(source+(cellNumber+1));
			}
			return *(source+(((cellNumber+x))+1));
			break;

		case lower:
			if (onBottomRow)
			{
				return *(source+(cellNumber-((x*y)-x)));
			}
			return *(source+(cellNumber+x));
			break;

		case lowerLeft:
			if (onBottomRow && onLeftColumn)
			{
				return *(source+(x-1));
			}
			if (onBottomRow && !onLeftColumn)
			{
				return *(source+(cellNumber-((x*y)-x)-1));
			}
			if (onLeftColumn && !onBottomRow)
			{
				return *(source+(cellNumber+((x*2)-1)));
			}
			return *(source+(cellNumber+(x-1)));
			break;

		case left:
			if (onLeftColumn)
			{
				return *(source+(cellNumber+(x-1)));
			}
			return *(source+(cellNumber-1));
			break;
	}


	return cellState;
}


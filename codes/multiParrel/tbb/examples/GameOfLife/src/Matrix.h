//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#pragma once

// This struct is used to communicate between C++/CLR (the UI) and native C++ (the sequential and parallel algorithms)

struct Matrix 
{
	int width;
	int height;
	char* data;
};

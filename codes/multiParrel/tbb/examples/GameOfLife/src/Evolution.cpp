//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

//
// Evolution.cpp
// 
// implementation file for evolution classes; evolution classes do looped 
// evolution of patterns in a defined 2 dimensional space

#include "stdafx.h"
#include "Evolution.h"

namespace Automata {

//
// Evolution constructor
//
Evolution::Evolution(
      Matrix *m,         // beginning matrix including initial pattern
      Board^ board,      // the board to update
      HWND messageWindow // window to which WM_DISPLAY_MATRIX message
                         // will be sent
      ) : m_matrix(m), m_board(board), m_hWnd(messageWindow), m_dest(NULL), 
          m_size(m_matrix->height * m_matrix->width)
{
  // allocate memory for second matrix data block
  m_dest = new char[m_size];
  m_done = false;
}

//
// Evolution destructor
//
Evolution::~Evolution()
{
  // release allocated memory
  delete m_dest;
}

//
// Evolution::PrepareForCalculation()
// moves the previous destination data to the 
// source data block and zeros out destination.
//
void Evolution::PrepareForCalculation()
{
  for (int i=0; i<m_size; i++) {
    *(m_matrix->data+i) = *(m_dest+i);
    *(m_dest+i) = 0;
  }
}

//
// SequentialEvolution constructor
//
SequentialEvolution::SequentialEvolution(Matrix *m, Board^ board, 
                                         HWND messageWindow)
                     : Evolution(m, board, messageWindow)
{
}

//
// SequentialEvolution::Run - begins looped evolution
//
void SequentialEvolution::Run()
{
  // copy source matrix to destination matrix to set up data for call to
  // PrepareForCalculation().
  for (int i=0; i<m_size; i++) {
    *(m_dest+i) = *(m_matrix->data+i);
  }

  while (!m_done)
  {
    PrepareForCalculation();
    Step();
    m_board->draw();
  }
}

//
// SequentialEvolution::Step() - override of step method
//
void SequentialEvolution::Step()
{
  Cell cell;

  for (int i=0; i<m_size; i++) {
    *(m_dest+i) = cell.CalculateState(
                      m_matrix->data,    // pointer to source data block
                      m_matrix->width,  // logical width of field
                      m_matrix->height,  // logical height of field
                      i          // number of cell position to examine
                      );
  }
}

//
// ParallelEvolution constructor
//
ParallelEvolution::ParallelEvolution(Matrix *m, Board^ board,
                                     HWND messageWindow)
                   : Evolution(m, board, messageWindow)
{
  // instantiate a task_scheduler_init object and save a pointer to it
  m_pInit = NULL;
}

//
// ParallelEvolution destructor
//
ParallelEvolution::~ParallelEvolution()
{
  // delete task_scheduler_init object
  if (m_pInit != NULL)
    delete m_pInit;
}

//
// ParallelEvolution::Run - begins looped evolution
//
void ParallelEvolution::Run()
{
  // start task scheduler as necessary
  if (m_pInit == NULL)
    m_pInit = new task_scheduler_init();

  // copy source matrix to destination matrix to set up data for call to
  // PrepareForCalculation().
  for (int i=0; i<m_size; i++)
  {
    *(m_dest+i) = *(m_matrix->data+i);
  }

  while (!m_done)
  {
    PrepareForCalculation();
    Step();
    m_board->draw();    
  }
}

//
// class tbb_parallel_task
// 
// TBB requires a class for parallel loop implementations. The actual
// loop "chunks" are performed using the () operator of the class. The
// blocked_range contains the range to calculate. Please see the TBB
// documentation for more information.
//
public class tbb_parallel_task
{
public:
  static void set_values(Matrix* source, char* dest)
  {
    void* x;
    m_source = source;
    m_dest = dest;
    x = m_source;
    x = m_dest;
    return;
  }

  void operator()( const blocked_range<size_t>& r ) const 
  {
    int begin = (int)r.begin();// capture lower range number for this chunk
    int end = (int)r.end();    // capture upper range number for this chunk
    Cell cell;

    for (int i=begin; i<=end; i++)
    {
      *(m_dest+i) = cell.CalculateState(
                        m_source->data,  // pointer to source data block
                        m_source->width, // logical width of field
                        m_source->height,// logical height of field
                        i                // number of cell position to examine
                       );
    }
  }

  // constructor
  tbb_parallel_task () {}

private:
  // private data

  static Matrix* m_source;
  static char* m_dest;
};

Matrix* tbb_parallel_task::m_source;
char* tbb_parallel_task::m_dest;

//
// ParallelEvolution::Step() - override of Step method
//
void ParallelEvolution::Step()
{
  size_t begin = 0;        // beginning cell position
  size_t end = m_size-1;   // ending cell position
  size_t grainSize = 4000; // grain (chunk) size for individual tasks

  // set matrix pointers
  tbb_parallel_task::set_values(m_matrix, m_dest);

  // do calculation loop
  parallel_for (blocked_range<size_t> (begin, end, grainSize),
                tbb_parallel_task());
}

}

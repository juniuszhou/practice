//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include <iostream>
#include <float.h>
#ifdef _WIN32
#include <malloc.h>
#endif
#include <math.h>
#include <time.h>
#include "tbb/task_scheduler_init.h"
#include "tbb/task.h"
#include "tbb/tick_count.h"

// Algorithm parameters:
int size = 128;
int strass = 32;
int block = 16;
int threadreq = tbb::task_scheduler_init::automatic;

void matrix_add(
  // dimensions of A, B, and C submatrices
  int n, int m,
  // (ax,ay) = origin of A submatrix for multiplicand
  double *A, int ax, int ay, int as,
  // (bx,by) = origin of B submatrix for multiplicand
  double *B, int bx, int by, int bs,
  // (cx,cy) = origin of C submatrix for result
  double *C, int cx, int cy, int cs
)
{
  for (int i=0; i<n; i+=1)
    for (int j=0; j<m; j+=1)
    C[(i+cx)*cs + j+cy] =
       A[(i+ax)*as + j+ay] + B[(i+bx)*bs + j+by];
}

void matrix_sub(
  // dimensions of A, B, and C submatrices
  int n, int m,
  // (ax,ay) = origin of A submatrix for multiplicand
  double *A, int ax, int ay, int as,
  // (bx,by) = origin of B submatrix for multiplicand
  double *B, int bx, int by, int bs,
  // (cx,cy) = origin of C submatrix for result
  double *C, int cx, int cy, int cs
)
{
  for (int i=0; i<n; i+=1)
    for (int j=0; j<m; j+=1)
      C[(i+cx)*cs + j+cy] =
        A[(i+ax)*as + j+ay] - B[(i+bx)*bs + j+by];
}

void matrix_mult(
  // dimensions of A (lxm), B(mxn), and C(lxn) submatrices
  int l, int m, int n,
  // (ax,ay) = origin of A submatrix for multiplicand
  double *A, int ax, int ay, int as,
  // (bx,by) = origin of B submatrix for multiplicand
  double *B, int bx, int by, int bs,
  // (cx,cy) = origin of C submatrix for result
  double *C, int cx, int cy, int cs,
  // depth of recursion (for debug only)
  int d
)
{
  if (l > block && n > block && m > block) {
    int ir, jr, kr, il, is;

    ir = 1 + (l-1) % block;
    jr = 1 + (n-1) % block;
    kr = 1 + (m-1) % block;

    il = 0;
    is = ir;
    for (int ib=0; ib<l; ib+=block) {
      int iu = il + is;
      int jl = 0;
      int js = jr;
      for (int jb=0; jb<n; jb+=block) {
        int ju = jl + js;
        for (int i=il; i<iu; i++)
          for (int j=jl; j<ju; j++)
            C[(i+cx)*cs + j+cy] = 0.0;
          int kl = 0;
          int ks = kr;
          for (int kb=0; kb<m; kb+=block) {
            int ku = kl + ks;
            for (int i=il; i<iu; i++)
              for (int j=jl; j<ju; j++)
                for (int k=kl; k<ku; k++)
                  C[(i+cx)*cs + j+cy] +=
                     A[(i+ax)*as + k+ay] * B[(k+bx)*bs + j+by];
            kl = ku;
            ks = block;
          }
          jl = ju;
          js = block;
      }
      il = iu;
      is = block;
    }
  } else {
    for (int i=0; i<l; i++)
      for (int j=0; j<n; j++) {
        C[(i+cx)*cs + j+cy] = 0.0;
        for (int k=0; k<m; k++)
        C[(i+cx)*cs + j+cy] +=
          A[(i+ax)*as + k+ay] * B[(k+bx)*bs + j+by];
      }
  }
}

void strassen_mult(
  // dimensions of A, B, and C submatrices
  int n,
  // (ax,ay) = origin of A submatrix for multiplicand
  double *A, int ax, int ay, int as,
  // (bx,by) = origin of B submatrix for multiplicand
  double *B, int bx, int by, int bs,
  // (cx,cy) = origin of C submatrix for result
  double *C, int cx, int cy, int cs,
  // current depth of strassen's recursion
  int d,
  // Strassen's recursion limit for array dimensions
  int s
)
{
  if (n < s) {
    matrix_mult(n, n, n, A, ax, ay, as,
                         B, bx, by, bs,
                         C, cx, cy, cs, d);
  } else {
    int n_2 = n >> 1;
    double *work;
    double *a_cum, *b_cum;
    double *p1, *p2, *p3, *p4, *p5, *p6, *p7;

    work  =
      (double *) alloca (sizeof(double) * n_2 * n_2 * 9);
    a_cum = work;
    b_cum = a_cum + n_2 * n_2;
    p1  = b_cum + n_2 * n_2;
    p2  = p1 + n_2 * n_2;
    p3  = p2 + n_2 * n_2;
    p4  = p3 + n_2 * n_2;
    p5  = p4 + n_2 * n_2;
    p6  = p5 + n_2 * n_2;
    p7  = p6 + n_2 * n_2;

    // p1 = (a11 + a22) x (b11 + b22)
    matrix_add(n_2, n_2, A, ax, ay, as,
               A, ax+n_2, ay+n_2, as, a_cum, 0, 0, n_2);
    matrix_add(n_2, n_2, B, bx, by, bs,
               B, bx+n_2, by+n_2, bs, b_cum, 0, 0, n_2);
    strassen_mult(n_2, a_cum, 0, 0, n_2, b_cum,
               0, 0, n_2, p1, 0, 0, n_2, d+1, s);

    // p2 = (a21 + a22) x b11
    matrix_add(n_2, n_2, A, ax+n_2, ay, as,
               A, ax+n_2, ay+n_2, as, a_cum, 0, 0, n_2);
    strassen_mult(n_2, a_cum, 0, 0, n_2, B,
               bx, by, bs, p2, 0, 0, n_2, d+1, s);

    // p3 = a11 x (b12 - b22)
    matrix_sub(n_2, n_2, B, bx, by+n_2, bs,
               B, bx+n_2, by+n_2, bs, b_cum, 0, 0, n_2);
    strassen_mult(n_2, A, ax, ay, as, b_cum,
               0, 0, n_2, p3, 0, 0, n_2, d+1, s);

    // p4 = a22 x (b21 - b11)
    matrix_sub(n_2, n_2, B, bx+n_2, by, bs,
               B, bx, by, bs, b_cum, 0, 0, n_2);
    strassen_mult(n_2, A, ax+n_2, ay+n_2, as, b_cum,
               0, 0, n_2, p4, 0, 0, n_2, d+1, s);

    // p5 = (a11 + a12) x b22
    matrix_add(n_2, n_2, A, ax, ay, as,
               A, ax, ay+n_2, as, a_cum, 0, 0, n_2);
    strassen_mult(n_2, a_cum, 0, 0, n_2, B,
               bx+n_2, by+n_2, bs, p5, 0, 0, n_2, d+1, s);

    // p6 = (a21 - a11) x (b11 + b12)
    matrix_sub(n_2, n_2, A, ax+n_2, ay, as,
               A, ax, ay, as, a_cum, 0, 0, n_2);
    matrix_add(n_2, n_2, B, bx, by, bs,
               B, bx, by+n_2, bs, b_cum, 0, 0, n_2);
    strassen_mult(n_2, a_cum, 0, 0, n_2, b_cum,
               0, 0, n_2, p6, 0, 0, n_2, d+1, s);

    // p7 = (a12 - a22) x (b21 + b22)
    matrix_sub(n_2, n_2, A, ax, ay+n_2, as,
               A, ax+n_2, ay+n_2, as, a_cum, 0, 0, n_2);
    matrix_add(n_2, n_2, B, bx+n_2, by, bs,
               B, bx+n_2, by+n_2, bs, b_cum, 0, 0, n_2);
    strassen_mult(n_2, a_cum, 0, 0, n_2, b_cum,
               0, 0, n_2, p7, 0, 0, n_2, d+1, s);

    // c11 = p1 + p4 - p5 + p7
    matrix_add(n_2, n_2, p1, 0, 0, n_2,
               p4, 0, 0, n_2, C, cx, cy, cs);
    matrix_sub(n_2, n_2, C, cx, cy, cs,
               p5, 0, 0, n_2, C, cx, cy, cs);
    matrix_add(n_2, n_2, C, cx, cy, cs,
               p7, 0, 0, n_2, C, cx, cy, cs);

    // c12 = p3 + p5
    matrix_add(n_2, n_2, p3, 0, 0, n_2,
               p5, 0, 0, n_2, C, cx, cy+n_2, cs);

    // c21 = p2 + p4
    matrix_add(n_2, n_2, p2, 0, 0, n_2,
               p4, 0, 0, n_2, C, cx+n_2, cy, cs);

    // c22 = p1 + p3 - p2 + p6
    matrix_add(n_2, n_2, p1, 0, 0, n_2,
               p3, 0, 0, n_2, C, cx+n_2, cy+n_2, cs);
    matrix_sub(n_2, n_2, C, cx+n_2, cy+n_2, cs,
               p2, 0, 0, n_2, C, cx+n_2, cy+n_2, cs);
    matrix_add(n_2, n_2, C, cx+n_2, cy+n_2, cs,
               p6, 0, 0, n_2, C, cx+n_2, cy+n_2, cs);
  }
  return;
}

class StrassenMultiply : public tbb::task {
  int n, ax, ay, as, bx, by, bs, cx, cy, cs, d, s;
  double *A, *B, *C;
public:
  // dimensions of A, B, and C submatrices
  StrassenMultiply ( int _n,
  // (ax,ay) = origin of A submatrix for multiplicand
   double *_A, int _ax, int _ay, int _as,
  // (bx,by) = origin of B submatrix for multiplicand
  double *_B, int _bx, int _by, int _bs,
  // (cx,cy) = origin of C submatrix for result
  double *_C, int _cx, int _cy, int _cs,
  // current depth of Strassen's recursion
  int _d,
  // Strassen's recursion limit for array dimensions
  int _s
): n(_n), A(_A), B(_B), C(_C),
   ax(_ax), ay(_ay), as(_as), bx(_bx), by(_by), bs(_bs),
     cx(_cx), cy(_cy), cs(_cs), d(_d), s(_s) {}

  tbb::task* execute () {
    if (n < s) {
       // just do the simple algorithm for small matrices
       matrix_mult(n, n, n, A, ax, ay, as,
                   B, bx, by, bs, C, cx, cy, cs, d);
    } else {

      // we are going to create a list of seven tasks -
      // those tasks may create seven more each
      tbb::task_list list;
      int count = 1;

      int n_2 = n >> 1;
      double *work;
      double *p1, *p2, *p3, *p4, *p5, *p6, *p7;

      work  = (double *) alloca (sizeof(double) * n_2 * n_2 * 9);
      p1  =  work;
      p2  = p1 + n_2 * n_2;
      p3  = p2 + n_2 * n_2;
      p4  = p3 + n_2 * n_2;
      p5  = p4 + n_2 * n_2;
      p6  = p5 + n_2 * n_2;
      p7  = p6 + n_2 * n_2;

      // p1 = (a11 + a22) x (b11 + b22)
      double* a_cum1 =
               (double *) alloca (sizeof(double) * n_2 * n_2);
      double* b_cum1 =
               (double *) alloca (sizeof(double) * n_2 * n_2);
      matrix_add(n_2, n_2, A, ax, ay, as,
                 A, ax+n_2, ay+n_2, as, a_cum1, 0, 0, n_2);
      matrix_add(n_2, n_2, B, bx, by, bs,
                 B, bx+n_2, by+n_2, bs, b_cum1, 0, 0, n_2);
      ++count;
      list.push_back (*new (allocate_child ())
        StrassenMultiply (n_2, a_cum1, 0, 0, n_2,
                          b_cum1, 0, 0, n_2, p1, 0, 0, n_2, d+1, s));

      // p2 = (a21 + a22) x b11
      double* a_cum2 = (double *) alloca (sizeof(double) * n_2 * n_2);
      matrix_add(n_2, n_2, A, ax+n_2,
                 ay, as, A, ax+n_2, ay+n_2, as, a_cum2, 0, 0, n_2);
      ++count;
      list.push_back (*new (allocate_child ())
        StrassenMultiply (n_2, a_cum2, 0, 0, n_2,
                          B, bx, by, bs, p2, 0, 0, n_2, d+1, s));

      // p3 = a11 x (b12 - b22)
      double* b_cum3 = (double *) alloca (sizeof(double) * n_2 * n_2);
      matrix_sub(n_2, n_2, B, bx,
                 by+n_2, bs, B, bx+n_2, by+n_2, bs, b_cum3, 0, 0, n_2);
      ++count;
      list.push_back (*new (allocate_child ())
        StrassenMultiply (n_2, A, ax, ay, as,
                          b_cum3, 0, 0, n_2, p3, 0, 0, n_2, d+1, s));

      // p4 = a22 x (b21 - b11)
      double* b_cum4 = (double *) alloca (sizeof(double) * n_2 * n_2);
      matrix_sub(n_2, n_2, B, bx+n_2,
                 by, bs, B, bx, by, bs, b_cum4, 0, 0, n_2);
      ++count;
      list.push_back (*new (allocate_child ())
        StrassenMultiply (n_2, A, ax+n_2, ay+n_2, as,
                          b_cum4, 0, 0, n_2, p4, 0, 0, n_2, d+1, s));

      // p5 = (a11 + a12) x b22
      double* a_cum5 = (double *) alloca (sizeof(double) * n_2 * n_2);
      matrix_add(n_2, n_2, A, ax,
                 ay, as, A, ax, ay+n_2, as, a_cum5, 0, 0, n_2);
      ++count;
      list.push_back (*new (allocate_child ())
        StrassenMultiply (n_2, a_cum5, 0, 0, n_2,
                          B, bx+n_2, by+n_2, bs, p5, 0, 0, n_2, d+1, s));

      // p6 = (a21 - a11) x (b11 + b12)
      double* a_cum6 = (double *) alloca (sizeof(double) * n_2 * n_2);
      double* b_cum6 = (double *) alloca (sizeof(double) * n_2 * n_2);
      matrix_sub(n_2, n_2, A, ax+n_2,
                 ay, as, A, ax, ay, as, a_cum6, 0, 0, n_2);
      matrix_add(n_2, n_2, B, bx,
                 by, bs, B, bx, by+n_2, bs, b_cum6, 0, 0, n_2);
      ++count;
      list.push_back (*new (allocate_child ())
        StrassenMultiply (n_2, a_cum6, 0, 0, n_2,
                          b_cum6, 0, 0, n_2, p6, 0, 0, n_2, d+1, s));

      // p7 = (a12 - a22) x (b21 + b22)
      double* a_cum7 = (double *) alloca (sizeof(double) * n_2 * n_2);
      double* b_cum7 = (double *) alloca (sizeof(double) * n_2 * n_2);
      matrix_sub(n_2, n_2, A, ax,
                 ay+n_2, as, A, ax+n_2, ay+n_2, as, a_cum7, 0, 0, n_2);
      matrix_add(n_2, n_2, B, bx+n_2,
                 by, bs, B, bx+n_2, by+n_2, bs, b_cum7, 0, 0, n_2);
      ++count;
      list.push_back (*new (allocate_child ())
        StrassenMultiply (n_2, a_cum7, 0, 0, n_2,
                          b_cum7, 0, 0, n_2, p7, 0, 0, n_2, d+1, s));

      set_ref_count (count);
      spawn_and_wait_for_all (list);

      // c11 = p1 + p4 - p5 + p7
      matrix_add(n_2, n_2, p1, 0,
                 0, n_2, p4, 0, 0, n_2, C, cx, cy, cs);
      matrix_sub(n_2, n_2, C, cx,
                 cy, cs, p5, 0, 0, n_2, C, cx, cy, cs);
      matrix_add(n_2, n_2, C, cx,
                 cy, cs, p7, 0, 0, n_2, C, cx, cy, cs);

      // c12 = p3 + p5
      matrix_add(n_2, n_2, p3, 0,
                 0, n_2, p5, 0, 0, n_2, C, cx, cy+n_2, cs);

      // c21 = p2 + p4
      matrix_add(n_2, n_2, p2, 0,
                 0, n_2, p4, 0, 0, n_2, C, cx+n_2, cy, cs);

      // c22 = p1 + p3 - p2 + p6
      matrix_add(n_2, n_2, p1, 0,
                 0, n_2, p3, 0, 0, n_2, C, cx+n_2, cy+n_2, cs);
      matrix_sub(n_2, n_2, C, cx+n_2,
                 cy+n_2, cs, p2, 0, 0, n_2, C, cx+n_2, cy+n_2, cs);
      matrix_add(n_2, n_2, C, cx+n_2,
                 cy+n_2, cs, p6, 0, 0, n_2, C, cx+n_2, cy+n_2, cs);
    }
    return NULL;
  }
};

void strassen_mult_par (
  // dimensions of A, B, and C submatrices
  int n,
  // (ax,ay) = origin of A submatrix for multiplicand
  double *A, int ax, int ay, int as,
  // (bx,by) = origin of B submatrix for multiplicand
  double *B, int bx, int by, int bs,
  // (cx,cy) = origin of C submatrix for result
  double *C, int cx, int cy, int cs,
  // current depth of Strassen's recursion
  int d,
  // Strassen's recursion limit for array dimensions
  int s
)
{
  StrassenMultiply& t = *new (tbb::task::allocate_root ())
    StrassenMultiply (n, A, ax, ay, as,
                         B, bx, by, bs,
                         C, cx, cy, cs, d, s);
  tbb::task::spawn_root_and_wait (t);
}

void init (size_t size, double* A, double* B) {
  srand((unsigned int)time(NULL));
  for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            A[i*size + j] = ((float) rand()) / ((float) RAND_MAX);
            B[i*size + j] = ((float) rand()) / ((float) RAND_MAX);
        }
  }
}

int main(int argc, char *argv[])
{
  double *A, *B, *C, *D, *E;

  // Allocate array storage
  A = new double [size * size];
  B = new double [size * size];
  C = new double [size * size];
  D = new double [size * size];
  E = new double [size * size];

  // Set up input matrices with random values
  init (size, A, B);

  std::cerr << "Parameters:" << std::endl <<
    "  array size: " << size << "x" << size << std::endl <<
    "  threads: " << threadreq << std::endl <<
    "  strassen minimum: " << strass << std::endl <<
    "  matmul blocksize: " << block << std::endl;

  // Blocked serial matrices multiplication
  tbb::tick_count simple1 = tbb::tick_count::now ();
  matrix_mult (size, size, size,
               A, 0, 0, size,
               B, 0, 0, size,
               D, 0, 0, size, 0);
  tbb::tick_count simple2 = tbb::tick_count::now ();
  std::cerr << "Simple serial algorithm: " <<
    (simple2-simple1).seconds () << " seconds" << std::endl;

  // Strassen algorithm [Serial]
  tbb::tick_count serial1 = tbb::tick_count::now ();
  strassen_mult (size, A, 0, 0, size,
                       B, 0, 0, size,
                       C, 0, 0, size, 1, strass);
  tbb::tick_count serial2 = tbb::tick_count::now ();
  std::cerr << "Strassen algorithm serial: " <<
    (serial2-serial1).seconds () << " seconds" << std::endl;

  // Strassen algorithm [Parallel]
  tbb::task_scheduler_init init (threadreq);
  tbb::tick_count parallel1 = tbb::tick_count::now ();
  strassen_mult_par (size, A, 0, 0, size,
                           B, 0, 0, size,
                           E, 0, 0, size, 1, strass);
  tbb::tick_count parallel2 = tbb::tick_count::now ();
  std::cerr << "Strassen algorithm parallel: " <<
    (parallel2-parallel1).seconds () << " seconds" << std::endl;

  delete[] A;
  delete[] B;
  delete[] C;
  delete[] D;
  delete[] E;

  return 0;
}

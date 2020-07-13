//////////////////////////////////////////////////////////////////////////
// Conjugate gradient squared routine routine iteratively calculates the
// value of X where Z*X = B
// The matrix Z is assumed to be square.
// The parameters are:
// Z[MAX_SIZE][MAX_SIZE] - the maximum Z-matrix;
// X - vector of the unknown values;
// B - vector of the products Z*X;
// N - real dimension of the matrix


#include "util.hh"
#include "complex.hh"

#define pi acos(-1) 
#define NO_OF_PLATES 2 
#define NOL  5 //Number of lines 
#define NOE (3*NOL*NOL - 8*NOL + 5)
#define MAX_SIZE NOE 
#define f 900000000 
#define omega 2.0*pi*f 
#define eps 8.854e-12 
#define mu  pi*4.0e-7 




complex  inner_prod( complex*, complex*, int, int );
void arr_vec_mult( complex [NO_OF_PLATES*NOE][NO_OF_PLATES*NOE], complex*,
		   complex* , int, int, int, int );

void cgs( complex Z[NO_OF_PLATES*NOE][NO_OF_PLATES*NOE], complex X[NO_OF_PLATES*NOE], complex B[NO_OF_PLATES*NOE],
          int N )
{
  complex r0[NO_OF_PLATES*NOE], p0[NO_OF_PLATES*NOE];
  complex s0[NO_OF_PLATES*NOE], t0[NO_OF_PLATES*NOE];
  complex e0, d, a1, b1, y, temp, z;

  double tol = 1.0e-12;
  register int k = 0, m, i, j;
 cout << "\n Inversion using CGS starting " << endl << endl;

  for ( i = 0; i < N; i++ )
  {
    r0[i] = complex( 0.0, 0.0 );
    X[i]  = r0[i];
    s0[i] = r0[i];
  }
   
   arr_vec_mult( Z, B, r0, CONJ, TRANS, N, N ); // r0 = conj(Z)*B

  for ( i = 0; i < N; i++ )
  {
    p0[i] = r0[i];
  }

   
  e0 = inner_prod( r0, r0, CONJ, N ); // e0 = sum( r0^2 ) 

  
//----- Conjugate gradient squares method as described by Van Der Vorst ----

  while (e0.real()  > tol)
  {
    k++;
    d = e0;
    
	arr_vec_mult( Z, p0, t0, NO_CONJ, NO_TRANS, N, N );

 
	 arr_vec_mult( Z, t0, s0, CONJ, TRANS, N, N );
     y = inner_prod( p0, s0, CONJ, N ); // y = sum(p0*s0)
    a1 = e0/y; // a1 = e0/y

    for ( i = 0; i < N; i++ )
    {
      X[i]  += a1 * p0[i]; // X  = X  + a1*p0
      r0[i] -= a1 * s0[i]; // r0 = r0 - a1*s0
    }

	e0 = inner_prod( r0, r0, CONJ, N ); // e0 = sum(r0^2)
    b1 = e0/d;

    for ( i = 0; i < N; i++ )
    {
      p0[i] = r0[i] + b1 * p0[i]; // p0 = r0 + b1*p0
    }

  }
  cout << "\n Inverted in " << k << " iterations with error "  << e0.real()   << endl ; 
}


//----------- Group of functions necessary to invert a matrix --------------
//-- other functions also needed include cdiv(),cmult(),cadd() and csub() --
//---------- The four functions above are contained in arithmetic.c --------

//---------------- array by vector multiplication --------------------------

void arr_vec_mult( complex Z[NO_OF_PLATES*NOE][NO_OF_PLATES*NOE], complex X[NO_OF_PLATES*NOE],
		   complex B[NO_OF_PLATES*NOE], int conjugate, int trans,
		   int N, int M )
{
  register int i,j;

//////////////////////////////////////////////////////////////////////////
// Calculate conj(Transpose(Z))*X or Transpose(Z)*X

  for ( i = 0; i < M; i++ )
  {
    B[i] = complex( 0.0, 0.0 );
    for ( j = 0; j < N; j++ )
    {
      if (trans == TRANS)
      {
	if ( conjugate == CONJ )
	{
	  B[i] += conj( Z[j][i] ) * X[j];
	}
	else if ( conjugate == NO_CONJ )
	{
	  B[i] += Z[j][i] * X[j];
	}
      }
      else if ( trans == NO_TRANS )
      {
        if ( conjugate == CONJ )
        {
          B[i] += conj( Z[i][j] ) * X[j];
        }
        else if ( conjugate == NO_CONJ )
        {
          B[i] += Z[i][j] * X[j];
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// calculate the inner product of a vector 

complex inner_prod( complex* z1, complex* z2, int conjugate, int N ) 
{

  complex z;
  register int i;

  z = complex( 0.0, 0.0 );
  for ( i = 0; i < N; i++ ) 
  {
    if ( conjugate == CONJ ) z += z1[i] * conj( z2[i] );
    else
    if ( conjugate == NO_CONJ ) z += z1[i] * z2[i];
  }
  return (z);
}



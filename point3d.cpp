//=========================================================================
// COPYRIGHT (c) 2001-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Eamonn M. Kenny, William O' Brien
// Previous Project:      FMW/ARG (vector.hh)
// Project:               STIWRO
// Project Manager:       Dr. Peter J. Cullen
// Last Modification:     October 2001
// Software Tool Version: 1.0
//=========================================================================

#include "point3d.hh"


CPoint3d& CPoint3d::operator=( const CPoint3d& v1 )
{
  x = v1.x;
  y = v1.y;
  z = v1.z;
  return *this;
}

CPoint3d::CPoint3d( const CPoint3d& v1 )
{
  x = v1.x;
  y = v1.y;
  z = v1.z;
}

boolean CPoint3d::operator==( const CPoint3d& v1 ) const
{
  if ( fabs( x - v1.x ) < TOL &&  fabs( y - v1.y ) < TOL 
    && fabs( z - v1.z ) < TOL ) return true;
  else
   return false;
}

boolean CPoint3d::operator!=( const CPoint3d& v1 ) const
{
	/* cout << "x equals " <<  x << endl ; 
     cout << "y equals " <<  y << endl ; 
	 cout << "z equals " <<  z << endl ; 
	 cout << "v1.x equals " <<  v1.x << endl ; 
	 cout << "v1.y equals " <<  v1.y << endl ; 
	 cout << "v1.z equals " <<  v1.z << endl ;  */ 

  if ( (x != v1.x) || (y != v1.y) || (z != v1.z) ) return true;
  else
   return false;
}

CPoint3d CPoint3d::operator-( const CPoint3d& v1 ) const
{
  CPoint3d v2;
  v2.x = x - v1.x;
  v2.y = y - v1.y;
  v2.z = z - v1.z;
  return v2;
}

CPoint3d CPoint3d::operator^( const CPoint3d& v1 ) const
{
  CPoint3d v2(0, 0, 0);
  v2.x = y * v1.z - z * v1.y;
  v2.y = z * v1.x - x * v1.z;
  v2.z = x * v1.y - y * v1.x;
  return v2;
}

CPoint3d CPoint3d::operator+( const CPoint3d& v1 ) const
{
  CPoint3d v2;
  v2.x = x + v1.x;
  v2.y = y + v1.y;
  v2.z = z + v1.z;
  return v2;
}

CPoint3d CPoint3d::operator*( const double& dd ) const
{
  CPoint3d v;
  v.x = x * dd;
  v.y = y * dd;
  v.z = z * dd;
  return v;
}


double CPoint3d::operator*( const CPoint3d& v ) const
{
  return( x * v.x + y * v.y + z * v.z );
}

CPoint3d CPoint3d::operator/( const double& dd ) const
{
  CPoint3d v;
  v.x = x / dd;
  v.y = y / dd;
  v.z = z / dd;
  return v;
}

double CPoint3d::cosAngle( const CPoint3d& v )
{
  CPoint3d r, s;
  r = unitVector();
  s = v.unitVector();
  return r * s;
}

double CPoint3d::angle( const CPoint3d& v )
{
  return ( acos( cosAngle( v ) ) );
}

double  CPoint3d::abs() const
{
  return ( sqrt( x * x + y * y + z * z ) );
}

CPoint3d CPoint3d::unitVector() const
{
  CPoint3d p2;

  p2 = *this / ( this->abs() );
  return p2;
}

double  CPoint3d::abs( const CPoint3d& p ) const
{
  return ( sqrt( qsqr(x-p.x) + qsqr(y-p.y) + qsqr(z-p.z) ) );
}



CPoint3d cross ( const CPoint3d& v1, const CPoint3d& v2 ) 
   {
      CPoint3d vv ;

      vv.x = v1.y * v2.z - v1.z * v2.y ;
      vv.y = - v1.x * v2.z + v1.z * v2.x ;
      vv.z = v1.x * v2.y - v1.y * v2.x ;

      return ( vv ) ;
   }


ostream&  operator<<( ostream& s, const CPoint3d& v )
{
  return s << "(" <<  v.x << " " << v.y << " " <<  v.z << ")" ;
}

/*
Commented by Conor 06/07/2020 for GPU
 istream& operator>>( istream& s, CPoint3d& v )
{
  char    TempString[80];
  int     Length;
  boolean Completed;

  do 
  {
    s.getline( TempString, 78 );
  } while ( ( Length = strlen(TempString) ) == 0 );
  TempString[Length] = '\0';
  Completed = characterStringToPoint( v, TempString );

  return s;
}


boolean characterStringToPoint( CPoint3d& v, char* CPoint3dString ) 
{
  char      temp[80];
  int       Length;
  int       i, j, k;
  boolean   Completed;
  
  v = CPoint3d( 0.0, 0.0, 0.0 );
  j = 0;
  k = 0;

  Completed = false;

  Length = strlen( CPoint3dString );
  if ( Length < 4 ) 
  {
    cerr << "String read error: Reading again: [" << CPoint3dString << "]" 
         << endl;
    return ( false );
  }

  for ( i = 0; i < Length; i++ )
  {
    if ( CPoint3dString[i] != '(' && CPoint3dString[i] != ',' 
      && CPoint3dString[i] != ')' && CPoint3dString[i] != ' ' )
    {
      temp[j] = CPoint3dString[i];
      j++;
    }
    else if (j == 0)
    {
      // do nothing
    }
    else
    {
      k++;
      temp[j] = '\0';
      if ( k == 1 )      v.x = atof( temp ); 
      else if ( k == 2 ) v.y = atof( temp ); 
      else if ( k == 3 ) v.z = atof( temp ); 
      j = 0; 
      temp[0] = '\0';
    }
    if (k == 3) 
    { 
      i = Length; //terminate loop
      Completed = true;
    }
  }
  if ( Completed == false )
    cerr << "String read error: Reading again: [" << CPoint3dString << "]" 
         << endl;

  return Completed;
}
*/

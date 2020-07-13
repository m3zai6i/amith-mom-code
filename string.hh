//=========================================================================
// COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Eamonn M. Kenny
// Project Manager:       Dr. Peter J. Cullen
// Last Modification:     October 2001
// Previous Projects:     Storms, FMW/ARG
// Current  Project:      IP2000 STIWRO
// Software Tool Version: 1.0
//=========================================================================

#ifndef TCD_STRING_HH
#define TCD_STRING_HH

#include <iostream.h>
#include <string.h>
#include <fstream.h>
#include "boolean.hh"

#ifndef __GNUG__
  #define EXPORT_CLASS_DECLSPEC class __declspec(dllexport) 
#else
  #define EXPORT_CLASS_DECLSPEC class
#endif

EXPORT_CLASS_DECLSPEC CString
//=========================================================================
// = FUNCTION 
//     string.hh
//
// = AUTHOR
//     Eamonn M. Kenny
//
// = DESCRIPTION
//     string class for making dynamic strings 
//
// = VERSION
//     1.0
//
// = COPYRIGHT
//     COPYRIGHT (c) 1995-1999 by Trinity College Dublin, Dublin 2, IRELAND
//     All rights reserved 
//=========================================================================
{
  private:
    int   length_;
    char* characters_;

  public:
    CString();
    CString( const char *CharacterString );
    CString( char *CharacterString );
    //
    // construct a string
    //

    int length() const;
    //
    // returns the length of the string
    //

    char  item( int i ) const;
    char* characters() const;
    //
    // returns the character string
    //

    boolean  operator==( const char*    CharacterString ) const;
    boolean  operator==( const CString& CharacterString ) const;
    boolean  operator!=( const char*    CharacterString ) const;
    boolean  operator!=( const CString& CharacterString ) const;
    //
    // Compare a string to a constant string 
    //

    CString& operator=( const CString& OldString );
    CString& operator=( char  *CharacterString );
    CString& operator=( const char  *CharacterString );
    CString& operator=( char OneCharacter );
    //
    // Make a new string from an old string or from a "charstring".
    //

    CString& operator+=( char AppendingCharacter );
    CString& operator+=( char  *AppendingCharacters );
    CString& operator+=( const CString&  AppendingString );
    CString& operator+(  char  *AppendingCharacters );
    CString& operator+(  const CString&  AppendingString );
    //
    // Append CharacterString to the current String
    //

    CString& subString( int i, int j ) const;
    //
    // Calculate the substring between reference i and j of the string
    // inclusive of both i and j. New String length size is: j-i+1
    //

    int occurrencesInFile( char* fileName );
    //
    // see how many times a string occurs in a file
    //

    bool readToString( ifstream& filePtr );
    bool readToString( ifstream& filePtr, const CString& terminationString );
    //
    // in a file read to the string containing characters_ and stop there.
    //

    CString& readFullString( ifstream& filePtr );
    //
    // In the string is a substring of a string in the file, then return
    // it's full string.
    //

    friend ostream& operator<<( ostream& out, const CString& OneString );
    friend istream& operator>>( istream& out, CString& OneString );
    //
    // Output/Input the contents of the string
    //

    ~CString()
    {
      if ( length() > 0 )
        delete [] characters_;
    }
};

#endif

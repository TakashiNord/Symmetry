// Symmetry.cpp : Defines the class behaviors for the application.
//
//#include "stdafx.h"
////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>  
#include <stdio.h>   
#include <string.h>
#include <conio.h>
#include <math.h>
#include <ctype.h>
/////////////////////////
#define mStr 80

class Sym
{
// Construction
public:
	Sym();	// standard constructor
	virtual ~Sym();
    // Implementation
	void main_Sym(void);
	int read_word(char *s, char w, char *sw) ;
	int returnError(int typeErr);
//////////////////
    FILE *in,*on ;
	int choice_methods;
protected:
	// Generated message map functions
};

// Tsym.h: interface for the Tsym class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSYM_H__D83B571F_BB23_49C1_B3BD_0B11441EAADD__INCLUDED_)
#define AFX_TSYM_H__D83B571F_BB23_49C1_B3BD_0B11441EAADD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define mStr 240

class Tsym  
{
public:
	int trim_str(char *s);
	int space;
	long int h33;
	long int program_format_H33(char *namefile, int codefeed);
	int trGCode(char *s,int tp);
	int EQ_is_gt (double s, double t);
	int EQ_is_equal (double s, double t);
	int EQ_is_zero (double s);
	long int main(char *sourcefile,char *destfile, int type);
	int trCoord(char *s,float fMulti,char *w);
	int trCoordConversion(float cst,char *s);
	int delete_word(char *s,char w);
	void replace_word(char *s,char w,char *sw);
	int read_word(char *s,char w,char *sw);
	Tsym();
	virtual ~Tsym();

};

#endif // !defined(AFX_TSYM_H__D83B571F_BB23_49C1_B3BD_0B11441EAADD__INCLUDED_)

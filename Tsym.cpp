// Tsym.cpp: implementation of the Tsym class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Symmetry.h"
#include "Tsym.h"

/* Include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <malloc.h>
#include <dos.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Tsym::Tsym()
{
 h33=-1;
 space=-1;
}

Tsym::~Tsym()
{
}

int Tsym::read_word(char *s, char w, char *sw)
{
     char *word,sym;
	 int  n;
	 if(s==NULL) return(0);
	 if ((word=strchr(s,w))==NULL) return(0);
	 n=0;
	 do
	 {  sym=*(word+(n+1));
		 if (isdigit(sym)||sym==' '||sym=='+'||sym=='-'||sym=='.') n++;
		 else break;
	 } while (1);
	 if (n>0){ strncpy(sw,word+1,n); sw[n]='\0'; return(n); }
	 else                                        return(0);
}

void Tsym::replace_word(char *s, char w, char *sw)
{
  int n;
  char old_sw[80],save[mStr],*p;
  char str[mStr];

  if(s==NULL) return;

  strcpy(str,sw);
  if (space==1) {
  	strcat(str," ");
   }

  if ((n=read_word(s,w,old_sw))!=0)
  {
	 /* replace word */
	 p=strchr(s,w);
	 *(p+1)='\0'; strcpy(save,p+n+1);
	 //strcat(strcat(s,sw),save);
	 strcat(strcat(s,str),save);
  }
  else
  {
	 /* add word at the end of string */
	 p=strchr(s,'<') ; /* string have <CR> or <LF> as text */
	 if (p==NULL) p=strchr(s,'\r'); /* string have \r\n */
	 if (p==NULL) p=strchr(s,'\n'); /* string have \n   */
	 //if (p!=NULL) { strcpy(save,p); *p=w; *(p+1)='\0'; strcat(strcat(s,sw),save); }
	 //else { save[0]=w; save[1]='\n'; save[2]='\0'; strcat(strcat(s,save),sw); }
	 if (p!=NULL) { strcpy(save,p); *p=w; *(p+1)='\0'; strcat(strcat(s,str),save); }
	 else { save[0]=w; save[1]='\n'; save[2]='\0'; strcat(strcat(s,save),str); }
  }

}

int Tsym::trim_str(char *s)
{
  int l, k, i;
  char *p;  char str[mStr];

  if(s==NULL) return (0);

  l=strlen(s);
  if (l==0) return (0);

  p = strrchr(s, ' ');
  if (!p) return (0);

  i=l-1;
  while( (*(s+i)=='\0') || (*(s+i)=='\n') || (*(s+i)=='\r') || (*(s+i)==' ') )
  {
   if (i<=0) break;
   i--;
  }

  if (i<0) i=0;

  for (k=i;k>=0;k--) str[k]=*(s+k);
  str[i+1]='\n';
  str[i+2]='\0';

  strcpy(s,str);

  return (1);
}

int Tsym::delete_word(char *s, char w)
{
 int n;
 char old_sw[mStr],save[mStr],*p;
 n=0;
 if ((n=read_word(s,w,old_sw))!=0)
  {
	 /* replace word */
	 p=strchr(s,w);
	 *(p+0)='\0'; strcpy(save,p+n+1);
	 strcat(s,save);
  }

 return n;
}

long int Tsym::program_format_H33(char *namefile, int codefeed)
{
/*локальные переменные*/
 FILE *rf; /*Указатель на файл*/
 long int numbers_of_kadrs;/* Число кадров*/
 long int error;
 char info[mStr*3];
 char curr[mStr], word[mStr];

 /*Открываем файл*/
 rf=fopen(namefile,"r");
 if (rf==NULL) {
   info[0]='\0';
   sprintf(info,"Невозможно открыть файл:\n %s \n на 'чтение' \n",namefile );
   /*Application->MessageBox(info,"Проверка программы на формат H33 - > ошибка ...", MB_OK);*/
   fprintf(stderr, info);
   return(-1);
  }

 /*Начальные условия*/
 error=0;
 /*if (codefeed!=1) codefeed=0;*/
 numbers_of_kadrs=0;

 curr[0]='\0'; fgets(curr,mStr,rf);
 while(!feof(rf))
 {

   /*Первичные признаки*/
   if (read_word(curr,'X',word)) {
      if (7!=strlen(word)) error++;
   }
   if (read_word(curr,'Y',word)) {
      if (7!=strlen(word)) error++;
   }
   if (read_word(curr,'Z',word)) {
      if (7!=strlen(word)) error++;
   }
   if (read_word(curr,'I',word)) {
      if (7!=strlen(word)) error++;
   }
   if (read_word(curr,'J',word)) {
      if (7!=strlen(word)) error++;
   }
   if (read_word(curr,'K',word)) {
      if (7!=strlen(word)) error++;
   }

   /*Вспомогательные признаки*/
   if (codefeed==0) {
      if (read_word(curr,'F',word)) {
         if (4!=strlen(word)) error++;
      }
   }

   /* if (read_word(curr,'M',word)) {
      if (3<=strlen(word)) error++;
   }  */
   /*if (read_word(curr,'L',word)) {
      if (3!=strlen(word)) error++;
   }*/
   /*if (read_word(curr,'N',word)) {
      if ((3!=strlen(word))||(5!=strlen(word))) error++;
   } */
   /*if (read_word(curr,'G',word)) {
      if (3<=strlen(word)) error++;
   }*/

   /*if (read_word(curr,'D',word)) error++;
   if (read_word(curr,'H',word)) error++;*/

   /*Вторичные признаки*/
   if (NULL!=strchr(curr,'.')) error++;
   /*if (NULL!=strchr(curr,';')) error++;
   if (NULL!=strchr(curr,'(')) error++;
   if (NULL!=strchr(curr,')')) error++;
   if (NULL!=strchr(curr,'"')) error++;
   if (NULL!=strchr(curr,'\'')) error++;*/

   curr[0]='\0'; fgets(curr,mStr,rf);
   numbers_of_kadrs++;
 } // end while

 fclose(rf);

 return(error);
}

/*Преобразование G кодов*/
/*
 tp -
	0 - без преобразований;
	1 - преобразование G02->G03 && G03->G02 ;
	2 - преобразование G41->G42 && G42->G41 ;
	21 - преобразование G43->G42 && G42->G43 ;
 */
int Tsym::trGCode(char *s, int tp)
{
  char word_p[70], s1[20];
  int n,num;
  char sp2[mStr];
  char *jpd,*jpdg;
  char *ptr;
  char save[128],*p;
  float gcode ;
  num=0;
  /*Кадры с G*/
  if (read_word(s,'G',word_p))  {
     strcpy(sp2,s);
     jpd=strchr(sp2,'G');
     if(jpd!=NULL) {
       while(strcmp(jpd,""))
       {
         if (read_word(jpd,'G',word_p))
         { sscanf(word_p,"%f",&gcode);
           //printf(" Gf==%f Gs=%s |" ,gcode,word_p);
		   switch (tp) {
		   case 0:  break;
		   case 1:
			   if (gcode==2) gcode=3;
			    else if (gcode==3) gcode=2; else { ; }
			   if ((gcode==2)||(gcode==3)) {
			     sprintf(s1,"G%s",word_p);
			     n=strlen(word_p);
			     ptr = strstr(s, s1);
	             	     p=strchr(ptr,'G');
	             	     *(p+1)='\0'; strcpy(save,p+n+1);
			     sprintf(s1,"%02.0f",gcode);
			     strcat(strcat(s,s1),save);
			     //printf("1 The substring is: %s\n", ptr);
			     num++;
			   }
			   break;
		   case 2:
			   if (gcode==41) gcode=42;
			    else if (gcode==42) gcode=41; else { ; }
			   if ((gcode==41)||(gcode==42)) {
			     sprintf(s1,"G%s",word_p);
			     n=strlen(word_p);
			     ptr = strstr(s, s1);
	              	     p=strchr(ptr,'G');
	             	     *(p+1)='\0'; strcpy(save,p+n+1);
			     sprintf(s1,"%02.0f",gcode);
			     strcat(strcat(s,s1),save);
			     //printf("2 The substring is: %s\n", ptr);
			     num++;
			   }
			   break;
		   case 21:
			   if (gcode==42) gcode=43;
			    else if (gcode==43) gcode=42; else { ; }
			   if ((gcode==42)||(gcode==43)) {
			     sprintf(s1,"G%s",word_p);
			     n=strlen(word_p);
			     ptr = strstr(s, s1);
	              	     p=strchr(ptr,'G');
	             	     *(p+1)='\0'; strcpy(save,p+n+1);
			     sprintf(s1,"%02.0f",gcode);
			     strcat(strcat(s,s1),save);
			     //printf("2 The substring is: %s\n", ptr);
			     num++;
			   }
			   break;
		   default : break ;
		   }
         }
         jpdg=strchr(jpd,'G');
         if(jpdg==NULL) strcpy(jpd,"");else strcpy(jpd,jpdg+1);
       }
     }

  }
  return num;
}

/*Преобразование числа*/
int Tsym::trCoordConversion(float cst, char *s)
{
    char sp[mStr];
    char format[20];
    float pr ;
    int len, k;
    char *ptr;

    if (s==NULL) return (0);

    if (1!=sscanf(s,"%f",&pr)) { return -1 ; }

    pr*=cst;

    // если формат Н33
    if (h33==0) {
      sp[0]='\0';
      sprintf(sp,"%+07.0f",pr);
      s[0]='\0';
      strcpy(s,sp);
      return 0 ;
    }

    // если число с пробелами - убираем
    len=strlen(s);
    ptr=strchr(s,' ');
    if (ptr) {
    	k=ptr-s;
        sp[0]='\0';
        strncpy(sp, s, k);
	sp[k]='\0';
        strcpy(s,sp);
        sp[0]='\0';
    }

    // если число с . - сколько знаков после запятой
    // форматируем
    len=strlen(s);
    ptr=strchr(s,'.');
    if (ptr) {
	k=len-(ptr-s+1);

    	sp[0]='\0';
    	switch (k) {
    	case 0 : sprintf(sp,"%.0f.",pr);
    	break;
    	case 1 : sprintf(sp,"%.1f",pr);
    	break;
    	case 2 : sprintf(sp,"%.2f",pr);
    	break;
    	case 3 : sprintf(sp,"%.3f",pr);
    	break;
    	case 4 : sprintf(sp,"%.4f",pr);
    	break;
    	default : sprintf(sp,"%.3lf",pr);
    	break;
    	}

        s[0]='\0';
        strcpy(s,sp);
        return 0 ;
     }

    // если число = 0
    // форматируем в соответствии с количеством нулей,и знака
    len=strlen(s);
    if (pr==0.0) {
    	format[0]='\0';
    	if ((NULL!=strchr(s,'+'))||(NULL!=strchr(s,'-'))) {
    		sprintf(format,"%%+0%dld",len);
         } else { sprintf(format,"%%0%dld",len); }
        sp[0]='\0';
        sprintf(sp,format,pr);
        s[0]='\0';
        strcpy(s,sp);
        return 0 ;
    }

    // если число формата = +70000 -010025 8960000
    // форматируем в соответствии с количеством нулей,и знака
    len=strlen(s);
    format[0]='\0';
    if ((NULL!=strchr(s,'+'))||(NULL!=strchr(s,'-'))) {
    	sprintf(format,"%%+0%d.0f",len);
     } else { sprintf(format,"%%0%d.0f",len); }

    sp[0]='\0';
    //sprintf(sp,"%.0f",pr);
    sprintf(sp,format,pr);

    s[0]='\0';
    strcpy(s,sp);

    return 0 ;
}

/*Преобразование координат на множитель fMulti*/
int Tsym::trCoord(char *s, float fMulti, char *w)
{
  char word_p[70]; int l,n,i,num;
  char *ptr;
  num=0;

  n=strlen(w);
  if (n<=0) return -1;

  if (s==NULL) return -1;
  l=strlen(s);

  space=-1;
  // предварительно необходимо обрезать строку с конца
  // что мы и сделали до вызова
  ptr = strchr(s, ' ');
  if (ptr) space=1;

  for (i=0;i<n;i++) {
   /*Кадры с i*/
   if (read_word(s,w[i],word_p))  {
    trCoordConversion(fMulti,word_p);
    replace_word(s,w[i],word_p) ;
    num++;
   }
  }

  space=-1;
  return num;
}

long int Tsym::main(char *sourcefile, char *destfile, int type)
{
 /*локальные переменные*/
 FILE *rf,*ff; /*Указатели на файл*/
 char info[mStr*3];
 char curr[mStr];
 char *jp;
 int flsign ; //флаг - комментарий ; ( )
 long int countAdr ;

 /*Проверка задаваемых значений*/
   switch (type) {
    case 0 : /*- нет преобразований*/
    break;
    case 1 : /*- X*/
    break;
    case 2 : /*- Y*/
    break;
    case 3 : /*- XY*/
    break;
    default : type=0;
    break;
   }

  if ( type== 0 ) return (-3) ;

 /*Открываем файл на чтение*/
 rf=fopen(sourcefile,"r");
 if (rf==NULL) {
   info[0]='\0';
   sprintf(info,"Невозможно открыть файл:\n %s \n на 'чтение' \n",sourcefile );
   fprintf(stderr, info);
   return(-1);
  }

 /*Открываем файл на запись*/
 ff=fopen(destfile,"w");
 if (rf==NULL) {
   info[0]='\0';
   sprintf(info,"Невозможно открыть файл:\n %s \n на 'запись' \n",destfile );
   fprintf(stderr, info);
   return(-2);
  }

 h33=program_format_H33(sourcefile, 1);
 if (h33<0) return(-1);

 /*Начальные условия*/
 countAdr=0;
 curr[0]='\0';
 jp=fgets(curr,mStr,rf);
 while(!feof(rf))
 {

   /*Если строка не комментарий  ; ( )*/
   flsign=0;
   if (!((NULL==strchr(jp,';'))&&(NULL==strchr(jp,'('))&&
         (NULL==strchr(jp,')'))&&(NULL==strchr(jp,'$')))) { flsign=1; }

   switch (type) {
    case 0 : /*- нет преобразований*/
    break;
    case 1 : /*- X*/
       /*Кадры с YJ G*/
       if (flsign!=0) break;
       trim_str(jp);
       countAdr+=trGCode(jp,1);
       if (h33==0) {
        countAdr+=trCoord(jp,-1,"Y");
        countAdr+=trGCode(jp,21);
       } else {
        countAdr+=trCoord(jp,-1,"YJ");
        countAdr+=trGCode(jp,2);
       }
    break;
    case 2 : /*- Y*/
      /*Кадры с XI G*/
      if (flsign!=0) break;
      trim_str(jp);
      countAdr+=trGCode(jp,1);
      if (h33==0) {
        countAdr+=trCoord(jp,-1,"X");
        countAdr+=trGCode(jp,21);
       } else {
        countAdr+=trCoord(jp,-1,"XI");
        countAdr+=trGCode(jp,2);
       }
    break;
    case 3 : /*- XY*/
       /*Кадры с XYIJ*/
       if (flsign!=0) break;
       trim_str(jp);
       if (h33==0) {
        countAdr+=trCoord(jp,-1,"XY");
       } else {
        countAdr+=trCoord(jp,-1,"XYIJ");
       }
    break;
    default :
    break;
   }

   trim_str(jp);

   fputs(jp,ff);

   curr[0]='\0';
   jp=fgets(curr,mStr,rf);
 } // end while

 fclose(rf);

 fputs(curr,ff);
 fclose(ff);

 return(countAdr);

}

int Tsym::EQ_is_zero(double s)
{
  double mom_system_tolerance=0.00000001 ;
  if (fabs(s)<= mom_system_tolerance) { return(1); } else { return(0) ; }
}

int Tsym::EQ_is_equal(double s, double t)
{
	double mom_system_tolerance=0.00000001 ;
	if (fabs(s-t)<= mom_system_tolerance) { return(1); } else { return(0) ; }
}

int Tsym::EQ_is_gt(double s, double t)
{
    double mom_system_tolerance=0.00000001 ;
    if (s > (t + mom_system_tolerance)) { return(1); } else { return(0) ; }
}


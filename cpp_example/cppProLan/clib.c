
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
//<cmath>
#include <math.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#include <stddef.h>     /* offsetof */
#include <time.h>

int FindMax (int n, ...){
  int i,val,largest;
  va_list vl;
  va_start(vl,n); // Initialize a variable argument list
  largest=va_arg(vl,int);// Retrieve next argument
  for (i=1;i<n;i++)  {
    val=va_arg(vl,int);
    largest=(largest>val)?largest:val;
  }
  va_end(vl); //End using variable argument list
  return largest;
}



void test_clib (){
    char str[]="1776ad";
    int year;
    /** isdigit  */ 
    if (isdigit(str[0]))  
        year = atoi (str);   printf (" was %d.\n",year);
    /** errno   */ 
    if (fopen("/etc/123", "r"))  printf("REPORT: File opened successfully\n");
    else   printf("ERROR: %s\n", strerror(errno)); /**must include <string.h> */ 
    /** math  */
    #define PI 3.14159265
    double result = cos( 60 * PI / 180.0 );
    float v = 2;
    //result = exp(result);// error exp
    float sq = 1+sqrt(2);
    printf("cos: %f, exp:%f, sqrt:%f\n", result,exp(1), sq);
    /** v arg */
    int m= FindMax (7,702,422,631,834,892,104,772);
    printf ("The largest value is: %d\n",m);
    /** offset */ 
    struct foo {  char a;  char b[10];  char c;};
    printf ("offsetof(struct foo,c) is %d\n",(int)offsetof(struct foo,c));
    /**  General Utilities */
    result = atof("1.23");
    char szOrbits[] = "686.97 365.24";    char* pEnd;
    float f1, f2;
    f1 = strtof (szOrbits, &pEnd);
    f2 = strtof (pEnd, NULL);
    printf("strtof :%f, %f ,%f\n", f1,f2,result);
    /** rand */
    int i;    srand (time(NULL)); //seed
    for(i=1; i<=5;i++) printf(": %d", rand()); printf("\n");
    /**  */ 



}

void test_io(){
    printf("\n");
    char str [80];    float f;
    FILE * pFile;
    /** fscanf : Read formatted data from file */ 
    pFile = fopen ("myfile.txt","w+");
    fprintf (pFile, "%f %s", 3.1416, "PI");
    rewind (pFile);
    fscanf (pFile, "%f", &f);    fscanf (pFile, "%s", str);
    fclose (pFile);
    printf ("I have read: %f and %s \n",f,str);
    /** scan: Read formatted data from stdin */ 
    //scanf ("%d",&i);
    /** sscanf: Read formatted data from string  */
    char sentence []="Rudolph is 12 years old"; int i;
    sscanf (sentence,"%s %*s %d",str,&i);
    printf ("%s -> %d\n",str,i);
    /** sprintf : Write formatted data to string*/ 
    int n, a=5, b=3;
    n=sprintf (str, "%d plus %d is %d", a, b, a+b); //Write formatted data to string
    printf ("[%s] is a string %d chars long\n",str,n);
    /**  */ 

}

void test_cstring(){
    /** cstring */ 
    char myname[] = "I am a string to copy *----* source.\n"; char name[80];
    /** copy  */ 
    memcpy (name, myname, strlen(myname)+1 );//copy: count/not only string/
    printf("memcpy: %s",name);
    memmove (myname+7,myname+22,6);//allow destination and source to overlap.
    puts (myname);
    char src[]="Sample string.";  char dest[40];
    //strcpy (dest,src); // all 
    strncpy(dest, src, 5); // only 5 copyed
    printf ("src: %s ; dest: %s\n",src,dest);
    int a[20];
    memset(a, 2, sizeof(a)); // every byte set to 0x01 (257 = 0x101 will put 0x01)
    printf("memset: %08x \n",a[2]); //got 0x02020202
    /** cat */ 
    //strcat(str, str2);
    strncat(src, " Goodbye World!", 8);
    puts(src);
    /** compare */
    char str1[]="1235"; char str2[]="1234"; 
    printf("compare :%d \n",strcmp(str2, str1)); // str cmp return 0 : same, positive: str2 include in str1
    printf("mem compare :%d \n",memcmp(str2, str1,3)); //mem compare
    printf("strlen:%d\n",(int)strlen(src)); //strlen 
    /** find  */ 
    const char * str3; str3 = strstr(src, "string"); //strstr  find string 
    printf("strstr :%s \n",str3);  
    str3 = strchr(src, 'G'); //strchr find first 's' ins src 
    printf("strchr :%s \n",str3); 

}

int main(int argc, char *argv[])
{
    /**  */ 
    test_clib();

    /**  */ 
    test_io();

    test_cstring();

    return 0;
}

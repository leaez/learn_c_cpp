
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

#define MARK (printf("--------------%s (%d) - <%s>\n",__FILE__,__LINE__,__FUNCTION__)) 
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
    MARK;
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
    /** qsort */ 
    int values[] = { 40, 10, 100, 90, 20, 25 };
    int compare (const void * a, const void * b) { return ( *(int*)a - *(int*)b ); }
    qsort (values, 6, sizeof(int), compare); int n;
    for (n=0; n<6; n++)  printf ("%d ",values[n]); printf("\n");

}

void test_io(){
    MARK;
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
    sscanf (sentence,"%s %*s %d",str,&i); //%*s means read but ignor
    printf ("%s -> %d\n",str,i); //Rudolph -> 12
    char hex[] = "1f1f";
    sscanf(hex,"%x",&i);
    printf("sscanf: %x = %d\n",i,i);
    /** sprintf : Write formatted data to string*/ 
    int n, a=5, b=3;
    n=sprintf (str, "%d plus %d is %d", a, b, a+b); //Write formatted data to string
    printf ("[%s] is a string %d chars long\n",str,n);
    char buffer [100];  
    n = snprintf ( buffer, 100, "The half of %d is %d", 60, 60/2 );
    printf("snprintf: %s  & L: %d\n", buffer, n);
    //Write formatted output to sized buffer
    /**  */ 

}

void test_cstring(){
    MARK;
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

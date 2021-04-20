#include <stdio.h> 
#include <string.h> 
  int flag=0;
/* Function to swap values at two pointers */
void swap(char *x, char *y) 
{ 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
/* Function to print permutations of string 
   This function takes three parameters: 
   1. String 
   2. Starting index of the string 
   3. Ending index of the string. */
void permute(char *a, int l, int r) 
{ 
   int i; 
   if (l == r){ 
    flag++;
    if(flag==2 || flag ==10){
     printf("%s\n", a); 
   }}
   else
   { 
       for (i = l; i <= r; i++) 
       { 
          swap((a+l), (a+i)); 
          permute(a, l+1, r); 
          swap((a+l), (a+i)); //backtrack 
       } 
   } 
} 
int main() 
{ 
      int N;
      scanf("%d",&N);
    char str[N+100]; 
    char c='0'+10;
    char d='0'+11;char e='0'+12;char f='0'+13;char g='0'+14;char h='0'+15;char i='0'+16;

    if(N==1){
       // str="1";
    strcpy(str,"1");
    }
     if(N==2){
      strcpy(str,"12"); // str="12";
    }
     if(N==3){
     //   str="123";
      strcpy(str,"123");
    }
     if(N==4){
     strcpy(str,"1234");
       // str="1234";
    }
     if(N==5){
     strcpy(str,"12345");
     //   str="12345";
    }
     if(N==6){
     strcpy(str,"123456");
       // str="123456";
    }if(N==7){
     strcpy(str,"1234567");
        //str="1234567";
    }
    if(N==8){
     strcpy(str,"12345678");
       // str="12345678";
    }if(N==9){
     strcpy(str,"123456789");
       // str="12345678";
    }if(N==10){
    
     strcpy(str,"123456789c");
       // str="12345678";
    }
    if(N==11){
    
     strcpy(str,"123456789cd");
       // str="12345678";
    }if(N==12){
    
     strcpy(str,"123456789cde");
       // str="12345678";
    }if(N==13){
    
     strcpy(str,"123456789cdef");
       // str="12345678";
    }if(N==14){
    
     strcpy(str,"123456789cdefg");
       // str="12345678";
    }   if(N==15){
    
     strcpy(str,"123456789cdefgh");
       // str="12345678";
    }if(N==16){
    
     strcpy(str,"123456789cdefghi");
       // str="12345678";
    }
    
    int n = strlen(str); 
    permute(str, 0, n-1); 
    return 0; 
} 
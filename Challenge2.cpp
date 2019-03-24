#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std ;

#define ONEBYTE 8

int hexToInt(const char x){
   int k = x-'0';
   if (k>9){
      k = (k-'0')+9;
   }
   return k;
}

char IntToHex(const int x){
   char k = x+'0';
   if (k>'9'){
      k = (k+'0')-9;
   }
   return k;
}

void Fixedxor(const char *x,const char *y, char* &res){
   int mask = 0xFF;
   int lunghezza1 = char_traits<char>::length(x);
   int lunghezza2 = char_traits<char>::length(y);
   if (lunghezza1 != lunghezza2){
      cout<< " Lunghezza errata \n";
      return ;
   }
   //cout << lunghezza1 <<" \n";

   for(int i =0;i<lunghezza1;i++){
      int hbyte = hexToInt(x[i]);
      int hbyteTwo = hexToInt(y[i]);
      res[i] = IntToHex(hbyte ^ hbyteTwo);
      //cout<<res[i]<<"\n";
   }
}

void printString(const char * x,const int len){
   cout << len <<" \n";
   for(int i=0; i<len; i++){
      cout<<x[i];
   }
   cout<<"\n";
}

int main()
{
   char myhex[] = "1c0111001f010100061a024b53535009181c";
   char mysecond[] = "686974207468652062756c6c277320657965";
   int lunghezza = char_traits<char>::length(myhex);
   char * myRes;
   myRes = new char[lunghezza];

   Fixedxor(myhex,mysecond,myRes);
   printString(myRes,lunghezza);

   system("pause");
   delete[] myRes;
   return 0;
}
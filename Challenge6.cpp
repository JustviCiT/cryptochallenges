#include <iostream>
#include <cstring> 
#include <fstream>
#include "crypto_helpers.h"

using namespace std;

struct EncryptedText{
   char * arr;
   int lunghezza;
} myText;

void Base64ToText(const char *x,int lenBase, EncryptedText &h){
   int lunghezza = lenBase;
   int Cresto = 0 ;
   int realResto = 0;
   int conta_h = 0;
   int mask = 0xFF;

   h.lunghezza = (lenBase/2)*3;
   h.arr = new char [h.lunghezza];

   //cout << lunghezza <<" \n";

   if (lunghezza<= 1)
      return ;

   for(int i =0;i<lunghezza;i+=2){
      int k = hexToInt(x[i]);
      int j = hexToInt(x[i+1]);
      k = k<<4;
      int byte = k^j;
      //cout<<byte<<"\n";

      Cresto = ( ONEBYTE + Cresto ) - 6;

      switch(Cresto) {
         case 2:
            mask = 0x03;
            break;

         case 4:
            mask = 0x0F;
            break;

         case 6:
            mask = 0x3F;
            break;

         default :
            mask = 0xFF;
      }

      h.arr[conta_h]= (byte >> Cresto)^realResto;

      realResto = (byte & mask)<< ( ONEBYTE - Cresto)-2;

      if(Cresto >= 6){
         conta_h++;
         h.arr[conta_h]= realResto;
         realResto = 0;
         Cresto =0;
      }
      conta_h++;
   }

   if(Cresto != 0){
      h.arr[conta_h]= realResto;
   }
}


int main(int argc, char* argv[])
{
   // Challenge 6
   // Compile: g++ Challenge6.cpp crypto_helpers.cpp -o Challenge5
   char a[] = "this is a test";
   char b[] = "wokka wokka!!!";

   int dist = 0;
   for(int i =0 ; i < strlen(a); i++){
      dist += hamming_distance(a[i],b[i]);   
   }

   cout<< dist<<endl; 

   ifstream ofile;
   char filename[] = "crypto_data6.txt";
   ofile.open(filename);
   if (!ofile) {
      cerr << "Unable to open file crypto_data6.txt";
      exit(1);   
   }
   char fileTmp[100];
   int index = 0;
   char * cryptoText;
   long int filesize = GetFileSize(filename);

   cryptoText = new char[filesize];

   while (ofile >> fileTmp){  
      strcat (cryptoText,fileTmp);
   };
   ofile.close();

   int total_added = strlen(cryptoText);


   cout << filesize <<" "<< total_added;

   system("pause");
   return 0;
}
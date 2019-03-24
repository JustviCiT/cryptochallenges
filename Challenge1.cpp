#include <iostream>
#include <cstring>
#include <cstdlib>
#include <bitset>
#include "crypto_helpers.h"

using namespace std ;

struct base64{
   unsigned int * arr;
   int lunghezza;
} myRes;

void hexToBase64(const char *x,base64 &h){
   int lunghezza = h.lunghezza;
   int Cresto = 0 ;
   int realResto = 0;
   int conta_h = 0;
   int mask = 0xFF;

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
   
   h.lunghezza = conta_h+1;
}

int main()
{
      //49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
   char myhex[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
   int lunghezza = char_traits<char>::length(myhex);
   myRes.arr = new unsigned int[lunghezza];
   myRes.lunghezza = lunghezza;

   //cout<<hexToInt('a')<<" "<<hexToInt('6')<<" "<<hexToInt('f')<<" ";
/*    char a[] = "4";
   int ia = (int) a[0];
   ia = ia >> 5;
   cout<<ia<<" \n";
   bitset<6> x(a[0]); 
   cout<<x<<" \n";*/
   hexToBase64(myhex,myRes);
   printBase64(myRes);

   system("pause");

   delete[] myRes.arr;
   return 0;
}

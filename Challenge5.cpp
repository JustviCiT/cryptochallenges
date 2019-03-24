#include <iostream>
#include <cstring> 

using namespace std;

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


int mergeHexes(int a,int b){
   a = a<<4;
   int ret = a^b;
   return ret;
}

void printString(const char * x,const int len){
   //cout << len <<" \n";
   for(int i=0; i<len; i++){
      cout<<x[i];
   }
   cout<<"\n";
}

void cryptTEXT(const char* testo, const char * key, unsigned int ltxt, unsigned int lkey, char * res){
   int templen = 0;
   int resIndex = 0;

   for(int i=0; i<ltxt; i++){
      if(templen == lkey)
         templen = 0;

      char tmp = testo[i] ^ key[templen];
      int al = tmp>>4; 
      int au = tmp & 0x0F;
      res[resIndex] = IntToHex(al);
      resIndex++;
      res[resIndex] = IntToHex(au);
      resIndex++;
      templen++;
   }

}


int main(int argc, char* argv[])
{
   // Challenge 5
   //char textToCrypt[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
   char key[255];
   char textToCrypt[255];
   char c;
   int i = 0;

   cout<<"Inserisci il testo: "<<endl;
   while(c != '\n'){
      c = getchar();

      if(i >= 255)
         break;
      textToCrypt[i++] = c;
   }
   textToCrypt[i]='\0';

   cout << "Key: " <<endl;
   cin >> key;

   unsigned int ltxt = strlen(textToCrypt) ;
   unsigned int lkey = strlen(key);

   cout << " " << textToCrypt << " " << key << " " << ltxt << " " << lkey << endl;

   // result
   char * res;
   res = new char[ltxt*2];
   cryptTEXT(textToCrypt,key,ltxt,lkey,res);
   printString(res,ltxt*2);


   delete[] res;
   system("pause");

   return 0;
}
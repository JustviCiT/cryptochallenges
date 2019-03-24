#include <iostream>
#include <sys/stat.h>
using namespace std;

const float frequencies[] = {
   0.0804, // A
   0.0148, // B
   0.0334, // C
   0.0382, // D
   0.1249, // E
   0.0240, // F
   0.0187, // G
   0.0505,
   0.0757,
   0.0016, // J
   0.0054, // K
   0.0407,
   0.0251,
   0.0723,
   0.0764, // O
   0.0214,
   0.0012,
   0.0628, // R
   0.0651, // S
   0.0928, // T
   0.0273, // U
   0.0105, // V
   0.0168, // W
   0.0023, // X
   0.0166, // Y
   0.0009, // Z
};

const char base64Table[] = {
   'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
   'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
   'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
   'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'
};

struct base64{
   unsigned int * arr;
   int lunghezza;
} myRes;


int const MAXHASHES = 100;
int const ONEBYTE = 8;
int const MAXFREQUENCIES = 26;

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

long GetFileSize(char const * filename)
{
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
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

void printFrequencies(){
   char letter = 'a';
   for(int i = 0 ; i < MAXFREQUENCIES; i++){
      cout<<letter++<<" "<<frequencies[i]<<" ";
      cout<<"\n";
   } 
   cout<<"\n";
}

void printBase64(base64 &x){
   cout<<"\n";
   for(int i = 0; i<x.lunghezza-1;i++){
      cout<<base64Table[ x.arr[i] ];
   }
   cout<<"\n";
}

float getFrequence(char f){
   if (f > 'A' && f < 'Z'){
      f +=32;
   } else{
      return 0;
   }

   if (f > 'a' &&  f < 'z'){
      f -= 'a';  
   }else{
      return 0;
   }
   return frequencies[f];
}

float weightString(const char *x,int len){
   float count = 0;
   float true_chars = 0;
   for(int i = 0; i< len;i++){
      float k = getFrequence( x[i] );
      if(k > 0){
         true_chars ++;
      }
      count += k;
   }
   return (true_chars/len)*count; 
}


int hamming_distance(unsigned x, unsigned y)
{
    int dist = 0;
    unsigned  val = x ^ y;

    // Count the number of bits set
    while (val != 0)
    {
        // A bit is set, so increment the count and clear the bit
        dist++;
        val &= val - 1;
    }

    // Return the number of differing bits
    return dist;
}
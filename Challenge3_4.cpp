#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cctype>

#include <fstream>

using namespace std;

#define ONEBYTE 8
#define MAXFREQUENCIES 26
#define MAXHASHES 100
// 0 = a ... 25 = z
const static float frequencies[MAXFREQUENCIES] = {
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

void printFrequencies(){
   char letter = 'a';
   for(int i = 0 ; i < MAXFREQUENCIES; i++){
      cout<<letter++<<" "<<frequencies[i]<<" ";
      cout<<"\n";
   } 
   cout<<"\n";
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

void SingleXOR(const char *x, const int lunghezza, char * &ret){
   char * myRes;
   char * finalAnswer;
   int conta_h = 0;
   myRes = new char[lunghezza];
   finalAnswer = new char[lunghezza];

   int j = 0;
   float max = 0;
   float wString = 0 ;

   //cout << lunghezza <<" \n";
   for(j = 0; j<256; j++){
      for(int i =0;i<lunghezza;i+=2){
         int hbyte = hexToInt(x[i]);
         int hbyteTwo = hexToInt(x[i+1]);
         int mByte = mergeHexes(hbyte,hbyteTwo);
         myRes[conta_h] = mByte ^ j;
         conta_h++;
      }

      wString = weightString(myRes,conta_h);
      if(wString > max){
         max = wString;
         memcpy(finalAnswer,myRes,conta_h);
      }
      
      conta_h = 0;
      wString = 0;
   }

   
/*    printString(finalAnswer,lunghezza/2);
   cout<<" "<<max<<" ";
   cout<<"\n"; */

   memcpy(ret,finalAnswer,lunghezza/2);

   delete[] myRes;
   delete[] finalAnswer;
}

int main()
{
   //printFrequencies();
   // Challenge 3
   //char myhex[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
   //SingleXOR(myhex,68);

   // Challenge 4
   ifstream ofile;
   ofile.open("encrypted_data1.txt");
   if (!ofile) {
      cerr << "Unable to open file encrypted_data1.txt";
      exit(1);   
   }
   char fileTmp[100];
   int i = 0;
   int totalrows = 0;

   while (ofile >> fileTmp){  
      totalrows ++;

   };
   ofile.close();

   ofile.open("encrypted_data1.txt");
   if (!ofile) {
      cerr << "Unable to open file encrypted_data1.txt";
      exit(1);   
   }

   char ** myHexes;
   myHexes = new char *[totalrows];
   int maxcols = 0;

   while (ofile >> fileTmp){  
      //cout<<fileTmp<<"\n";
      maxcols = strlen(fileTmp);
      myHexes[i] = new char [maxcols];
      memcpy(myHexes[i],fileTmp, maxcols);
      //cout<<myHexes[i];
      i++;
   };

/*    for(i=0; i<totalrows; i++){
      printString(myHexes[i],maxcols);   
   } */

   float max = 0;
   float wString = 0;

   char * finalAnswer;
   char * tmp;

   tmp = new char[maxcols/2];
   finalAnswer = new char[maxcols/2];

   for(i=0; i<totalrows; i++){

      SingleXOR(myHexes[i], maxcols, tmp);
      wString = weightString(tmp,maxcols/2);
      if(wString > max){
         max = wString;
         memcpy(finalAnswer,tmp,maxcols/2);
      }

      wString = 0;
   }
   
   printString(finalAnswer,maxcols/2);
   cout<<" "<<max<<" ";
   cout<<"\n";

   ofile.close();

	// release dynamically allocated memory
	for (i=0; i < totalrows; i++)
		delete [] myHexes[i];// each array of characters

	delete [] myHexes;// the array of pointers

   delete[] finalAnswer;
   delete[] tmp;

   system("pause");
   return 0;
}
extern float const frequencies[];
extern const char base64Table[];

extern int const MAXHASHES;
extern int const ONEBYTE;
extern int const MAXFREQUENCIES;


int hexToInt(const char x);
char IntToHex(const int x);
long GetFileSize(char const * filename);
int mergeHexes(int a,int b);
void printString(const char * x,const int len);
void printFrequencies();
void printBase64(base64 &x);
float getFrequence(char f);
float weightString(const char *x,int len);
int hamming_distance(unsigned x, unsigned y);
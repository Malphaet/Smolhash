#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* pbit(const char *c){
  int i,w;
  char mask;
  int len=strlen(c);
  char*res=malloc(sizeof(char)*8*(len+1));
  for (w=0; w < len; w++) {
    mask=c[w];
    for(i=0;i<sizeof(char)*8;i++){
      res[i+8*w]='0'+(mask&1);
      mask>>=1;
    }
    //printf("%c %s\n",c[w],res);
  }
  return res;
}

// Hash a string into an int
unsigned char hash(const char*word){
   unsigned char sum=0;
   int step=0;
   unsigned int psum[3];
   psum[0]=0;psum[1]=0;psum[2]=0;
   for(step=0;;step++){
       if(word[step] >='A' && word[step] < 'A'+26)
            psum[step%3]^=(word[step] -'A');
       else if(word[step] >='a' && word[step] < 'a'+26)
            psum[step%3]^=(word[step] -'a');
      else if(word[step]=='\0') break;
       //printf("%u\n",psum[step%3]);
   }
   psum[1]<<=1; psum[2]<<=2;
   sum=psum[0]^psum[1]^psum[2];
   //printf("sum %u %u %u %u\n",sum,psum[0],psum[1],psum[2]);
   return sum;
}

int maxin(int*ar,int s){
  int i,m=0;
  for (i = 0; i < s; i++) if (ar[i]>m) m=ar[i];
  return m;
}

void printa(int*ar,int s){
  int i,j,mx=maxin(ar,s);
  for (i = 0; i < s; i++) printf("#");
  printf("\n");
  for (j = 0; j < 32; j++) {
    for (i = 0; i < s; i++) {
      if (ar[i]*32/mx>j) printf("#");
      else printf(" ");
    }
    printf("\n");
  }
}

/*Main test function*/
int main(int argc, char const *argv[]) {
  //printf("%s %s\n",argv[1],pbit(argv[1]));
  int i,j;
  char test[7];
  int vals[128];
  for (i = 0;i < 128;i++)vals[i]=0;
  for (i = 0; i < 6; i++) test[i]=0;
  for (j = 0; j < MAXT; j++) {
    test[(j/26)%6]=j%26+'a';
    vals[hash(test)]+=1;
    //  if(j%26==25) test[((j-1)/26)%6]='a';
    //printf("%s %i\n",test,hash(test));
  }

  printa(vals,128);
  //int res[64];
  return 0;
}

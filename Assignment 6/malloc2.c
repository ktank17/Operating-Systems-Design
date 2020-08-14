#include "malloc2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *addrI; 
int lenI; 

typedef
struct _mem_Node
{
   void *address; 
   size_t nbytes; 
} mem_node;


int *malloc2(int size){
if(size <= 0){
   printf("Memory size should be greate then zero\n");
   exit(0);
}

addrI = (int*)malloc(sizeof(int));
if(addrI == NULL){
   printf("Memory allocation unsuccessful\n");
   exit(0);  
}
return addrI;
}


int free2(void *ptr){
if (ptr != NULL){
   free(ptr);
   ptr = NULL;

}else if (ptr != addrI){
   printf("Error: Not the first byte of the range of memory that was allocated\n");
   exit(0);
}else if(ptr == NULL){
   printf("Error: Freeing memory that was previously freed.\n");
}else{
      printf("Error:Freeing memory not allocated by malloc2\n");
   exit(0);
}
return 0;
}


int *realloc2(void *ptr, int size){
if(ptr == NULL){
    if(size <= 0){
       return 0;
   }else{
       return malloc2(size);
   }
}else{
   if(size == 0){
   int i= free2(ptr);
   return 0;
   }
}

void *ptr2;
ptr2 = realloc(ptr,size);
if(ptr2 == NULL){
    printf("Realloc value is null\n");
   exit(-1);
}
memcpy(addrI, ptr,size);
free(ptr);
return 0;

}


int memcheck2(void *addr, int size){

if(addr == NULL){
   printf("Error: Null pointer specified\n");
   exit(-1);
}
if(size == 0){
   printf("Error: Memorys size zero\n");
}
void *ptr2,*ptr_new;
ptr2 = &addr + size;
if(ptr2 == NULL){
   printf("Error: Address not allocated");  
//   exit(-1);
}

ptr_new = (int *)malloc2(sizeof(size));

if(ptr2 == ptr_new){
    printf("Memory check failed\n");
    exit(-1);
}
return 0;
}



int main(int argc,char* argv[]){
int *ptr;
int size =16;
ptr = (int *)malloc2(sizeof (size));
if(ptr == NULL)
{ printf("error\n");
    return 1;
}
else
{ printf(" Malloc2 successful\n");
}
memcheck2(ptr, 36);
printf("Memcheck successfull\n");
free2(ptr);
printf("free Successfull\n");

char *buff = (char*)malloc(10);
memcheck2(buff,strlen("hi hello!"));
strcpy(buff,"hi hello!");
return 0;

}
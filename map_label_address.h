#pragma once
#include "mytypes.h"
#include "stdlib.h"
#include "string.h"

u32 enumerate_labels(Expression * e  , u32 len){

  u32 counter = 0;
  for(u32 i = 0 ;  i < len ; i++){
    if(e[i].m1.name[0] == '_'){
      counter ++;
    }
  }

  return counter;
}

Label_table * find_labels (Expression * e  , u32 len ){

  u32 table_len = enumerate_labels(e , len);
  
  Label_table * l = (Label_table *) calloc (table_len , sizeof(Label_table) );

  for(u32 i = 0 ; i < table_len ; i++){
    l[i].name = calloc(32,sizeof(char));
  }
  u32 j = 0;
  for(u32 i = 0 ; i < len ; i++){
    if(e[i].m1.name[0] == '_'){
      l[j].index = i;
      strcpy(l[j].name ,e[i].m1.name );
      j++;
    }
  }

  for(int i = 0 ; i  < j ;i++){
    printf("found(%s) at %d \n",l[i].name , l[i].index);
  }

  return l;
  
}


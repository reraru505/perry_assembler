#pragma once

#include "mytypes.h"
#include "loader.h"
#include "parser.h"
#include "stdio.h"

void pasm(char * src ){

  Length_tracker * lt = (Length_tracker *) malloc(sizeof(Length_tracker));
  
  Node * n = loader(src , lt);
  
  
  Token * tokarr = flatten_token_list(n, lt);
   

  for(int i = 0 ; i < lt->token_array_len ;i++){
    
    printf("{ type = %d  name = %s}\n",tokarr[i].type , tokarr[i].name);
  }
  
  parse(tokarr, lt->token_array_len);
  
  for(int i = 0 ; i < lt->token_array_len ;i++){

    printf("{ type = %d  name = %s}\n",tokarr[i].type , tokarr[i].name);
  }
  
}

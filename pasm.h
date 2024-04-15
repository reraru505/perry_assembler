#pragma once

#include "mytypes.h"
#include "loader.h"
#include "parser.h"
#include "lexer.h"
#include "stdio.h"
#include "string.h"
#include "mkunits.h"
#include "amchecker.h"
#include "map_label_address.h"
#include "mkbin.h"

void pasm(char * src ){

  Length_tracker * lt = (Length_tracker *) malloc(sizeof(Length_tracker));
  
  Node * n = loader(src , lt);
  
  
  Token * tokarr = flatten_token_list(n, lt);
  

  u32 text_start_index = 0;
  
  for(int i = 0 ; i < lt->token_array_len ;i++){
    
    printf("{ type = %d  name = %s}\n",tokarr[i].type , tokarr[i].name);
    if(!strcasecmp(tokarr[i].name , ".text")){
      text_start_index = i;
    }
  }
  
  parse(tokarr, lt->token_array_len , text_start_index);
  
  for(int i = text_start_index ; i < lt->token_array_len ;i++){

    printf("{ type = %d  name = %s}\n",tokarr[i].type , tokarr[i].name);
    
  }

  Expression * exparr = make_expression_array(tokarr,text_start_index + 1 , lt->token_array_len);

  u32 explen  = enumerate_expressions(tokarr,text_start_index , lt->token_array_len);


  
  
  for(u32 i  = 0 ; i < explen ; i++){
    printf (" Expression { [%s]   [%s]   [%s]   [%s] }\n",give_token_name(exparr[i].m1),
	    give_token_name(exparr[i].m2),
	    give_token_name(exparr[i].m3),
	    give_token_name(exparr[i].m4)); 

  }

  UNIT *  unitarr =  make_units(exparr , explen);

  for ( u32 i = 0 ; i < explen ; i++){
    printf(" opcode = %d , a1 = %s , a2 = %s , a3 = %s \n",
	   unitarr[i].opcode ,
	   unitarr[i].arg1_data,
	   unitarr[i].arg2_data,
	   unitarr[i].arg3_data);

  }


  u32 llen = enumerate_labels(exparr , explen);

  Label_table * l = find_labels(exparr , explen);

  IP * iparr = make_instructions(unitarr, explen , l , llen);

  for(u32 i = 0 ; i < explen ; i++){
    printf(" mode = %d | opcode = %d | argx = %d | argy = %d | argz = %d  \n" , iparr[i].mode,
	   iparr[i].code,iparr[i].argx,iparr[i].argy,iparr[i].argz);
  }
  
  
}

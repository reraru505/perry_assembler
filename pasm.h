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
#include "map_data_address.h"

void pasm(char * src ){

  IP file_header;
  
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

  

  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////                                                                              ///////////////
  ///////////                              DATA SEGMENT                                    ///////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  

  u32 num_data = enumerate_data(tokarr, text_start_index);

  u32 * return_array = (u32 *) calloc(num_data , sizeof(u32));
  
  IP * data = map_data_and_get_addresses(return_array , tokarr , text_start_index , num_data );

  Data_address_table * d = find_data_addresses( return_array , num_data , tokarr , text_start_index);


  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////                                                                              ///////////////
  ///////////                              TEXT SEGMENT                                    ///////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  parse(tokarr, lt->token_array_len , text_start_index , d , num_data);
  
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

  IP * iparr = make_instructions(unitarr, explen , l , llen ,  d , num_data);

  for(u32 i = 0 ; i < explen ; i++){
    printf(" mode = %d | opcode = %d | argx = %d | argy = %d | argz = %d  \n" , iparr[i].mode,
	   iparr[i].code,iparr[i].argx,iparr[i].argy,iparr[i].argz);
  }

  IP header = gen_header(num_data , explen , l  , llen);

  write_binary(&header , data , iparr  , num_data , explen);
  
  
}

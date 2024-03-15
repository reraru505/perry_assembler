#pragma once

#include "mytypes.h"
#include "stdlib.h"
#include "string.h"
#include "map_label_address.h"

u32 resolve_args(Token_type t , char * c , Label_table * l , u32 llen){

  if(t == DONT_CARE){
    return 0;
  }else if(t == REGISTER ){
    if(!strcasecmp(c , "%a")){
      return 0;
    }else if(!strcasecmp(c , "%b")){
      return 1;
    }else if(!strcasecmp(c , "%c")){
      return 2;
    }else if(!strcasecmp(c , "%d")){
      return 3;
    }else if(!strcasecmp(c , "%e")){
      return 4;
    }else if(!strcasecmp(c , "%f")){
      return 5;
    }else if(!strcasecmp(c , "%g")){
      return 6;
    }else if(!strcasecmp(c , "%h")){
      return 7;
    }
  }else if(t == LITERAL){
    return atoi(c);
    
  }else if(t == ADDRESS){
    
    char buff[32];
    int j = 0;
    for(int i = 1 ; i < 32 ; i++ , j++){
      buff[j] = c[i]; 
    }

    return atoi(buff);
    
  }else if ( t == LABEL){

    for(u32 i = 0 ; i < llen ; i++){
      if(!strcasecmp(l[i].name,c)){
	return l[i].index;
      }
    }
    
  }

}


IP * make_instructions(UNIT * u , u32 len , Label_table * l , u32 llen){

  IP * iparr =(IP *) calloc(len , sizeof(IP));
  
  for(u32 i = 0 ; i < len ; i++){
    iparr[i].mode = give_addressing_mode(u[i]);
    iparr[i].code = u[i].opcode;
    iparr[i].argx = resolve_args(u[i].arg1,u[i].arg1_data , l , llen);
    iparr[i].argy = resolve_args(u[i].arg2,u[i].arg2_data , l , llen);
    iparr[i].argz = resolve_args(u[i].arg3,u[i].arg3_data , l , llen);
  }

  return iparr;

}

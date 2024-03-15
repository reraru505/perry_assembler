#include <stdio.h>
#include <stdlib.h>
#include "mytypes.h"
#include "string.h"

u32 enumerate_expressions(Token * tokarr , u32 start , u32 len){

  u32 counter = 0;
  
  for(int i = start ; i < len ; i++ ){
    if(tokarr[i].type == OPCODE or tokarr[i].type == LABEL){
      counter++;
    }
    if(!strcasecmp(tokarr[i].name,"call") or
       !strcasecmp(tokarr[i].name,"jz") or
       !strcasecmp(tokarr[i].name,"jl") or
       !strcasecmp(tokarr[i].name,"je") or
       !strcasecmp(tokarr[i].name,"jne")){
      counter--;
    }
  }

  return counter;
}



Expression * make_expression_array(Token * tokarr , u32 start , u32 len ){

  u32 exp_arr_len = enumerate_expressions(tokarr , start , len);

  Expression * exp_arr = (Expression *) calloc(exp_arr_len ,sizeof(Expression));

  for(u32 i = 0 ; i < exp_arr_len ; i++){
    exp_arr[i].m1.name = (char *) calloc(32 ,sizeof(char));
    exp_arr[i].m2.name = (char *) calloc(32 ,sizeof(char));
    exp_arr[i].m3.name = (char *) calloc(32 ,sizeof(char));
    exp_arr[i].m4.name = (char *) calloc(32 ,sizeof(char));
    
  }
  
  for(u32 i = 0 ; i < exp_arr_len ; i++){

    exp_arr[i].m1.type = DONT_CARE;
    exp_arr[i].m2.type = DONT_CARE;
    exp_arr[i].m3.type = DONT_CARE;
    exp_arr[i].m4.type = DONT_CARE;

    
    if(tokarr[start].type == OPCODE and start < len ){
      exp_arr[i].m1.type = tokarr[start].type;
      strcpy(exp_arr[i].m1.name,tokarr[start].name);
      start++;

      if((tokarr[start].type != OPCODE ) and start < len){
	exp_arr[i].m2.type = tokarr[start].type;
	strcpy(exp_arr[i].m2.name,tokarr[start].name);
	start++;
      }
      
      if((tokarr[start].type != OPCODE and tokarr[start].type != LABEL) and start < len){
	exp_arr[i].m3.type = tokarr[start].type;
        strcpy(exp_arr[i].m3.name,tokarr[start].name);
	start++;
      }

      if((tokarr[start].type != OPCODE and tokarr[start].type != LABEL) and start < len){
	exp_arr[i].m4.type = tokarr[start].type;
        strcpy(exp_arr[i].m4.name,tokarr[start].name);
	start++;
      }
      
    }else if(tokarr[start].type == LABEL and start < len){
      exp_arr[i].m1.type = tokarr[start].type;
      strcpy(exp_arr[i].m1.name,tokarr[start].name);
      start++;
    }
    
  }

  return exp_arr;
  

}

//debug mode function
char * give_token_name(Token token){

  if(token.type == DONT_CARE){
    return "NULL";
  }
  return token.name;

}

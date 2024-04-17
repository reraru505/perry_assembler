#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mytypes.h"

#define NO_OF_OPCODES 17


void init_optable(char ** s)
{
  s[0]= "mov";
  s[1]= "hlt";
  s[2]= "print";
  s[3]= "pop";
  s[4]= "push";
  s[5]= "add";
  s[6]= "sub";
  s[7]= "mul";
  s[8]= "div";
  s[9]= "call";
  s[10]="je";
  s[11]="mod";
  s[12]="ret";
  s[13]="cmp";
  s[14]="jne";
  s[15]="jge";
  s[16]="jle";
}



bool isOpcode(char * s, char **table){
  
  for (int i = 0 ; i < NO_OF_OPCODES ; i++){
    
    if(strcasecmp(s,table[i])==0){
      return true;
    }
    
 }
  return false;
}


bool isReg(char * s){

  if(s[0] == '%'){
    return true;
  }

  return false;
  
}

bool isAddress(char * s){

  if(s[0] == '&'){
    return true;
  }

  return false;
  
}


bool isDirective(char * s){

  if(s[0] == '.'){
    return true;
  }

  return false;
  
}

bool isLabel(char * s){

  if(s[0] == '_'){
    return true;
  }

  return false;
}

bool isData(Data_address_table * d , u32 len , char * s){

  for(int i = 0 ;  i < len ;i++){
    if(!strcasecmp(s , d[i].name)){
      return true;
    }
  }

  return false;
}

Token_type checker(char *s, char **table ,Data_address_table * d , u32 l  ){

  if(isReg(s))
    return REGISTER;
  else if(isAddress(s))
    return ADDRESS;
  else if(isDirective(s)) 
    return DIRECTIVE;
  else if(isLabel(s))
    return LABEL;
  else if(isOpcode(s,table))
    return OPCODE;
  else if(isData(d , l , s))
    return DATA;
  else
    return LITERAL;
}

void parse(Token * tokarr ,int len , u32 start , Data_address_table * d , u32 l){
  
  char ** opt = calloc(NO_OF_OPCODES,sizeof(char*));
  
  for(int i = 0 ; i < NO_OF_OPCODES ; i++){
   
    opt[i] = calloc(32,sizeof(char));
  }
  
  init_optable(opt);

  
 // for (int i = 0 ; i < NO_OF_OPCODES ; i++){
 //   printf("%s \n",opt[i]);
 //   
 // }
  
  for (u32  i  = start ; i < len ;i++){
    printf("checking for [%s]\n",tokarr[i].name);
    tokarr[i].type = checker(tokarr[i].name , opt ,  d , l);  
  
  }
  
}



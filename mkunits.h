#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "mytypes.h"




OPC check_opcode(char * name){

  if(!strcasecmp(name , "mov")){
    return MOV;
  }else if(!strcasecmp(name , "hlt")){
    return HLT;
  }else if(!strcasecmp(name , "call")){
    return CALL;
  }else if(!strcasecmp(name , "ret")){
    return RET;
  }else if(!strcasecmp(name , "je")){
    return JE;
  }else if(!strcasecmp(name , "jl")){
    return JL;
  }else if(!strcasecmp(name , "jg")){
    return JG;
  }else if(!strcasecmp(name , "jne")){
    return JNE;
  }else if(!strcasecmp(name , "cmp")){
    return CMP;
  }else if(!strcasecmp(name , "clf")){
    return CLF;
  }else if(!strcasecmp(name , "push")){
    return PUSH;
  }else if(!strcasecmp(name , "pop")){
    return POP;
  }else if(!strcasecmp(name , "syscall")){
    return SYSCALL;
  }else if(!strcasecmp(name , "add")){
    return ADD;
  }else if(!strcasecmp(name , "sub")){
    return SUB;
  }else if(!strcasecmp(name , "div")){
    return DIV;
  }else if(!strcasecmp(name , "mul")){
    return MUL;
  }else if(!strcasecmp(name , "mod")){
    return MOD;
  }else if(name[0] == '_') {
    return OP_LABEL;
  }
  
  
}

UNIT * make_units(Expression * e , u32 len ){

  UNIT * retval = (UNIT *) calloc(len , sizeof(UNIT));
  
  for (u32 i = 0 ; i < len ; i++){
    retval[i].arg1_data = calloc(32, sizeof(char));
    retval[i].arg2_data = calloc(32, sizeof(char));
    retval[i].arg3_data = calloc(32, sizeof(char));
  }

  for(u32 i = 0 ;  i < len ; i++){

    retval[i].opcode = check_opcode(e[i].m1.name);

    retval[i].arg1 = e[i].m2.type;
    retval[i].arg2 = e[i].m3.type;
    retval[i].arg3 = e[i].m4.type;

    strcpy(retval[i].arg1_data ,e[i].m2.name);
    strcpy(retval[i].arg2_data ,e[i].m3.name);
    strcpy(retval[i].arg3_data ,e[i].m4.name);
    
  }

  return retval;

}

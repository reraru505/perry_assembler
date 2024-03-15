#pragma once
#include "mytypes.h"

AMODE mov_am(UNIT u){

  if(u.arg1 == REGISTER and u.arg2 == LITERAL ){
    return IMMEDIATE;
  }
  
  if(u.arg1 == REGISTER and u.arg2 == REGISTER ){
    return REGISTER_DIRECT;
  }

  
  if(u.arg1 == REGISTER and u.arg2 == ADDRESS ){
    return INDIRECT;
  }
  
}

AMODE push_am(UNIT u){

  if(u.arg1 == REGISTER ){
    return REGISTER_DIRECT;
  }
  
  if(u.arg1 == ADDRESS ){
    return INDIRECT;
  }

  
  if(u.arg1 == LITERAL ){
    return IMMEDIATE;
  }
  
  
}



AMODE give_addressing_mode(UNIT u){

  switch (u.opcode){
  case MOV :
    return mov_am(u);
  case HLT :
    return IMPLIED;
  case CALL :
    return IMPLIED;
  case RET :
    return IMPLIED;
  case JE :
    return IMPLIED;
  case JL :
    return IMPLIED;
  case JNE :
    return IMPLIED;
  case CMP :
    return REGISTER_DIRECT;
  case CLF:
    return IMPLIED;
  case PUSH:
    return push_am(u);
  case POP:
    return REGISTER_DIRECT;
  case SYSCALL:
    return IMPLIED;
  case ADD:
    return REGISTER_DIRECT;
  case SUB:
    return REGISTER_DIRECT;
  case DIV:
    return REGISTER_DIRECT;
  case MUL:
    return REGISTER_DIRECT;
  case MOD:
    return REGISTER_DIRECT;
  case OP_LABEL:
    return IMPLIED;
  }
  

}

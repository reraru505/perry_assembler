#pragma once
#include "stdint.h"

#define STACK_SIZE 10000000

typedef enum AM{

  IMPLIED,           //no operand 
  IMMEDIATE,         //literal is a data value
  REGISTER,          //register contains a data value
  REGISTER_INDIRECT, //register contains an address value
  INDIRECT           //literal is an address value 
  
}AM;

typedef enum FLAG{
  NOT_SET,
  EQUAL,
  GREATER,
  LESSER
}FLAG;

typedef enum OPC{

  MOV,
  HLT,
  CALL,
  RET,
  JE,
  JL,
  JG,
  JNE,
  CMP,
  CLF,
  PUSH,
  POP,

  SYSCALL,

  ADD,
  SUB,
  DIV,
  MUL,
  MOD,
  
  
  
}OPC;

typedef struct IP{

  uint32_t mode;
  uint32_t code;
  uint32_t argx;
  uint32_t argy;
  uint32_t argz;
  
}IP;

typedef struct DATA{
  uint32_t * stack;
  
}DATA;

typedef struct PVM{

  uint32_t pc;
  uint32_t ret;
  IP ip;
  
  uint32_t gpr[8];

  FLAG flag;
  
  uint32_t sp;
  uint32_t bp;
  uint32_t st;
  uint32_t sb;
  
}PVM;

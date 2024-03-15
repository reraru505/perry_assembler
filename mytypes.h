#pragma once

//simple types

#define or ||
#define and &&

typedef unsigned char  u8;
typedef unsigned int  u32;
typedef unsigned long u64;

typedef float  f32;
typedef double f64;

typedef u8 bool;
#define true 1
#define false 0


//enums 

typedef enum {
    IMPLIED,
    IMMEDIATE,
    REGISTER_DIRECT,
    REGISTER_INDIRECT,
    INDIRECT,
    INVALID
} AMODE;

typedef enum Token_type {
  ADDRESS,
  OPCODE,
  REGISTER,
  LABEL,
  LITERAL,
  DIRECTIVE,
  DONT_CARE
} Token_type;

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

  OP_LABEL
  
  
}OPC;


//complex types

typedef struct Length_tracker{
  int token_list_len;
  int token_array_len;
  int code_len;
  
} Length_tracker;


typedef struct Token {

  Token_type type;
  char * name;
  
} Token;

typedef struct Node{

  struct Node * next;
  Token token;
  
} Node;


typedef struct Expression{
    Token m1;
    Token m2;
    Token m3;
    Token m4;
} Expression;

typedef struct UNIT{

  OPC opcode;
  
  Token_type arg1;
  Token_type arg2;
  Token_type arg3;

  char * arg1_data;
  char * arg2_data;
  char * arg3_data;

} UNIT;

typedef struct Label_table{
  char * name;
  u32 index;
} Label_table;

typedef struct IP{

  u32 mode; 
  u32 code; 
  u32 argx;
  u32 argy;
  u32 argz;
  
}IP;


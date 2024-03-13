#pragma once

//simple types

typedef unsigned char  u8;
typedef unsigned int  u32;
typedef unsigned long u64;

typedef float  f32;
typedef double f64;

typedef u8 bool;
#define true 1
#define false 0

//enums 
typedef enum Token_type {
  ADDRESS,
  OPCODE,
  REGISTER,
  LABEL,
  LITERAL,
  DIRECTIVE
} Token_type;

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

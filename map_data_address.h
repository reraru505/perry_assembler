#pragma once

#include "mytypes.h"
#include "stdio.h"
#include "string.h"

u32 enumerate_data(Token * arr , u32 len){

  u32 no_of_data = 0;
  for( u32 i = 0 ; i < len ; i++  ){
    if(!strcasecmp("db",arr[i].name)){
      no_of_data++;
    }
    
  }

  return no_of_data;

}


IP * map_data_and_get_addresses(u32 * return_array , Token * arr , u32 len , u32 num_of_data){

  u32 ret_array_index = 0;

  char * big_string_buffer = (char *) calloc(10000, sizeof(char ));
  u32 big_string_buffer_counter = 0;
  
  
  for( u32 i = 1 ; i < len ; i++  ){

    if(!strcasecmp("db",arr[i].name)){
      return_array[ret_array_index] = big_string_buffer_counter;
      i++;
    }else{
      u32 name_len = strlen(arr[i].name);
      for(int j = 0 ; j < name_len ; j++){
	big_string_buffer[big_string_buffer_counter] = arr[i].name[j];
	big_string_buffer_counter++;
      }
      big_string_buffer[big_string_buffer_counter] = ' ';
      big_string_buffer_counter++;
    }
    
  }

  u32 buffer_len = strlen(big_string_buffer);

  u32 ipptrlen = 0;
  if(buffer_len % 4 == 0){
    ipptrlen = buffer_len/ 4;
  }else{
    ipptrlen = (buffer_len/ 4) + 1;
  }

  IP * ipbuffer = (IP *) calloc(ipptrlen , sizeof(IP));

  char * buffer = (char * ) ipbuffer;

  for(int i = 0 ; i < buffer_len ; i++){
    buffer[i] = big_string_buffer[i];
  }

  free(big_string_buffer);

  IP * retval = (IP *) buffer;

  return retval;
  
  
}


Data_address_table * find_data_addresses(u32 * index_array , u32  len, Token * tokarr , u32 tlen ){

  Data_address_table * table = (Data_address_table *) calloc(len , sizeof(Data_address_table));

  for(int i = 0 ; i < len ; i++){

    table[i].name = (char *) calloc(32, sizeof(char ));
    table[i].index = index_array[i];

  }
  
  int table_index = 0;
  
  for(int i = 0 ; i < tlen ; i++){

    if(!strcasecmp(tokarr[i].name,"db")){
      strcpy(table[table_index].name , tokarr[i+1].name);
      table_index++;
    }
    
  }

  return table;
}

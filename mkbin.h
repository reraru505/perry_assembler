#pragma once

#include "mytypes.h"
#include "stdlib.h"
#include "string.h"
#include "map_label_address.h"

u32 resolve_args(Token_type t , char * c , Label_table * l , u32 llen , Data_address_table * d , u32 dlen){

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
    
  }else if( t == DATA){

    for(u32 i = 0 ; i < dlen ; i++){
      if(!strcasecmp(d[i].name,c)){
	return d[i].index;
      }
    }
    
  }

}

IP gen_header(u32 data_len , u32 text_len , Label_table * l , u32 llen){

  IP header;
  header.mode = data_len + text_len;
  header.code = data_len;
  header.argx = text_len;
  
  for(u32 i = 0 ; i < llen ; i++){
    if(!strcasecmp(l[i].name,"_start")){
      header.argy = l[i].index;
    }
  }

  header.argz = 0;

  return header;
  
}

IP * make_instructions(UNIT * u , u32 len , Label_table * l , u32 llen , Data_address_table * d , u32 dlen){

  IP * iparr =(IP *) calloc(len , sizeof(IP));
  
  for(u32 i = 0 ; i < len ; i++){
    iparr[i].mode = give_addressing_mode(u[i]);
    iparr[i].code = u[i].opcode;
    iparr[i].argx = resolve_args(u[i].arg1,u[i].arg1_data , l , llen , d , dlen);
    iparr[i].argy = resolve_args(u[i].arg2,u[i].arg2_data , l , llen , d , dlen);
    iparr[i].argz = resolve_args(u[i].arg3,u[i].arg3_data , l , llen , d , dlen);
  }

  return iparr;

}

void write_binary(IP * header , IP * data , IP * text , u32 datalen , u32 texlen){

  u32 all_len = datalen + texlen + 1;
  char * buffer = (char *) calloc(all_len , sizeof(IP));

  char * forheader = (char *) header;
  char * fordata = (char * ) data;
  char * fortext = (char *) text;

  u32 w = 0;
  u32 x = sizeof(IP)/sizeof(char);
  u32 y = (sizeof(IP) * datalen ) /sizeof(char);
  u32 z = (sizeof(IP) * texlen )/sizeof(char);
  
  for(u32 i = 0 ;  i < x ; i++){
    buffer[w] = forheader[i];
    w++;
  }

  
  for(u32 i = 0 ;  i < y ; i++){
    buffer[w] = fordata[i];
    w++;
  }

  
  for(u32 i = 0 ;  i < z ; i++){
    buffer[w] = fortext[i];
    w++;
  }
  
  IP * buffer_for_bin = (IP *) buffer;
    
  for(int i = 0 ; i < all_len ; i++){
    printf(" %d ",buffer_for_bin[i].mode);
    printf(" %d ",buffer_for_bin[i].code);
    printf(" %d ",buffer_for_bin[i].argx);
    printf(" %d ",buffer_for_bin[i].argy);
    printf(" %d \n",buffer_for_bin[i].argz);
    
  }

  
  free(data);
  free(text);

  FILE * f = fopen("b.out", "wb");

  fwrite(buffer_for_bin , sizeof(IP) ,all_len ,f);

  fclose(f);

  free(buffer_for_bin);

}

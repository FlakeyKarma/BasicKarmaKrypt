#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENCRYPT_DATA 0x1
#define DECRYPT_DATA 0x0
#define __VERBOSE 0x1
#define false 0b0
#define true 0b1

void print_binary(unsigned char character_to_print){
  for(unsigned char i = 0; i < 8; i++){
    if((character_to_print>>i)&0x1){
      printf("1");
    }else{
      printf("0");
    }
  }
  printf("\n");
}

//Basic Binary Rotation and BitFlip Ops to encrypt. Shouldn't be used for anything serious.
//Based on ASCII table - This function determines which direction(left_direction=>[Left = 1, Right = 0]) to rotate char (char_to_rot) an amount of times (bit_rotate_count)
char rot_char(unsigned char char_to_rot, unsigned char psk_char, unsigned char left_direction, unsigned char verbose){
  unsigned char temp_char,
                true_rotate_num = (unsigned char)psk_char%7,
                temp_bit;
  for(unsigned char i = 0; i < true_rotate_num; i++){
    temp_bit = 0;
    if(!left_direction){
      //Take bit from msb of char_to_rot and store in temp_bit
      temp_bit = char_to_rot>>0x7;
      //Rotate left one place
      char_to_rot<<=0x1;
      //Place temp_bit at lsb of char
      char_to_rot |= temp_bit;
    }else{
      //Take lsb from char_to_rot and store in temp_bit
      temp_bit = char_to_rot&0x1;
      //Rotate all bits right
      char_to_rot>>=0x1;
      char_to_rot&=0x7F;
      //Place temp_bit in temp_char as lsb for rotation
      temp_char = temp_bit;
      //Place lsb as msb
      temp_char<<=0x07;
      //Set msb in char_to_rot
      char_to_rot |= temp_char;
    }
  }
  //BitFlip
  char_to_rot ^= 0xFF;
  if(verbose) printf("%c\n", char_to_rot);
  return char_to_rot;
}

//Encrypt or Decrypt string
char *crypt_string(unsigned char crypt_choice, char *crypt_string, char *passkey, unsigned char line_idx, char verbose){
  //Length of
  unsigned char u_len = strlen(crypt_string),
                p_len = strlen(passkey);
  char *temp_new_str = (char *)calloc(strlen(crypt_string), sizeof(char));
  for(unsigned char j = 0; j < u_len; j++)
    for(unsigned char i = 0; i < p_len; i++){
      if(verbose){
        printf("%s\n%d\n%d\n", crypt_string, u_len, p_len);
        #ifdef _WIN64
          system("CLS");
        #else
          system("clear");
        #endif
      }
      temp_new_str[j] = rot_char(crypt_string[j], rot_char(passkey[i], j*u_len+line_idx, DECRYPT_DATA, verbose)-line_idx, crypt_choice, verbose);
    }
  return temp_new_str;
}

#include "encrypt_ez.h"

int main(){
       //Cleartext version of string
  char *clear_text = (char *)calloc(15, sizeof(char)),
       //Password
       *password = (char *)calloc(5, sizeof(char)),
       //Encrypted string
       *encrypted,
       //Decrypted string
       *decrypted;
  clear_text = "we the people\0";
  password = "the longer the stronger\0";
  encrypted = (char *)calloc(strlen(clear_text), sizeof(char));
  decrypted = (char *)calloc(strlen(clear_text), sizeof(char));
  encrypted = crypt_string(ENCRYPT_DATA, clear_text, password);
  decrypted = crypt_string(DECRYPT_DATA, encrypted, password);
  printf("Original:%s\n", clear_text);
  printf("Password:%s\n", password);
  printf("Encrypted:%s\n", encrypted);
  printf("Decrypted:%s\n", decrypted);
  return 0;
}

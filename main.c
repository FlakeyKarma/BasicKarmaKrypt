#include "encrypt_ez.h"

int main(){
  char a = 'a',
       b = rot_char(a, 'a', 0),
       //Cleartext version of string
       *clear = (char *)calloc(15, sizeof(char)),
       //Password
       *psk = (char *)calloc(5, sizeof(char)),
       //Encrypted string
       *enc,
       //Decrypted string
       *dec;
  clear = "we the people\0";
  psk = "asdf\0";
  enc = (char *)calloc(strlen(clear), sizeof(char));
  dec = (char *)calloc(strlen(clear), sizeof(char));
  enc = crypt_string(ENCRYPT_DATA, clear, psk);
  dec = crypt_string(DECRYPT_DATA, enc, psk);
  printf("%s=>%s", clear, enc);
  printf("\n");
  printf("%s<=%s", dec, enc);
  return 0;
}

#include <dirent.h>
#include <errno.h>
#include <unistd.h>

#include "encrypt_ez.h"
#define __TEST false

#define __MAX_LINE_LENGTH 64

char checkPath(char *path){
     //DIR* file_path = opendir(path);
     //Path exists
     printf("%s\n", path);
     printf("ACC - %d\n", access(path, F_OK));
     if (!access(path, F_OK)) {
          //closedir(file_path);
          return 0;
     //Doesn't exist
     } else if (ENOENT == errno) {
          fprintf(stderr, "checkPath:The path does not exist - %s\n", path);
          return 1;
     //Other error
     } else {
          fprintf(stderr, "checkPath:Error Unknown - %s\n", path);
          return 2;
     }

}

int main(int argc, char **argv){
     //Cleartext version of string
     char *clear_text,
     //Password
     *password,
     //Encrypted string
     *encrypted,
     //Set verbosity
     verbose = 0;

     if(__TEST){
          clear_text = (char *)calloc(64, sizeof(char));
          password = (char *)calloc(5, sizeof(char));
          //Decrypted string
          char *decrypted;
          clear_text = "we the people\0";
          password = "the longer the stronger\0";
          decrypted = (char *)calloc(strlen(clear_text), sizeof(char));
          encrypted = crypt_string(ENCRYPT_DATA, clear_text, password, 12, verbose);
          decrypted = crypt_string(DECRYPT_DATA, encrypted, password, 12, verbose);
          printf("Original:%s\n", clear_text);
          printf("Password:%s\n", password);
          printf("Encrypted:%s\n", encrypted);
          printf("Decrypted:%s\n", decrypted);
          return 0;
     }else{
          //Set file pointers
          FILE *fp_password,
               *fp_input,
               *fp_output;

          char verbose = false,
               decrypt = false,
               input_file = false;
          
          password = (char *)calloc(__MAX_LINE_LENGTH, sizeof(char));
          clear_text = (char *)calloc(__MAX_LINE_LENGTH, sizeof(char));

          for(char i = 0; i < argc; i++){
               if((!strcmp(argv[i], "-h") | !strcmp(argv[i], "--help"))){
                    printf("BasicKarmaKrypt v1.0\n");
                    printf("bkk [-h, --help][-e,--encrypt][-d,--decrypt][-s,--string STRING][-p,--password PATH][-i,--input PATH][-o,--output PATH][-v,--verbose]\n");
                    printf("\t-h,--help\t\tPrint this menu.\n");
                    printf("\t-e,--encrypt\t\tEncrypt the message. (default)\n");
                    printf("\t-d,--decrypt\t\tDecrypt the message.\n");                    
                    printf("\t-s,--string STRING\tDirect string argument encryption.\n");
                    printf("\t-p,--password PATH\tPath to the file containing the password for encryption.\n");
                    printf("\t-i,--input PATH\tPath to the file of contents being encrypted.\n");
                    printf("\t-o,--output PATH\tPath to the file that the output will be written to.\n");
                    printf("\t-v,--verbose\tIncrease verbosity of output.\n");
                    exit(0);
               }
               if((!strcmp(argv[i], "-s") | !strcmp(argv[i], "--string"))){
                    i++;
                    clear_text = argv[i];
                    clear_text[strlen(clear_text)] = 0;
               }
               if((!strcmp(argv[i], "-p") | !strcmp(argv[i], "--password"))){
                    i++;
                    switch(checkPath(argv[i])){
                         case 0:
                              fp_password = fopen(argv[i], "r");

                              if(!fp_password){
                                   perror("Password file not found!\n");
                                   return 1;
                              }

                              fgets(password, sizeof(password)+1, fp_password);

                              password[strlen(password)] = 0;

                              break;
                         default:
                              return 1;
                    }
               }
               if((!strcmp(argv[i], "-i") | !strcmp(argv[i], "--input"))){
                    i++;
                    switch(checkPath(argv[i])){
                         case 0:
                              fp_input = fopen(argv[i], "r");

                              input_file = true;

                              if(!fp_input){
                                   perror("Input file not found!\n");
                                   return 1;
                              }
                              
                              /*
                              fgets(clear_text, sizeof(clear_text), fp_input);

                              clear_text[strlen(clear_text)] = 0;
                              */
                              break;
                         default:
                              return 1;
                    }
               }
               if((!strcmp(argv[i], "-o") | !strcmp(argv[i], "--output"))){
                    i++;
                    switch(checkPath(argv[i])){
                         case 0:
                              fp_output = fopen(argv[i], "w+");

                              if(!fp_output){
                                   perror("Output file not found!\n");
                                   return 1;
                              }

                              break;
                         default:
                              return 1;
                    }
               }
               if((!strcmp(argv[i], "-v") | !strcmp(argv[i], "--verbose"))) verbose = true;
               if((!strcmp(argv[i], "-d") | !strcmp(argv[i], "--decrypt"))) decrypt = true;
          }


          if(input_file){
               size_t len = __MAX_LINE_LENGTH;

               unsigned char line_idx = 0;

               while(!feof(fp_input))
                    if(fgets(clear_text, sizeof(clear_text), fp_input)){
                         printf("%s", clear_text);
                         printf("%s\n", crypt_string(decrypt, clear_text, password, line_idx++, verbose));
                    }
          }else{
               printf("%s\n", crypt_string(decrypt, clear_text, password, 0, verbose));
          }
     }
}

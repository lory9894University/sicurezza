#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#define KEYLEN 32
#define TEXTLEN 10000
#define MAX_TEXT_PATH 100
#define MAX_KEY_PATH 100

//openssl enc -aes-256-cbc -k prova -P -md sha1

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

void encrypt(unsigned char *text, int text_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext);

void decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *text);

void set_variables(char key_file[16], char text_file[16], int *encrypt_flag, int argc, char **argv);

void print_help() {
  printf("Usage: openssl_api [options] [file]\n");
  printf("Options:\n");
  printf("  -e, --encrypt\t\tEncrypt the file\n");
  printf("  -d, --decrypt\t\tDecrypt the file\n");
  printf("  -h, --help\t\tPrint this help\n");

}

int main (int argc, char *argv[])
{
  char key_file[MAX_KEY_PATH];
  char text_file[MAX_TEXT_PATH];
  int encrypt_flag = 0;
  FILE *key_file_ptr;
  char key[KEYLEN];
  char *line = NULL;
  size_t len = 0;

  set_variables(key_file, text_file, &encrypt_flag, argc, argv);

  //get variable key from file key_file
  if ( ( key_file_ptr = fopen(key_file, "rb")) != NULL) {
      fread(key, 1, KEYLEN, key_file_ptr);
      fclose(key_file_ptr);
  } else {
    printf("Error: key file not found\n");
    exit(1);
  }

  /* A 128 bit random IV */
  unsigned char *iv = (unsigned char *)"5893781563109275";

  //get text from file text_file
  FILE *text_file_ptr;
  char text[TEXTLEN];
  if (( text_file_ptr = fopen(text_file, "rb")) != NULL) {
    fread(text, 1, KEYLEN, text_file_ptr);
    fclose(text_file_ptr);
  }
  else {
    printf("Error: text file not found\n");
    exit(1);
  }

  if (encrypt_flag) {
    unsigned char ciphertext[TEXTLEN];
    encrypt(text, strlen(text), key, iv, ciphertext);
    printf("%s",ciphertext);

  }else {
    unsigned char decryptedtext[TEXTLEN];
    decrypt(text, strlen(text), key, iv,
                                decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[strlen(decryptedtext)] = '\0';
    printf("%s", decryptedtext);

  }

  return 0;
}

void set_variables(char key_file[16], char text_file[16], int *encrypt_flag, int argc, char **argv) {
  if (argc == 1) {
    printf("Insert key path\n");
    scanf("%s", key_file);
    printf("Insert text file path\n");
    scanf("%s", text_file);
    printf("Encrypt or decrypt? (0/1)\n");
    scanf("%d", encrypt_flag);
    if (*encrypt_flag != 0 && *encrypt_flag != 1) {
      printf("Invalid input");
      exit(1);
    }
  }
  else if (argc == 4) {
    strcpy(key_file,argv[1]);
    strcpy(text_file, argv[3]);
    //if argv[2] is --decrypt, encrypt_flag = 0 else if argv[2] is --encrypt, encrypt_flag = 1
    *encrypt_flag = (strcmp(argv[2], "--decrypt") == 0) ? 0 : 1;
  }
  else {
    print_help();
    exit(1);
  }

}


void encrypt(unsigned char *text, int text_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  /*
   * Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /*
   * Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, text, text_len))
    handleErrors();



  /*
   * Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    handleErrors();

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

}

void decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *text)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  /*
   * Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if(1 !=
  (ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /*
   * Provide the message to be decrypted, and obtain the text output.
   * EVP_DecryptUpdate can be called multiple times if necessary.
   */
  if(1 != EVP_DecryptUpdate(ctx, text, &len, ciphertext, ciphertext_len))
    handleErrors();

  /*
   * Finalise the decryption. Further text bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, text + len, &len))
    handleErrors();

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

}

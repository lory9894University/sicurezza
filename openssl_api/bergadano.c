#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>

int main ()
{
	FILE *src=fopen("chiaro","rb");
	FILE *dst=fopen("cifrato","wb");

	EVP_CIPHER_CTX *ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_CipherInit_ex(&ctx, EVP_XXX_cbc(), NULL, NULL, NULL, 1);
	EVP_CIPHER_CTX_set_key_length(&ctx, keylen);
	EVP_CipherInit_ex(&ctx, NULL, NULL, key, vect, 1);

	while (num_read=fread(srcbuf, 1, 1024, src)) {
		EVP_CipherUpdate(&ctx, dstbuf, &num_write, srcbuf, num_read);
		fwrite(dstbuf, 1, num_write, dst);
	}

	EVP_CipherFinal_ex(&ctx, outbuf, &outlen);
	EVP_CIPHER_CTX_cleanup(&ctx);
}

//https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "aes_d.h"

void readCipherText(uint8_t *);
void writePlainText(uint8_t *);


int main(void)
{
    uint8_t key[16] =        { (uint8_t) 0x2b, (uint8_t) 0x7e, (uint8_t) 0x15, (uint8_t) 0x16, (uint8_t) 0x28, (uint8_t) 0xae, (uint8_t) 0xd2, (uint8_t) 0xa6, (uint8_t) 0xab, (uint8_t) 0xf7, (uint8_t) 0x15, (uint8_t) 0x88, (uint8_t) 0x09, (uint8_t) 0xcf, (uint8_t) 0x4f, (uint8_t) 0x3c };
           
    printf("Acme Corporation AES Decryptor System\n");
    printf("\nDecrypting file ciphertext.dat\n");
    
    uint8_t in[]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    readCipherText(in);
    
    struct AES_ctx ctx;

    AES_init_ctx(&ctx, key);
    
    AES_decrypt(&ctx, in);    
    
    writePlainText(in);
    
    printf("Decryption is complete. The plain text is in file PlaintextRecovered.dat\n");
    
    return 0;
}

/*
void readCipherText(uint8_t * ciph) {
    FILE *fp;
    fp = fopen("ciphertext.dat", "rb");

    fread(ciph, 16, 1, fp);
  
    fclose(fp);
}


void writePlainText(uint8_t * ctxt) {
    FILE *fp;
    fp = fopen("PlaintextRecovered.dat", "wb");

    fwrite(ctxt, 16, 1, fp);
  
    fclose(fp);
}
*/


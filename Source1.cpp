#include <gmp.h>
//n = 95163118457906153499715750847001433441357 //Part of Public Key
//e = 65537                                     //Part of Public Key
//d = 5617843187844953170308463622230283376298685 //Private Key

mpz_t ptext;
mpz_t ctext;
mpz_t n;
mpz_t e;
mpz_t d;


mpz_init(ptext);
mpz_init(ctext);

mpz_set_str(ptext, "This is plaintext", 10);

mpz_init_set_str(n, "95163118457906153499715750847001433441357", 10);//Public Key
mpz_init_set_str(e, "65537", 10);                                    //Public Key
mpz_init_set_str(d, "5617843187844953170308463622230283376298685", 10); //Private Key

//Encrypting plaintext and storing it into ctext
mpz_powm(ctext, ptext, e, n);

//Decrypting Ciphertext and storing into ptext
mpz_powm(ptext, ctext, d, n);

void mpz_import(mpz_t rop, size_t count, int order, size_t size, int endian, size_t nails, const void *op)


mpz_import(ctext, 16, 1, 1, 0, 0, buffer);

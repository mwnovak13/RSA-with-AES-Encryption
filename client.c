#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <gmp.h>
#include "aes_e.h"

#define PORT 5000 

void mpz_import(mpz_t rop, size_t count, int order, size_t size, int endian, size_t nails, const void *op){

}


void gmpz_export(void *rop, size_t *countp, int order, size_t size, int endian, size_t nails, const mpz_t op){

}

int main(int argc, char const *argv[]) { 
    printf("This is the client program.\n");
    
	struct sockaddr_in address; 

    int sock = 0; 
	
    struct sockaddr_in serv_addr; 
	
    char *message = "This is a message from the client: Are you listening?"; 
	
    char buffer[2048]; 
	//use mem set to set buffer to all 0's
	memset(&buffer, '0', sizeof(buffer));
	//Creating socket to store connection information
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		printf("\n Socket creation failed \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <=0) { 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 
	//connect to socket with address stored
	if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	//send message
	send(sock, message, strlen(message), 0 ); 
	//Reads in the message sent back.
    read(sock, buffer, sizeof(buffer)); 
	//display message from server
    printf("%s\n", buffer); 
	memset(&buffer, '0', sizeof(buffer));
//*************************************************************Read In RSA Encrypted AES Key***************************************************************
	uint8_t AES_key_client[16] = { (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65, (uint8_t)0x65 };

	mpz_t ptext;
	mpz_t ctext;
	mpz_t n;
	mpz_t e;
	

	//Initilizing ptext, ctext
	mpz_init(ptext);
	mpz_init(ctext);
	//Initilizing and setting n, e. We couldn't figure out how to pass the keys.
	mpz_init_set_str(n, "95163118457906153499715750847001433441357", 10);//Public Key
	mpz_init_set_str(e, "65537", 10);                                    //Public Key


	//Show AES key 
	gmp_printf("\n", AES_key_client, "\n");
	printf("\n The encryption key will now be sent encrypted by RSA.");
	//Place AES_key_client into ptext, encrypt into ctext
	mpz_import(ptext, sizeof(AES_key_client), 1, 1, 0, 0, AES_key_client);
	mpz_powm(ctext, ptext, e, n);

	//Export ctext into buffer to send over the netwrok
	gmpz_export(buffer, NULL, 1, 1, 0, 0, ctext);
	gmp_printf(buffer);
	//Send encrypted buffer(ctext) to server, Reset buffer
	send(new_socket, buffer, sizeof(buffer), 0);
	memset(&buffer, '0', sizeof(buffer));

	printf("\nEncryption key has been sent.");
	printf("\nWaiting on server to send a message.");





	/*
	//Read in server RSA encrypted message with AES key inside
	read(sock, buffer, sizeof(buffer));

	//Import buffer into ctext
	mpz_import(ctext, sizeof(buffer), 1, 1, 0, 0, buffer);
	
	//Decrypt ctext into ptext
	mpz_powm(ptext, ctext, e, n);

	//Export ptext into AES_key_client, print out AES_key_client
	gmpz_export(AES_key_client, NULL, 1, 1, 0, 0, ptext);
	printf("%s\n""The AES key is: ");
	gmp_printf(AES_key_client);
	
	*/


//*********************************************************************************************************************************************************	
	//Initilize ptext, ctext
	//mpz_init(ptext);
	//mpz_init(ctext);


	//We receive the error incomplatable pointer type
	//gmpz_export(AES_key, NULL, 1, 1, 0, 0, key);

	//mpz_import(ctext, 16, 1, 1, 0, 0, buffer);

	//mpz_set_str(ptext, key, sizeof(key);
	//gmp_printf(key);

	//Encrypting ptext into ctext, encrypting using Public key(e) and Public key (n)
	//mpz_powm(ctext, ptext, e, n);
	//Placing ctext into AES_key
	//gmpz_export(buffer, NULL, 1, 1, 0, 0, ctext);
	//Send buffer (Encrypted AES key) to server.c
	//send(sock, buffer, sizeof(buffer), 0);

	//printf("\nEncryption key sent.");
	//gmp_printf(ctext);

	//mpz_import(ctext, 16, 1, 1, 0, 0, buffer);
	//mpz_powm(ctext, ptext, e, n);
	//mpz_powm(ptext, ctext, d, n);
	//mpz_import(ctext, 16, 1, 1, 0, 0, buffer);
	//mpz_export(buffer, NULL, 1, 1, 0, 0, ctext);

    return 0; 
} 

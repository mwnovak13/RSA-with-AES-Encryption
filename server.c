//Import libraries
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <gmp.h>
#include <stdint.h>
#include "aes_e.h"



//Define Constance "PORT" on port 5000
#define PORT 5000

mpz_t ptext;
mpz_t ctext;
mpz_t n;
mpz_t e;
mpz_t d;

void mpz_import(mpz_t rop, size_t count, int order, size_t size, int endian, size_t nails, const void *op) {

}


void gmpz_export(void *rop, size_t *countp, int order, size_t size, int endian, size_t nails, const mpz_t op) {

}


int main(int argc, char const *argv[]) {
	printf("This is the server program.\n");
	//Created a enpoint for communication 
	int server_fd, new_socket;
	//Creating a socket address, needed for communication
	struct sockaddr_in address;

	int opt = 1;
	//Storing the size of the struct in bytes
	int addrlen = sizeof(address);
	//Arrys of 2048 bytes, to store message data
	char buffer[2048];
	char AES_key_serv[2048];
	//char AES_keyDC[2048];
	//char Client_mess;

	//Greeting message
	char *greeting = "This is a message from the server: I am ready to start the cryptographic handshake";
	//Create server side socket into existance: AF_INET = IPv4 socket, SOCK_STREAM = TCP connection
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	//Changes the options of the socket
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT); //port the server will accept connection on ie. 5000

	//Bind operates on the server socket to assign the address
	if (bind(server_fd, (struct sockaddr *) &address, sizeof(address))<0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	//"listen" makes the socket passive socket, waiting for a connection request. 3 connections can be made
	if (listen(server_fd, 3) < 0) {
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
	//Accepting new connections from clients
	if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t*)&addrlen))<0) {
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	//Reads in message from client
	read(new_socket, buffer, 2048);
	//Print out client message, Rest buffer
	printf("%s\n", buffer);
	memset(&buffer, '0', sizeof(buffer));
	//Send reply (greeting)
	send(new_socket, greeting, strlen(greeting), 0);
	//Read in client message, Reset buffer
	read(new_socket, buffer, 2048);
	memset(&buffer, '0', sizeof(buffer));
	//Print out client message again
	printf("%s\n", buffer);
	printf("Lets begin the key exchange!\n");
	//******************************************************************RSA_KEY_EXCHANGE************************************************************
	//Initilizing ptext, ctext
	mpz_init(ptext);
	mpz_init(ctext);
	//Initilizing and setting n, e. We couldn't figure out how to pass the keys.
	mpz_init_set_str(n, "95163118457906153499715750847001433441357", 10);//Public Key
	mpz_init_set_str(e, "65537", 10);                                    //Public Key
	mpz_init_set_str(d, "5617843187844953170308463622230283376298685", 10); //Private Key

	//Call function to generate a 256 bit AES key
	generateKey(AES_key_serv);
	printf("\nEncryption key creation complete. The key will now be sent encrypted by RSA.");
	//Place AES_key_serv into ptext, encrypt into ctext
	gmpz_export(AES_key_serv, NULL, 1, 1, 0, 0, ptext);
	mpz_powm(ptext, ctext, d, n);
	
	//Send encrypted ctext(AES key) to client
	send(new_socket, ctext, sizeof(ctext), 0);
	






	








//***********************************************************************************************************************************
	
	//Convert buffer into ctext
	mpz_import(ctext, sizeof(AES_key_serv), 1, 1, 0, 0, AES_key_serv);
	//Decrypt ctext into ptext
	mpz_powm(ptext, ctext, d, n);
	//Convert ptext into AES_key
	gmpz_export(AES_keyDC, NULL, 1, 1, 0, 0, ptext);
	//Display AES_keyDC, This output maybe different from the output on the client. Professor Rrushi talked to me about that.
	printf("%s\n", AES_key_serv);
	//Below will give an error
	//gmp_printf(ptext);

	//Below is a text to see if the server waits for a message
	read(new_socket, Client_mess, sizeof(Client_mess);



	//Below I am attempting to use the AES key to encrypt a message from the server to the client. I will comment this out if it does not work.
	char Serv_mess[2048];

	memset(Serv_mess, 0, sizeof(Serv_mess));

	printf("Please enter a message you want to send to the client.\n");
	
	fgets(Serv_mess, sizeof(Serv_mess), stdin);

	

	printf("Encryption is complete.\n");

	send(new_socket, Serv_mess, strlen(Serv_mess), 0);

	return 0;
}

void generateKey{

unsigned char buf[16];
	int i;
	srand(time(NULL));
		for (i = 0; i < sizeof(buf); i++) {
			buf[i] = rand() % 256;
		}
}



/*
 ============================================================================
 Name        : receiver.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "config/config.h"
#include "net/net.h"


void swap_MAC(void);	//for testing on single machine

int main(void) {
	FILE	*fd;
	int		Len;
	char	incom_buf[2048];
	char	outcom_buf[2048];
	int		RLen;

	if (config_LoadFromFile()) {
		if (net_init()) {
			swap_MAC();
			puts("listening...");
			do {
				if (net_recv(incom_buf,&Len)) {
					incom_buf[Len] = 0;
					//printf("cmd>%s", incom_buf);
					//system(incom_buf);

					if ((fd = popen(incom_buf,"r")) != NULL) {
						printf("cmd>%s\n", incom_buf);

						while((RLen = fread(outcom_buf,MY_PROTO_MAX_DATA_LEN, 1, fd)) > 0) {
							outcom_buf[RLen] = 0;
							printf("%s",outcom_buf);
						}
						puts("out finished");

						pclose(fd);
					}
					//puts(buf);
					//net_send("command accepted ok");
				}
			} while (1);
		}
	}


	puts("Terminated!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}

void swap_MAC(void) {	//for testing on single machine
	//iface_MAC_SRC[6];
	iface_MAC_DST[6];

	unsigned char iface_MAC_TMP[6];

	iface_MAC_TMP[0] = iface_MAC_SRC[0];
	iface_MAC_TMP[1] = iface_MAC_SRC[1];
	iface_MAC_TMP[2] = iface_MAC_SRC[2];
	iface_MAC_TMP[3] = iface_MAC_SRC[3];
	iface_MAC_TMP[4] = iface_MAC_SRC[4];
	iface_MAC_TMP[5] = iface_MAC_SRC[5];

	iface_MAC_SRC[0] = iface_MAC_DST[0];
	iface_MAC_SRC[1] = iface_MAC_DST[1];
	iface_MAC_SRC[2] = iface_MAC_DST[2];
	iface_MAC_SRC[3] = iface_MAC_DST[3];
	iface_MAC_SRC[4] = iface_MAC_DST[4];
	iface_MAC_SRC[5] = iface_MAC_DST[5];

	iface_MAC_DST[0] = iface_MAC_TMP[0];
	iface_MAC_DST[1] = iface_MAC_TMP[1];
	iface_MAC_DST[2] = iface_MAC_TMP[2];
	iface_MAC_DST[3] = iface_MAC_TMP[3];
	iface_MAC_DST[4] = iface_MAC_TMP[4];
	iface_MAC_DST[5] = iface_MAC_TMP[5];
}

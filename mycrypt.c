#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <pthread.h>
//#include <android/log.h> 

#include "pw_encrypt.h"


int main(int argc, char *argv[])
{
	char *encrypted = NULL;
//	char *plaintext = "12345";
	char *pw_pass = "$5$WobXo4uCl0MG5muc$AONKNr.tZHDAXv19yyH2CG6CF0D/f9u3a4s1Rqbice1";
	int r = 0;
	errno = 0;
	printf("###############%s %s %d   %s\r\n",__FILE__,__FUNCTION__,__LINE__,strerror(errno));
	encrypted = pw_encrypt(argv[1], /*salt:*/ pw_pass);
	printf("###############%s %s %d   encrypted:%s\r\n",__FILE__,__FUNCTION__,__LINE__,encrypted);
	r = (strcmp(encrypted, pw_pass) == 0);
	free(encrypted);
	printf("###############%s %s %d   r：%d\r\n",__FILE__,__FUNCTION__,__LINE__,r);
	return 0;
}
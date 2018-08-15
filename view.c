#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backdoor.h"

unsigned char *decrypt2(data *dt, int len)
{
        int i;

        for(i = 0;i < len; i ++)
        {
                dt->data[i] = dt->data[i] ^ dt->key;
        }
        return dt->data;
}

int main(int argc, char *argv[], char *envp[])
{
	FILE *fp = NULL;
	unsigned char buf[128] = {0};
	int len, datalen;
	record *rc = NULL;
	data *dt = NULL;
	char *msg = NULL;

	fp = fopen(argv[1], "rb");
	if(!fp)
		goto END;
	while(fread(buf, sizeof(record), 1, fp))
	{
		rc = (record *) &buf;
		datalen = rc->header.len;
		len = fread(buf, datalen, 1, fp);
		if(!len)
			goto END;
		dt = (data *) &buf;
		len = datalen - sizeof(data);
		msg = (char *) decrypt2(dt, len);
		msg[len] = 0;
		puts(msg);
	}
	END:
		fclose(fp);
		return 0;
}

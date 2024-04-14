#include <fcntl.h>
#include <sys/random.h>
#include <unistd.h>

int main() {
	int fd = open("test.txt", O_CREAT | O_RDWR | O_APPEND);

	char c;
	for (int i = 0; i < 500; i++) {
		c = i % 26 + 97;
		write(fd, &c, 1);
	}

	lseek(fd, 250, SEEK_SET);

	for (int i = 0; i < 500; i++) {
		c = i % 26 + 97;
		write(fd, &c, 1);
	}

	lseek(fd, 0, SEEK_SET);

	char buf[100];
	read(fd, buf, 100);

	write(STDOUT_FILENO, buf, 100);

	close(fd);

	unlink("test.txt");
}

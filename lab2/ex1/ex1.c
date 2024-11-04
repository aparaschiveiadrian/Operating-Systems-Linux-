#include <unistd.h>
#include <stdlib.h>

int main(){
	char *message = "Hello World!\n";
	write(1, message, 14);
	exit(0);
}

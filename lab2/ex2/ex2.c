#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        const char *msg = "Incearca ./exx2 fisier_sursa fisier_destinatie\n";
        write(STDERR_FILENO, msg, strlen(msg));
        return 1;
    }
    int source = open(argv[1], O_RDONLY);
    if (source == -1) {
        const char *error_msg = "Nu a putut fi deschis fisier_sursa\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        return 1;
    }
    int destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0744);
    if (destination == -1) {
        const char *error_msg = "Nu a putut fi creat fisier_destinatie";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        close(source);
        return 1;
    }
    char buffer[1000];
    ssize_t bytesRead;
    while ((bytesRead = read(source, buffer, sizeof(buffer))) > 0) {
        if (write(destination, buffer, bytesRead) != bytesRead) {
            const char *error_msg = "Nu s a putut copia in fisier_destinatie\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            close(source);
            close(destination);
            return 1;
        }
    }

    if (bytesRead == -1) {
        const char *error_msg = "Nu a putut fi citit fisierul sursa\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        close(source);
        close(destination);
        return 1;
    }

    close(source);
    close(destination);

    const char *success_msg = "Copiere cu succes\n";
    write(STDOUT_FILENO, success_msg, strlen(success_msg));
    return 0;
}

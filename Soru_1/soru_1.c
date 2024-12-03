#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid; // �ocuk PID
    int status; // �ocuk ��k�� 

    
    pid = fork();

    if (pid < 0) {
        // fork ba�ar�s�z olursa
        printf("Hata: �ocuk surec olu�turulamadi.\n");
        exit(1); // Program� hata ile bitir
    } else if (pid == 0) {
        // �ocuk s�re� (pid == 0)
        printf("Bu cocuk surec! Dosya icerigi g�steriliyor...\n");

        // dosya i�eri�ini ekrana yazd�r
        execlp("cat", "cat", "sample.txt", NULL);

        // execlp ba�ar�s�z olursa buras� �al���r
        printf("Hata: Komut calistirilmadi.\n");
        exit(1);
    } else {
        // Ana s�re� (pid > 0)
        printf("Bu ana surec. Cocuk sureci bekliyorum...\n");

        // �ocuk s�reci bekle
        wait(&status);

        // �ocuk s�recin ��k�� durumunu kontrol et
        if (WIFEXITED(status)) {
            printf("Cocuk surec basariyla bitti. �iki� durumu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Cocuk surec bir hata ile sonlandi.\n");
        }
    }

    return 0;
}


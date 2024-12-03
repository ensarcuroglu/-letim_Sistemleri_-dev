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
        printf("Hata: �ocuk s�re� olu�turulamad�.\n");
        exit(1); // Program� hata ile bitir
    } else if (pid == 0) {
        // �ocuk s�re� (pid == 0)
        printf("Bu �ocuk s�re�! Dosya i�eri�i g�steriliyor...\n");

        // dosya i�eri�ini ekrana yazd�r
        execlp("cat", "cat", "sample.txt", NULL);

        // execlp ba�ar�s�z olursa buras� �al���r
        printf("Hata: Komut �al��t�r�lamad�.\n");
        exit(1);
    } else {
        // Ana s�re� (pid > 0)
        printf("Bu ana s�re�. �ocuk s�reci bekliyorum...\n");

        // �ocuk s�reci bekle
        wait(&status);

        // �ocuk s�recin ��k�� durumunu kontrol et
        if (WIFEXITED(status)) {
            printf("�ocuk s�re� ba�ar�yla bitti. ��k�� durumu: %d\n", WEXITSTATUS(status));
        } else {
            printf("�ocuk s�re� bir hata ile sonland�.\n");
        }
    }

    return 0;
}


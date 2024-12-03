#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid; // Çocuk PID
    int status; // Çocuk çýkýþ 

    
    pid = fork();

    if (pid < 0) {
        // fork baþarýsýz olursa
        printf("Hata: Çocuk surec oluþturulamadi.\n");
        exit(1); // Programý hata ile bitir
    } else if (pid == 0) {
        // Çocuk süreç (pid == 0)
        printf("Bu cocuk surec! Dosya icerigi gösteriliyor...\n");

        // dosya içeriðini ekrana yazdýr
        execlp("cat", "cat", "sample.txt", NULL);

        // execlp baþarýsýz olursa burasý çalýþýr
        printf("Hata: Komut calistirilmadi.\n");
        exit(1);
    } else {
        // Ana süreç (pid > 0)
        printf("Bu ana surec. Cocuk sureci bekliyorum...\n");

        // Çocuk süreci bekle
        wait(&status);

        // Çocuk sürecin çýkýþ durumunu kontrol et
        if (WIFEXITED(status)) {
            printf("Cocuk surec basariyla bitti. Çikiþ durumu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Cocuk surec bir hata ile sonlandi.\n");
        }
    }

    return 0;
}


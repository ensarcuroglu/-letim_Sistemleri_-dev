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
        printf("Hata: Çocuk süreç oluþturulamadý.\n");
        exit(1); // Programý hata ile bitir
    } else if (pid == 0) {
        // Çocuk süreç (pid == 0)
        printf("Bu çocuk süreç! Dosya içeriði gösteriliyor...\n");

        // dosya içeriðini ekrana yazdýr
        execlp("cat", "cat", "sample.txt", NULL);

        // execlp baþarýsýz olursa burasý çalýþýr
        printf("Hata: Komut çalýþtýrýlamadý.\n");
        exit(1);
    } else {
        // Ana süreç (pid > 0)
        printf("Bu ana süreç. Çocuk süreci bekliyorum...\n");

        // Çocuk süreci bekle
        wait(&status);

        // Çocuk sürecin çýkýþ durumunu kontrol et
        if (WIFEXITED(status)) {
            printf("Çocuk süreç baþarýyla bitti. Çýkýþ durumu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Çocuk süreç bir hata ile sonlandý.\n");
        }
    }

    return 0;
}


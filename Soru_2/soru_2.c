#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid; // Çocuk süreç PID
    int status; // Çýkýþ durumu

    pid = fork(); // Çocuk süreç oluþturma

    if (pid < 0) {
        // fork baþarýsýz olursa
        printf("Hata: Cocuk surec olusturulamadi.\n");
        exit(1); // Programý hata ile bitir
        
        
    } else if (pid == 0) {
        // Çocuk süreç
        printf("Bu cocuk surec! Dosya acmaya calisiyorum...\n");
        
        

        // Dosya açma 
        FILE *file = fopen("olmayan_dosya.txt", "r");
        if (file == NULL) {
            // Dosya açýlamazsa abort() çaðrýlýr
            printf("Hata: Dosya bulunamadi. abort() cagriliyor...\n");
            abort(); // Zorla çýkýþ
        } else {
            // Dosya açýlýrsa düzgün çýkýþ
            printf("Dosya basariyla acildi.\n");
            fclose(file);
            exit(0); // Düzgün çýkýþ
        }
        
        
        
    } else {
        // Ana süreç
        printf("Bu ana surec. Cocuk sureci bekliyorum...\n");

        // Çocuk süreci bekle
        wait(&status);

        // Çocuk sürecin çýkýþ durumunu analiz et
        if (WIFEXITED(status)) {
            printf("Cocuk surec duzgun bir sekilde tamamlandi. Cikis durumu: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Cocuk surec bir sinyal ile sonlandi. Sinyal numarasi: %d\n", WTERMSIG(status));
        } else {
            printf("Cocuk surec beklenmedik bir sekilde sonlandi.\n");
        }
    }

    return 0;
}


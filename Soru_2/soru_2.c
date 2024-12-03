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
        printf("Hata: Çocuk süreç oluþturulamadý.\n");
        exit(1); // Programý hata ile bitir
        
        
    } else if (pid == 0) {
        // Çocuk süreç
        printf("Bu çocuk süreç! Dosya açmaya çalýþýyorum...\n");
        
        

        // Dosya açma 
        FILE *file = fopen("olmayan_dosya.txt", "r");
        if (file == NULL) {
            // Dosya açýlamazsa abort() çaðrýlýr
            printf("Hata: Dosya bulunamadý. abort() çaðrýlýyor...\n");
            abort(); // Zorla çýkýþ
        } else {
            // Dosya açýlýrsa düzgün çýkýþ
            printf("Dosya baþarýyla açýldý.\n");
            fclose(file);
            exit(0); // Düzgün çýkýþ
        }
        
        
        
    } else {
        // Ana süreç
        printf("Bu ana süreç. Çocuk süreci bekliyorum...\n");

        // Çocuk süreci bekle
        wait(&status);

        // Çocuk sürecin çýkýþ durumunu analiz et
        if (WIFEXITED(status)) {
            printf("Çocuk süreç düzgün bir þekilde tamamlandý. Çýkýþ durumu: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Çocuk süreç bir sinyal ile sonlandý. Sinyal numarasý: %d\n", WTERMSIG(status));
        } else {
            printf("Çocuk süreç beklenmedik bir þekilde sonlandý.\n");
        }
    }

    return 0;
}


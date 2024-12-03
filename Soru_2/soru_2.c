#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid; // �ocuk s�re� PID
    int status; // ��k�� durumu

    pid = fork(); // �ocuk s�re� olu�turma

    if (pid < 0) {
        // fork ba�ar�s�z olursa
        printf("Hata: Cocuk surec olusturulamadi.\n");
        exit(1); // Program� hata ile bitir
        
        
    } else if (pid == 0) {
        // �ocuk s�re�
        printf("Bu cocuk surec! Dosya acmaya calisiyorum...\n");
        
        

        // Dosya a�ma 
        FILE *file = fopen("olmayan_dosya.txt", "r");
        if (file == NULL) {
            // Dosya a��lamazsa abort() �a�r�l�r
            printf("Hata: Dosya bulunamadi. abort() cagriliyor...\n");
            abort(); // Zorla ��k��
        } else {
            // Dosya a��l�rsa d�zg�n ��k��
            printf("Dosya basariyla acildi.\n");
            fclose(file);
            exit(0); // D�zg�n ��k��
        }
        
        
        
    } else {
        // Ana s�re�
        printf("Bu ana surec. Cocuk sureci bekliyorum...\n");

        // �ocuk s�reci bekle
        wait(&status);

        // �ocuk s�recin ��k�� durumunu analiz et
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


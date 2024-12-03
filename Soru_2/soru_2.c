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
        printf("Hata: �ocuk s�re� olu�turulamad�.\n");
        exit(1); // Program� hata ile bitir
        
        
    } else if (pid == 0) {
        // �ocuk s�re�
        printf("Bu �ocuk s�re�! Dosya a�maya �al���yorum...\n");
        
        

        // Dosya a�ma 
        FILE *file = fopen("olmayan_dosya.txt", "r");
        if (file == NULL) {
            // Dosya a��lamazsa abort() �a�r�l�r
            printf("Hata: Dosya bulunamad�. abort() �a�r�l�yor...\n");
            abort(); // Zorla ��k��
        } else {
            // Dosya a��l�rsa d�zg�n ��k��
            printf("Dosya ba�ar�yla a��ld�.\n");
            fclose(file);
            exit(0); // D�zg�n ��k��
        }
        
        
        
    } else {
        // Ana s�re�
        printf("Bu ana s�re�. �ocuk s�reci bekliyorum...\n");

        // �ocuk s�reci bekle
        wait(&status);

        // �ocuk s�recin ��k�� durumunu analiz et
        if (WIFEXITED(status)) {
            printf("�ocuk s�re� d�zg�n bir �ekilde tamamland�. ��k�� durumu: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("�ocuk s�re� bir sinyal ile sonland�. Sinyal numaras�: %d\n", WTERMSIG(status));
        } else {
            printf("�ocuk s�re� beklenmedik bir �ekilde sonland�.\n");
        }
    }

    return 0;
}


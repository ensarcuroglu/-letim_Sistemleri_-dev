#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void dosya_olustur(const char *dosya_adi) {
    // dosya oluþturma
    FILE *dosya = fopen(dosya_adi, "w");
    if (dosya == NULL) {
        perror("Dosya olusturulamadi");
        exit(1);
    }
    printf("Dosya basariyla olusturuldu: %s\n", dosya_adi);
    fclose(dosya);
}

void dosyaya_yaz(const char *dosya_adi) {
    // Dosyaya veri ekleme
    FILE *dosya = fopen(dosya_adi, "a");
    if (dosya == NULL) {
        perror("Dosyaya yazilamadi");
        exit(1);
    }
    fprintf(dosya, "Bu, ikinci child process tarafindan yazilmis bir test verisidir.\n");
    printf("Dosyaya veri yazildi: %s\n", dosya_adi);
    fclose(dosya);
}

void dosya_oku(const char *dosya_adi) {
    // Dosyayý okuma ve yazdýrma
    FILE *dosya = fopen(dosya_adi, "r");
    if (dosya == NULL) {
        perror("Dosya okunamadi");
        exit(1);
    }
    printf("Dosya icerigi:\n");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), dosya) != NULL) {
        printf("%s", buffer);
    }
    fclose(dosya);
}

int main() {
    const char *dosya_adi = "test.txt";
    pid_t pids[3]; 
    int i;

    for (i = 0; i < 3; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("Fork basarisiz");
            exit(1);
        }

        if (pids[i] == 0) {
            // farklý görev atama
            if (i == 0) {
                dosya_olustur(dosya_adi);
            } else if (i == 1) {
                sleep(1); // dosya oluþturma gecikmesi
                dosyaya_yaz(dosya_adi);
            } else if (i == 2) {
                sleep(2); // Yazma iþleminin gecikmesi
                dosya_oku(dosya_adi);
            }
            exit(0); // Çocuk süreçler görevini tamamlayýnca çýkýþ yapar
        }
        }
    }

    // Parent process: Tüm child process'lerin tamamlanmasýný bekler
    for (i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Tum child process'ler tamamlandi.\n");
    return 0;
}


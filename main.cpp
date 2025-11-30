#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

int saglik = 100;     
int enerji = 100;     
int yemek_sayisi = 5; 
int siginak_var = 0;  
char komut;

void durum_goster() {
    printf("\n--- KARAKTER DURUMU ---\n");
    printf("Saglik: %d/100\n", saglik);
    printf("Enerji: %d/100\n", enerji);
    printf("Yemek Sayisi: %d\n", yemek_sayisi);
    printf("Siginak Durumu: %s\n", siginak_var ? "VAR" : "YOK");
    printf("-------------------------\n");
}

int sinirla(int deger) {
    if (deger > 100) return 100;
    if (deger < 0) return 0;
    return deger;
}

int avlan() {
    printf("\n--> AVLANMA BASLADI...\n");
    
    if (enerji < 10) {
        printf("Cok yorgunsunuz. Avlanmak icin yeterli enerji yok.\n");
        return 1;
    }
    
    int enerji_kaybi = (rand() % 10) + 5; 
    enerji -= enerji_kaybi;
    printf("Enerji kaybi: %d\n", enerji_kaybi);

    int sans = rand() % 100; 
    int yorgunluk = (enerji < 25); 

    if (yorgunluk == 0 || sans > 50) { 
        yemek_sayisi += 2;
        printf("Basari! 2 yemek kazandiniz.\n");
    } else {
        printf("Avlanma basarisiz oldu.\n");
        if (yorgunluk == 1 && sans < 40) { 
             saglik -= 10;
             printf("Tehlikeden kacilamadi, 10 saglik kaybettiniz!\n");
        }
    }
    enerji = sinirla(enerji);
    saglik = sinirla(saglik);
    return 0; 
}

int siginak_ara() {
    printf("\n--> SIGINAK ARAMASI...\n");
    
    if (siginak_var == 1) {
        printf("Zaten guvenli bir siginaginiz var.\n");
        return 0; 
    }
    
    int sans = rand() % 100;
    if (enerji > 50 && sans > 40) { 
        siginak_var = 1;
        printf("Basarili! Guvenli bir siginak buldunuz.\n");
        return 0;
    } else {
        printf("Basarisiz. Siginak bulunamadi.\n");
        return 1;
    }
}

int dinlen() {
    printf("\n--> DINLENILIYOR...\n");
    
    enerji += 30; 
    saglik += 10; 
    
    if (yemek_sayisi > 0) {
        yemek_sayisi -= 1;
        enerji += 5; 
        printf("Yemek tuketildi. Enerji ve saglik arttirildi.\n");
    } else {
        saglik -= 5; 
        printf("Yemek yok! Yemeksiz dinlendiniz, sagliginiz biraz dustu.\n");
    }
    
    enerji = sinirla(enerji);
    saglik = sinirla(saglik);
    return 0;
}

int envanter_goster() {
    printf("\n--> ENVANTERINIZ\n");
    durum_goster(); 
    return 0;
}

int tehlike_simule_et() {
    printf("\n--- BOLGEDE TEHLIKE SERISI BASLIYOR ---\n");
    int dalga_siddeti = (rand() % 5) + 3; 

    for (int i = 1; i <= dalga_siddeti; i++) {
        if (saglik <= 0) break; 
        
        int etki = rand() % 3; 
        printf("Tehlike Dalgasi %d/%d: ", i, dalga_siddeti);

        if (etki == 0) { 
            saglik -= 10;
            printf("Hasar alindi! 10 saglik kaybi.\n");
        } else if (etki == 1) { 
            enerji -= 10;
            printf("Yorucu bir kacis! 10 enerji kaybi.\n");
        } else { 
            printf("Basariyla atlatildi.\n");
        }
        
        saglik = sinirla(saglik);
        enerji = sinirla(enerji);
    }
    printf("--- Tehlike Sona Erdi. ---\n");
    return 0;
}

int sifreli_ilerleme() {
    printf("\n--- SIFRELI ENGEL (DO-WHILE Dogrulama) ---\n");
    char dogru_sifre = 'K'; 
    char tahmin;
    
    do {
        printf("Sifreyi tahmin edin (Tek karakter): ");
        scanf(" %c", &tahmin);

        if (tahmin != dogru_sifre) {
            enerji -= 5; 
            printf("Yanlis sifre! Enerji kaybi. Kalan enerji: %d\n", enerji);
            
            if (enerji <= 0) {
                printf("Cok yoruldunuz. Engel asilamadi.\n");
                return 1; 
            }
        }
    } while (tahmin != dogru_sifre); 
    
    printf("Basarili! Sifre cozuldu. Engeli astiniz. Enerji yenilendi.\n");
    enerji = 100;
    return 0; 
}

void goster_hosgeldin() {
    printf("\n*******************************************************\n");
    printf("     KARAKTER TABANLI HAYATTA KALMA SIMULATORU (C)\n");
    printf("*******************************************************\n");
}

int main() {
    srand(time(0)); 
    goster_hosgeldin();
    int sonuc_kodu; 
    
    do {
        durum_goster(); 
        printf("\nKomut girin (A, S, R, E, F, P, X - Cikis): ");
        scanf(" %c", &komut); 
        
        switch (komut) {
            case 'A': sonuc_kodu = avlan(); 
                      if(sonuc_kodu != 0) printf("Avlanma iþlemi sistem hatasi verdi.\n"); 
                      break;
            case 'S': sonuc_kodu = siginak_ara(); break;
            case 'R': sonuc_kodu = dinlen(); break;
            case 'E': sonuc_kodu = envanter_goster(); break;
            case 'F': sonuc_kodu = tehlike_simule_et(); break; 
            case 'P': sonuc_kodu = sifreli_ilerleme(); break; 
            case 'X': printf("Simulasyon sona eriyor. Iyi calismalar!\n"); break;
            default: printf("Gecersiz komut. Lutfen A, S, R, E, F, P, X girin.\n");
        }
        
        if (saglik <= 0) {
            printf("\n--- SAGLIGINIZ BITTI! KARAKTER ÖLDÜ. OYUN SONA ERDÝ. ---\n");
            komut = 'X'; 
        }

    } while (komut != 'X');
    
    return 0;
}


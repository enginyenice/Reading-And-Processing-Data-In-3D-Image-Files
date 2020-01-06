#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <stdlib.h>
#include <float.h>
/* Degiskenler */
DIR *dir;
struct dirent *file;
char fileName[255];
int versionStatus = 0; // Versiyon kontrol 2000 Dogru 1000 Yanlis
int alanlarStatus = 0; // Alanlar kontrolu 2001 XYZ 2002 XYZRGB 1001 Yanlis
int noktaStatus = 0;   //1030 OK 1031 NO
int noktaControlStatus = 0; //1020 OK 1021 NO
int dataStatus = 0; //Data kontrolu 3000 DATA yaziyor ascci 3001 binnary 3002 yanlis 1003
int dosyaType[20]; // 1 ascii 2 binary
char a[20][100]; // Dosya kodu => dosya Adi
char Noktakopya[20][5][250];
int NoktaSay[20];
//kordinatlar [dno][x];
int okunmayacakDosya[20];
char *dosyaIsimleri[10];
float xKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir
float yKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir
float zKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir

float kureXKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir
float kureYKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir
float kureZKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir

int kureRKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir
int kureGKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir
int kureBKordinatlari[20][100000]; // Eger ram yetersiz gelirse degistir
int kacSatirKureVar[20];
int dosyaAlanlarType[20];


float xEnKucukKordinat[20]; // Eger ram yetersiz gelirse degistir
float yEnKucukKordinat[20]; // Eger ram yetersiz gelirse degistir
float zEnKucukKordinat[20]; // Eger ram yetersiz gelirse degistir

float xEnBuyukKordinat[20]; // Eger ram yetersiz gelirse degistir
float yEnBuyukKordinat[20]; // Eger ram yetersiz gelirse degistir
float zEnBuyukKordinat[20]; // Eger ram yetersiz gelirse degistir

float enUzakMesafe[20];
float enYakinMesafe[20];

int yakinKordinatSatirNo[20][2];
int uzakKordinatSatirNo[20][2];

float mesafeSonuclari[20][100] ;// [dNo][MesafeBilgisi]
float toplamMesafe[100];
float ortalamaMesafe[100];

int ortalamaDonenSatir[20];
int Kirmizi[20][500000];
int Yesil[20][500000];
int Mavi[20][500000];
int DosyaToSatir[20];
int dosyaKodu = 0;
int dosyaSayisi = 0;
int DosyaController[20]; //[dNo][BilgiNo]
int DosyaControllerSatirNo[20]; //[dNo][BilgiNo]

float kullaniciX = 0;
float kullaniciY = 0;
float kullaniciZ = 0;
float yariCap = 0;

int menuDevam = 0;



//Fonksiyonlar
int menu();
void dosyalariCek();
void dosyalariAyir(char files[255]);
void dosyalariOku(char file_name[255]);
void satirOkuma(char a[300], FILE * dosya_a, char file_name[255],int dosyaKodu);
void versionControl(char version[100], char file_name[255],int dosyaKodu);
void alanControl(char version[100], char file_name[255],int dosyaKodu);
void dosyayiCikar(char file_name[255],int hataKodu,int dosyaKodu, int satir_sayisi);
void noktaSayisiControlBaslik(char version[100],char file_name[255], int dosyaKodu);
void noktaSayisiControl(int i);
void dataControl(char version[100], char file_name[255],int dosyaKodu);
void kordinatKontrol(char a[300],int dosyaKodu,int satir_sayisi,char file_name[255]);
void binaryKordinatKontrol(FILE * dosya,char file_name[255], int dosyaKodu);
void enYakinEnUzakHesapla();
void noktalarinOrtalamasi();
void kupOlusturma();
void kureIcindeKalanNoktaHesaplama();
void outputOlustur();

/* Main */
/* Methodlar */
int main()
{

    int a = menu();
    while(a == 400)
    {
        menu();

    }
    return 0;
}

int menu()
{
    system("color 70");
    system("cls");
    int secim;

    printf("\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("| Secim Yetkisi: Menu secimleri yapildikca otomatik olarak artmaktadir.|\n");
    printf("| Secim Yetkisi: 0 ise sadece 1 ve 6 numaralari menuler calisir.       |\n");
    printf("| Secim Yetkisi: 1 ise sadece 2,3,4 ve 6 numaralari menu calisir.      |\n");
    printf("| Secim Yetkisi: 2 ise sadece 2,3,4,5 6 numaralari menu calisir.       |\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("|                                 MENU                                 | \n");
    printf("|                                                    Secim Yetkisi %d   |\n",menuDevam);
    printf("| 1-) Dosya Uyumluluk Taramasi                                         |\n");
    printf("| 2-) En Yakin Ve En Uzak Noktalarin Hesaplanmasi                      |\n");
    printf("| 3-) En Kucuk Kupun Olusturulmasi                                     |\n");
    printf("| 4-) Kure Olusturma Ve Icinde Kalan  Noktalari Bulunmasi              |\n");
    printf("| 5-) Tum Noktalarin Ortalamasinin Hesaplanmasi                        |\n");
    printf("| 6-) Programi Kapat                                                   |\n");
    printf("|  Secim Yapiniz: ");
    scanf("%d", &secim);
    printf(" ---------------------------------------------------------------------- \n");



     switch(secim)
    {
    case 1:
        if(menuDevam == 0)
        {
            menuDevam = 1;
            versionStatus = 2000;
            alanlarStatus = 2002;
            memset(xKordinatlari,0,sizeof(xKordinatlari));
            memset(xKordinatlari,0,sizeof(yKordinatlari));
            memset(xKordinatlari,0,sizeof(zKordinatlari));
            dosyalariCek();
            dosyaKodu = 0;
            for(int i = 0; i<dosyaSayisi; i++)
            {
                noktaSayisiControl(i);
            }
            system("PAUSE");
        } else
        {
            printf("Kontrol islemleri daha onceden yapildi.\n");
            system("PAUSE");
        }
        break;
    case 2:
        if(menuDevam >= 1)
        {
         menuDevam = 2;
         enYakinEnUzakHesapla();
         system("PAUSE");
        } else {
         printf("Hatali Secim\n");
         system("PAUSE");
        }
        break;
    case 3:
        if(menuDevam >= 1)
        {
          kupOlusturma();
          system("PAUSE");

        } else {
         printf("Hatali Secim\n");
         system("PAUSE");
        }
        break;
    case 4:
        if(menuDevam >= 1)
        {
         kureIcindeKalanNoktaHesaplama();
         system("PAUSE");
        } else {
         printf("Hatali Secim\n");
         system("PAUSE");
        }
        break;
    case 5:
        if(menuDevam >= 2)
        {
         noktalarinOrtalamasi();
         system("PAUSE");
        } else {
         printf("Hatali Secim\n");
         system("PAUSE");
        }
        break;
    case 6:
        printf("Program kapatiliyor...\n");
        exit(99);
        break;
    }
    return 400;
}

void dosyalariCek()
{
    // system("cls");
    printf("SECIM1\n");
    dir = opendir(".");
    while ((file = readdir(dir)) != NULL)
    {
        strncpy(fileName, file->d_name, 254);
        fileName[254] = '\0';
        dosyalariAyir(fileName);
    }
    closedir(dir);
}

void dosyalariAyir(char files[255])
{
    int karakterSay;
    karakterSay = strlen(files);
    if(karakterSay > 4)
    {

        //a.nkt
        if((files[karakterSay-4] == '.')&&(files[karakterSay-3] == 'n')&&(files[karakterSay-2] == 'k')&&(files[karakterSay-1] == 't'))
        {


            //printf("\n-------------------------------------------------------------------\n");

            //printf("\nDosya: %s Karakter Sayisi %d DosyaKodu %d\n",files,karakterSay,dosyaKodu);
            // dosyaIsimleri[dosyaKodu] = files;
            dosyaIsimleri[dosyaKodu] = malloc(strlen(files) + 1);
            strcpy(dosyaIsimleri[dosyaKodu], files);
            /*
                malloc()dinamik olarak her dizesi i�in arabellek ay�rmak ve bu tampon kopyalanacak:
            */


            dosyalariOku(files);
        }

    }
}

void dosyalariOku(char file_name[255])
{

    FILE * dosya_a;
    char a[300];
    if ((dosya_a = fopen(file_name, "r")) == NULL)
    {
        printf("%s bulunamadi\n", file_name);
    }
    else
    {
        //      printf("%s okundu", file_name); satirGec(1);
        //     printf("================================"); satirGec(1);
        dosyaSayisi++;
        satirOkuma(a,dosya_a,file_name,dosyaKodu);
        xKordinatlari[dosyaKodu][0] = 0;
        yKordinatlari[dosyaKodu][0] = 0;
        zKordinatlari[dosyaKodu][0] = 0;
        // printf("Dosya Kodu %d \t Dosya Adi: %s\n", dosyaKodu,file_name);

        dosyaKodu++;
    }
}

void satirOkuma(char a[300], FILE * dosya_a, char file_name[255],int dosyaKodu)
{
    int satir_sayisi = 0;


    while ( fgets(a, 10000, dosya_a) != NULL )
    {

        satir_sayisi++;

        if(satir_sayisi > 1)
        {
            //printf("Satir Sayisi: %d", satir_sayisi); satirGec(1);
            //printf("%d) satir: %s\n", satir_sayisi, a);

            if(satir_sayisi == 2)
            {
                versionControl(a,file_name,dosyaKodu);
            }
            else if(satir_sayisi == 3)
            {
                alanControl(a,file_name,dosyaKodu);
            }
            else if(satir_sayisi == 4)
            {
                //printf("%s\n", a);
                noktaSayisiControlBaslik(a,file_name,dosyaKodu);
            }

            else if(satir_sayisi == 5)
            {
                dataControl(a,file_name,dosyaKodu);
            }
            else if(satir_sayisi > 5)
            {
                if(okunmayacakDosya[dosyaKodu] != 1)
                {
                    if(dosyaType[dosyaKodu] == 1)
                    {
                        kordinatKontrol(a,dosyaKodu,satir_sayisi,file_name);
                    }
                    else if(dosyaType[dosyaKodu] == 2)
                      {
                         binaryKordinatKontrol(dosya_a,file_name,dosyaKodu);
                      }
                }
            }
        }

        if(dosyaType[dosyaKodu] == 1)
        {
            DosyaToSatir[dosyaKodu] = satir_sayisi;
        }

    }

        if(okunmayacakDosya[dosyaKodu] != 1)
        {
            printf("%s Dosyasi basariyla tarandi.\n",dosyaIsimleri[dosyaKodu]);
        }





    //printf("%s dosyasinda %d satir vardir",file_name,satir_sayisi);satirGec(1);

}

void versionControl(char version[100], char file_name[255],int dosyaKodu)
{
    if((version[0] == 'V')&&(version[1] == 'E')&&(version[2] == 'R')&&(version[3] == 'S')&&(version[4] == 'I')&&(version[5] == 'O')&&(version[6] == 'N')&&(version[7] == ' '&&(version[8] == '1')&&(version[9] == '\n')))
    {

        versionStatus = 2000;
    }
    else
    {
        //printf("version hatasi");
        versionStatus = 1000;
        dosyayiCikar(file_name,1000,dosyaKodu,0);

    }
}

void alanControl(char version[100], char file_name[255],int dosyaKodu)
{
    // ALANLAR x y z r g b
    if(xKordinatlari[dosyaKodu][0] != -999)
    {
        if((version[0] == 'A')&&(version[1] == 'L')&&(version[2] == 'A')&&(version[3] == 'N')&&(version[4] == 'L')&&(version[5] == 'A')&&(version[6] == 'R')&&(version[7] == ' '&&(version[8] == 'x')&&(version[9] == ' ')&&(version[10] == 'y')&&(version[11] == ' ')&&(version[12] == 'z')&&(version[13] == ' ')&&(version[14] == 'r')&&(version[15] == ' ')&&(version[16] == 'g')&&(version[17] == ' ')&&(version[18] == 'b')&&(version[19] == '\n')))

        {
            dosyaAlanlarType[dosyaKodu] = 2001;
            alanlarStatus = 2001;
        }
        else if((version[0] == 'A')&&(version[1] == 'L')&&(version[2] == 'A')&&(version[3] == 'N')&&(version[4] == 'L')&&(version[5] == 'A')&&(version[6] == 'R')&&(version[7] == ' '&&(version[8] == 'x')&&(version[9] == ' ')&&(version[10] == 'y')&&(version[11] == ' ')&&(version[12] == 'z')&&(version[13] == '\n')))
        {


            dosyaAlanlarType[dosyaKodu] = 2002;
            alanlarStatus = 2002;
        }
        else
        {
            //printf("\ALANLAR YANLIS"); satirGec(1);
            alanlarStatus = 1001;
            dosyayiCikar(file_name,alanlarStatus,dosyaKodu,0);
        }
    }
    else
    {
        //printf("Dosyadaki versiyon hatadan dolayi okunmadi\n");
    }

}

void dosyayiCikar(char file_name[255],int hataKodu,int dosyaKodu, int satir_sayisi)
{
    //printf("DOSYA CIKARDosya Kodu: %d |", dosyaKodu);
    okunmayacakDosya[dosyaKodu] = 1;
    DosyaController[dosyaKodu] = hataKodu;
    DosyaControllerSatirNo[dosyaKodu] = satir_sayisi;

    xKordinatlari[dosyaKodu][0] = -999;

    if(hataKodu == 1000)
    {
        printf("%s Dosyasinin VERSION basligi hatalidir.\n", file_name);
    }
    else if(hataKodu == 1001)
    {
        printf("%s Dosyasinin ALANLAR basligi hatalidir.\n", file_name);
    }
    else if(hataKodu == 1002)
    {
        printf("%s Dosyasinin NOKTALAR  basligi hatalidir.\n", file_name);
    }
    else if(hataKodu == 1003)
    {
        printf("%s Dosyasinin DATA basligi hatalidir.\n", file_name);
    }
    else if(hataKodu == 1004)
    {
        printf("%s Dosyasinin satir numarasi %d olan kordinatinda kordinat hatasi bulunmaktadir.\n",file_name,satir_sayisi);

    }
    else if(hataKodu == 1005)
    {
        printf("%s Dosyasinin satir numarasi %d olan kordinatinda renk hatasi bulunmaktadir.\n",file_name,satir_sayisi);

    }
    else if(hataKodu == 1021)
    {
        printf("%s Dosyasinin NOKTALAR  basligi hatalidir.\n",file_name);

    }
    else if(hataKodu == 1031)
    {
        printf("%s Dosyasinin  NOKTALAR basligi ile nokta sayisi eslesmemektedir.\n",file_name);

    }
    else if(hataKodu == 2001)
    {
        printf("%s Dosyasinin %d  satirinda kurallara uygun olmayan kordinat bulunmaktadir..\n",file_name,satir_sayisi);

    }


    //printf("Dosya KODU [%d] | X [%f]", dosyaKodu, xKordinatlari[dosyaKodu][0]); satirGec(1);
}
//a,file_name,dosyaKodu
void noktaSayisiControlBaslik(char version[100],char file_name[255], int dosyaKodu)
{

    if(okunmayacakDosya[dosyaKodu] != 1)
    {
        if((version[0] == 'N')&&(version[1] == 'O')&&(version[2] == 'K')&&(version[3] == 'T')&&(version[4] == 'A')&&(version[5] == 'L')&&(version[6] == 'A')&&(version[7] == 'R')&&(version[8] == ' '))
        {
            noktaControlStatus = 1020;
            char*bosluk=" ";
            char* birkelime=NULL;
            birkelime=strtok(version,bosluk);
            int i = 0;
            while(birkelime!=NULL)
            {
                // printf("\n");
                // printf("%s",birkelime);
                strcpy(Noktakopya[dosyaKodu][i], birkelime);
                birkelime=strtok(NULL,bosluk);
                i++;
            }

            sscanf(Noktakopya[dosyaKodu][1], "%d", &NoktaSay[dosyaKodu]);
            //printf("%d",NoktaSay[dosyaKodu] );



        }
        else
        {
            noktaControlStatus = 1021;
        }

        if(noktaControlStatus == 1021)
        {
            dosyayiCikar(file_name,1021,dosyaKodu,0);
        }
    }
    else
    {
        //printf("Dosyadaki noktalar hatadan dolayi okunmadi\n");
    }
    //printf("%s", version);

}
void noktaSayisiControl(int i)
{
    if(NoktaSay[i] == DosyaToSatir[i]-5)
    {

        //printf("Noktalar uyusuyor");
        noktaStatus = 1030;
    }
    else
    {
        noktaStatus = 1031;
        dosyayiCikar(dosyaIsimleri[i],1031,i,0);
    }

}

void dataControl(char version[100], char file_name[255],int dosyaKodu)
{

    if(xKordinatlari[dosyaKodu][0] != -999)
    {
        if((version[0] == 'D')&&(version[1] == 'A')&&(version[2] == 'T')&&(version[3] == 'A')&&(version[4] == ' '))
        {
            if( (version[5] == 'a') && (version[6] == 's') && (version[7] == 'c') && (version[8] == 'i') && (version[9] == 'i'))
            {
                //ascii
                dataStatus = 3001;
                dosyaType[dosyaKodu] = 1;
            }
            else if( (version[5] == 'b') && (version[6] == 'i') && (version[7] == 'n') && (version[8] == 'a') && (version[9] == 'r') && (version[10] == 'y'))
            {
                //binary
                dataStatus = 3002;
                dosyaType[dosyaKodu] = 2;


            }
        }
        else
        {
            dataStatus = 1003;
        }
        if(dataStatus == 1003)
        {
            dosyayiCikar(file_name,1003,dosyaKodu,0);
        }
    }
    else
    {
        //printf("Dosyadaki alanlar hatadan dolayi okunmadi\n");
    }


}

void kordinatKontrol(char a[300],int dosyaKodu,int satir_sayisi,char file_name[255])
{

    if(okunmayacakDosya[dosyaKodu] != 1)
    {

        /*
        dosyaAlanlarType[dosyaKodu] = 2001; xyzrgb
        dosyaAlanlarType[dosyaKodu] = 2002;  xyz
        */

        int kordinatStatus;
        int alanlarRenkStatus; // 0 Hatali 1 D�zg�n
        int renkStatus;
//char a[300],dosyaKodu);

// printf("SATIR SAYISI [%d]", satir_sayisi); satirGec(1);
        char*bosluk=" ";
        char* nokta=NULL;
        nokta=strtok(a,bosluk);
        int i = 0;
        while(nokta!=NULL)
        {

            if(i == 0)
            {
                if(dosyaAlanlarType[dosyaKodu] == 2001)
                {
                    alanlarRenkStatus = 0;

                }
                else if(dosyaAlanlarType[dosyaKodu] == 2002)
                {

                    alanlarRenkStatus = 0;
                }
                kordinatStatus = 0;
                sscanf(nokta, "%f", &xKordinatlari[dosyaKodu][satir_sayisi]);
//      xKordinatlari[dosyaKodu][satir_sayisi] = strtod(nokta,NULL);
                //printf("X => Float: %f |  ",xKordinatlari[dosyaKodu][satir_sayisi]);
            }
            if(i == 1)
            {
                sscanf(nokta, "%f", &yKordinatlari[dosyaKodu][satir_sayisi]);
//      xKordinatlari[dosyaKodu][satir_sayisi] = strtod(nokta,NULL);
                //printf("Y => Float: %f | ",yKordinatlari[dosyaKodu][satir_sayisi]);
            }
            if(i == 2)
            {
                if(dosyaAlanlarType[dosyaKodu] == 2002)
                {
                    alanlarRenkStatus = 1;
                }
                kordinatStatus = 1;
                sscanf(nokta, "%f", &zKordinatlari[dosyaKodu][satir_sayisi]);
//      xKordinatlari[dosyaKodu][satir_sayisi] = strtod(nokta,NULL);
                //printf("Z => Float: %f | ",zKordinatlari[dosyaKodu][satir_sayisi]);
            }
            else if(i == 3)
            {
                if(dosyaAlanlarType[dosyaKodu] == 2002)
                {
                    alanlarRenkStatus = 0;
                }
                renkStatus = 0;
                Mavi[dosyaKodu][satir_sayisi] = -88;
                int r;
                r = atoi(nokta);
                //printf("  \n R | ");
                //printf("R => Integer: %d | ", r);
                Kirmizi[dosyaKodu][satir_sayisi] = r;
                r = 0;

            }
            else if(i == 4)
            {
                int g;
                g = atoi(nokta);
                //printf("G => Integer: %d | ", g);
                Yesil[dosyaKodu][satir_sayisi] = g;
                g = 0;

            }
            else if(i == 5)
            {
                if(dosyaAlanlarType[dosyaKodu] == 2001)
                {
                    alanlarRenkStatus = 1;
                }
                renkStatus = 1;
                Mavi[dosyaKodu][satir_sayisi] = -88;
                int b;
                b = atoi(nokta);
                //printf("  \n B | ");
                //printf("B => Integer: %d | ", b);
                Mavi[dosyaKodu][satir_sayisi] = b;
                b = 0;
            }
            if(i > 5)
            {
                i = 0;
            }
            i++;


            nokta=strtok(NULL,bosluk);
        }

        if(kordinatStatus == 0)
        {
            //kordinatKontrol(satir_sayisi);
            //printf("Kordinattan Gelen Hata.\n");

            //char file_name[255],int hataKodu,int dosyaKodu
            dosyayiCikar(file_name,1004,dosyaKodu,satir_sayisi);
            //exit(1);
        }
        if(renkStatus == 0)
        {
            // renkKontrol(satir_sayisi);
            //printf("Renkden gelen hata..\n");
            dosyayiCikar(file_name,1005,dosyaKodu,satir_sayisi);
            //exit(1);
        }
        if(alanlarRenkStatus == 0)
        {
            dosyayiCikar(file_name,2001,dosyaKodu,satir_sayisi);
        }




    }
}

void binaryKordinatKontrol(FILE * dosya,char file_name[255], int dosyaKodu)
{

    if(okunmayacakDosya[dosyaKodu] != 1)
    {

        FILE *file = fopen(file_name, "rb");

        int kordinatStatus = -1;
        int alanlarRenkStatus = -1; // 0 Hatali 1 D�zg�n
        int renkStatus= -1;

        float i[3];
        int   k[3];
        char  a[100];
        int x = 6;
        fgets(a,100,file);
        fgets(a,100,file);
        fgets(a,100,file);
        fgets(a,100,file);
        fgets(a,100,file);
        int yer = ftell(file);
        fseek(file,(yer), SEEK_SET );
        //printf("%f\n",(fread(&i, sizeof(float), 1, file)));
        //int satir = 6;
        while(!feof(file))
        {

            xKordinatlari[dosyaKodu][x] = -1.000000;
            yKordinatlari[dosyaKodu][x] = -1.000000;
            zKordinatlari[dosyaKodu][x] = -1.000000;
            fread(&i,4,3,file);
            if(feof(file))
            {
                break;
            }
            //printf("%f,%f,%f\t",i[0],i[1],i[2]);


            xKordinatlari[dosyaKodu][x] = i[0];
            yKordinatlari[dosyaKodu][x] = i[1];
            zKordinatlari[dosyaKodu][x] = i[2];

            //printf("\n!\t\t%d )x ->%f",x, xKordinatlari[dosyaKodu][x]);



            if(i[0] != -1)
            {
                alanlarRenkStatus = 0;
            }
            if(i[2] != -1)
            {
                if(dosyaAlanlarType[dosyaKodu] == 2002)
                {
                    alanlarRenkStatus = 1;
                }
            }



            if(dosyaAlanlarType[dosyaKodu] == 2001)
            {

                fread(&k,4,3,file); //if(feof(file)) { break; }
                //printf("%d,%d,%d",k[0],k[1],k[2]);
                //printf("%d\n",Kirmizi[dosyaKodu][x]);
                Kirmizi[dosyaKodu][x] = k[0];
                Yesil[dosyaKodu][x] = k[1];
                Mavi[dosyaKodu][x] = k[2];

                if(k[0] != -1)
                {
                    if(dosyaAlanlarType[dosyaKodu] == 2002)
                    {
                        alanlarRenkStatus = 0;
                    }
                    renkStatus = 0;

                }
                if(k[2] != -1)
                {
                    if(dosyaAlanlarType[dosyaKodu] == 2001)
                    {
                        alanlarRenkStatus = 1;
                    }
                    renkStatus = 1;
                }

            }

            x++;
        }
        if(kordinatStatus == 0)
        {
            //kordinatKontrol(satir_sayisi);
            //printf("Kordinattan Gelen Hata.\n");

            //char file_name[255],int hataKodu,int dosyaKodu
            dosyayiCikar(file_name,1004,dosyaKodu,x);
            //exit(1);
        }
        if(renkStatus == 0)
        {
            // renkKontrol(satir_sayisi);
            //printf("Renkden gelen hata..\n");
            dosyayiCikar(file_name,1005,dosyaKodu,x);
            //exit(1);
        }
        if(alanlarRenkStatus == 0)
        {
            dosyayiCikar(file_name,2001,dosyaKodu,x);
        }


        DosyaToSatir[dosyaKodu] = x-1;
        fclose(file);
    }




}

void enYakinEnUzakHesapla()
{


    //system("cls");
    printf("Lutfen bekleyiniz. Bu islem uzun surebilir...\n");
    printf("SECIM2\n");

    int dosyaKoduBelirle;
    dosyaKoduBelirle = dosyaSayisi-1;
    int donmeSayisi = 0;

    for(int i = 0; i<dosyaKoduBelirle+1; i++)
    {
        if(okunmayacakDosya[i] != 1)
        {
            //noktaSayisiControl(i);
            if(okunmayacakDosya[i] != 1)
            {

                //printf("Hatasiz X : %f", xKordinatlari[i][0]);
                xEnBuyukKordinat[i] = 0;
                yEnBuyukKordinat[i] = 0;
                zEnBuyukKordinat[i] = 0;

                xEnKucukKordinat[i] = 9999999999;
                yEnKucukKordinat[i] = 9999999999;
                zEnKucukKordinat[i] = 9999999999;

                enUzakMesafe[i] = -99;
                enYakinMesafe[i] = 9999999;

                //printf("Kontrol Edilen Dosya Kodu %d\n",i);
                ortalamaDonenSatir[i] = 0;
                donmeSayisi = 0;
                for(int j = 6; j< DosyaToSatir[i]; j++)
                {

                    float basX = xKordinatlari[i][j];
                    float basY = yKordinatlari[i][j];
                    float basZ = zKordinatlari[i][j];

                    //printf("Baslangic: %f , %f , %f\n",basX,basY,basZ);
                    // #pragma omp parallel
                    // #pragma omp for
                    for(int k = j+1; k<= DosyaToSatir[i]; k++)
                    {

                        float ortaX = xKordinatlari[i][k];
                        float ortaY = yKordinatlari[i][k];
                        float ortaZ = zKordinatlari[i][k];
                        //printf("Orta: %f , %f , %f\n",ortaX,ortaY,ortaZ);
                        float xFarki,yFarki,zFarki;
                        xFarki = basX-ortaX;
                        yFarki = basY-ortaY;
                        zFarki = basZ-ortaZ;


                        float MesafeHesapla;
                        //ortalamaDonenSatir[i] = ortalamaDonenSatir[i] + 1;
                        donmeSayisi++;
                        MesafeHesapla =  sqrt(pow(xFarki,2) + pow(yFarki,2) + pow(zFarki,2));
                        toplamMesafe[i] += MesafeHesapla;


                        //printf("FARK X %f FARK y %f FARK z %f\n", xFarki,yFarki,zFarki);
                        //printf("Mesafe %f\n", MesafeHesapla);
                        //satirGec(2);
                        //printf("%f , %f , %f", xFarki,yFarki,zFarki);
                        //satirGec(1);


                        if(MesafeHesapla > enUzakMesafe[i] )
                        {
                            uzakKordinatSatirNo[i][0] = j;
                            uzakKordinatSatirNo[i][1] = k;

                            enUzakMesafe[i] = MesafeHesapla;
                            // 1       10


                            //printf("Uzaktan Gelen Dosya Kodu: %d En Uzun: Bas: %d Orta %d\n",i,j,k);
                            /*
                            satirGec(1);

                            printf("En Uzak Mesafe: %f \t En Yakin Mesafe: %f", enUzakMesafe[i],enYakinMesafe[i]);
                            satirGec(1);
                            printf("--------------------------------------------------");
                            satirGec(1);
                            */

                        }
                        if(MesafeHesapla < enYakinMesafe[i] )
                        {
                            enYakinMesafe[i] = MesafeHesapla;
                            yakinKordinatSatirNo[i][0] = j;
                            yakinKordinatSatirNo[i][1] = k;


                            //printf("Yak�ndan Gelen Dosya Kodu: %d En Uzun: Bas: %d Orta %d\n",i,j,k);
                            /*
                             satirGec(1);
                             printf("En Uzak Mesafe: %f \t En Yakin Mesafe: %f", enUzakMesafe[i],enYakinMesafe[i]);
                             satirGec(1);
                             printf("--------------------------------------------------");
                             satirGec(1);
                             */


                        }
                        if(xKordinatlari[i][k] > xEnBuyukKordinat[i])
                        {
                            xEnBuyukKordinat[i] = xKordinatlari[i][k];
                        }
                        if(yKordinatlari[i][k] > yEnBuyukKordinat[i])
                        {
                            yEnBuyukKordinat[i] = yKordinatlari[i][k];
                        }
                        if(zKordinatlari[i][k] > zEnBuyukKordinat[i])
                        {
                            zEnBuyukKordinat[i] = zKordinatlari[i][k];
                        }


                        if(xKordinatlari[i][k] < xEnKucukKordinat[i])
                        {
                            xEnKucukKordinat[i] = xKordinatlari[i][k];
                        }
                        if(yKordinatlari[i][k] < yEnKucukKordinat[i])
                        {
                            yEnKucukKordinat[i] = yKordinatlari[i][k];
                        }
                        if(zKordinatlari[i][k] < zEnKucukKordinat[i])
                        {
                            zEnKucukKordinat[i] = zKordinatlari[i][k];
                        }
                    }



                }

                /*
                                printf("Toplam Mesafe %f\n",toplamMesafe[i]);
                                printf("Donen Satir  %i\n",donmeSayisi);
                */
                ortalamaDonenSatir[i] = donmeSayisi;
                //ortalamaMesafe[i] = toplamMesafe[i]/(ortalamaDonenSatir[i]);
                /*
                              printf("Donen Satir Arr %i\n",ortalamaDonenSatir[i]);
                              printf("Ortalama %f\n",ortalamaMesafe[i]);
                */

                // printf("Dosya Kodu %d En Uzak Mesafe: %f \t En Yakin Mesafe: %f\n", i, enUzakMesafe[i],enYakinMesafe[i]);
                printf("%s\n",dosyaIsimleri[i]);
                if(dosyaAlanlarType[i] == 2002)
                {
                    printf("%f %f %f\n",xKordinatlari[i][uzakKordinatSatirNo[i][0]],yKordinatlari[i][uzakKordinatSatirNo[i][0]],zKordinatlari[i][uzakKordinatSatirNo[i][0]]);
                    printf("%f %f %f\n",xKordinatlari[i][uzakKordinatSatirNo[i][1]],yKordinatlari[i][uzakKordinatSatirNo[i][1]],zKordinatlari[i][uzakKordinatSatirNo[i][1]]);


                    printf("%f %f %f\n",xKordinatlari[i][yakinKordinatSatirNo[i][0]],yKordinatlari[i][yakinKordinatSatirNo[i][0]],zKordinatlari[i][yakinKordinatSatirNo[i][0]]);
                    printf("%f %f %f\n\n",xKordinatlari[i][yakinKordinatSatirNo[i][1]],yKordinatlari[i][yakinKordinatSatirNo[i][1]],zKordinatlari[i][yakinKordinatSatirNo[i][1]]);
                }
                else if(dosyaAlanlarType[i] == 2001)
                {
                    printf("%f %f %f %d %d %d\n",xKordinatlari[i][uzakKordinatSatirNo[i][0]],yKordinatlari[i][uzakKordinatSatirNo[i][0]],zKordinatlari[i][uzakKordinatSatirNo[i][0]],Kirmizi[i][uzakKordinatSatirNo[i][1]],Mavi[i][uzakKordinatSatirNo[i][1]],Yesil[i][uzakKordinatSatirNo[i][1]]);
                    printf("%f %f %f %d %d %d\n",xKordinatlari[i][uzakKordinatSatirNo[i][1]],yKordinatlari[i][uzakKordinatSatirNo[i][1]],zKordinatlari[i][uzakKordinatSatirNo[i][1]],Kirmizi[i][uzakKordinatSatirNo[i][1]],Mavi[i][uzakKordinatSatirNo[i][1]],Yesil[i][uzakKordinatSatirNo[i][1]]);


                    printf("%f %f %f %d %d %d\n",xKordinatlari[i][yakinKordinatSatirNo[i][0]],yKordinatlari[i][yakinKordinatSatirNo[i][0]],zKordinatlari[i][yakinKordinatSatirNo[i][0]],Kirmizi[i][yakinKordinatSatirNo[i][0]],Mavi[i][yakinKordinatSatirNo[i][0]],Yesil[i][yakinKordinatSatirNo[i][0]]);
                    printf("%f %f %f %d %d %d\n\n",xKordinatlari[i][yakinKordinatSatirNo[i][1]],yKordinatlari[i][yakinKordinatSatirNo[i][1]],zKordinatlari[i][yakinKordinatSatirNo[i][1]],Kirmizi[i][yakinKordinatSatirNo[i][1]],Mavi[i][yakinKordinatSatirNo[i][1]],Yesil[i][yakinKordinatSatirNo[i][1]]);

                }
                printf("En Uzak Mesafe: %f \t En Yakin Mesafe: %f\n", enUzakMesafe[i],enYakinMesafe[i]);

            }
        }

    }
}

void noktalarinOrtalamasi()
{
    //system("cls");
    printf("\nSECIM5\n");
    for(int i = 0; i <dosyaSayisi; i++)
    {
        if(okunmayacakDosya[i] != 1)
        {
            ortalamaMesafe[i] = toplamMesafe[i]/(ortalamaDonenSatir[i]);

            printf("%s\n",dosyaIsimleri[i]);
            printf("Ortalama %f\n\n",ortalamaMesafe[i]);

        }
    }

    outputOlustur();




}

void kupOlusturma()
{
    printf("\nSECIM3\n");
    for(int i = 0; i <dosyaSayisi; i++)
    {
        if(okunmayacakDosya[i] != 1)
        {
            printf("%s\n",dosyaIsimleri[i]);
            //printf("En buyuk X: %f \t En kucuk X: %f\n",xEnBuyukKordinat[i],xEnKucukKordinat[i]);
            //printf("En buyuk Y: %f \t En kucuk Y: %f\n",yEnBuyukKordinat[i],yEnKucukKordinat[i]);
            //printf("En buyuk Z: %f \t En kucuk Z: %f\n",zEnBuyukKordinat[i],zEnKucukKordinat[i]);
            float xFarki = xEnBuyukKordinat[i] - xEnKucukKordinat[i];
            float yFarki = yEnBuyukKordinat[i] - yEnKucukKordinat[i];
            float zFarki = zEnBuyukKordinat[i] - zEnKucukKordinat[i];





            if((xFarki > yFarki) && (xFarki > zFarki))
            {
                yEnBuyukKordinat[i] = yEnKucukKordinat[i] + xFarki;
                zEnBuyukKordinat[i] = zEnKucukKordinat[i] + xFarki;


            }
            else if((yFarki > xFarki) && (yFarki > zFarki))
            {
                xEnBuyukKordinat[i] = xEnKucukKordinat[i] + yFarki;
                zEnBuyukKordinat[i] = zEnKucukKordinat[i] + yFarki;

            }
            else if((zFarki > xFarki) && (zFarki > yFarki))
            {
                xEnBuyukKordinat[i] = xEnKucukKordinat[i] + zFarki;
                yEnBuyukKordinat[i] = yEnKucukKordinat[i] + zFarki;
            }
            else
            {
                // printf("\n");
            }
            /*
                        printf("X\t\tY\t\tZ\n");
            */
            printf("%f %f %f\n",xEnKucukKordinat[i],yEnKucukKordinat[i],zEnKucukKordinat[i]);

            printf("%f %f %f\n",xEnKucukKordinat[i],yEnKucukKordinat[i],zEnBuyukKordinat[i]);


            printf("%f %f %f\n",xEnKucukKordinat[i],yEnBuyukKordinat[i],zEnKucukKordinat[i]);

            printf("%f %f %f\n",xEnKucukKordinat[i],yEnBuyukKordinat[i],zEnBuyukKordinat[i]);



            printf("%f %f %f\n",xEnBuyukKordinat[i],yEnKucukKordinat[i],zEnKucukKordinat[i]);

            printf("%f %f %f\n",xEnBuyukKordinat[i],yEnKucukKordinat[i],zEnBuyukKordinat[i]);


            printf("%f %f %f\n",xEnBuyukKordinat[i],yEnBuyukKordinat[i],zEnKucukKordinat[i]);

            printf("%f %f %f\n\n",xEnBuyukKordinat[i],yEnBuyukKordinat[i],zEnBuyukKordinat[i]);

            /*
            X    Y     Z
            1    2     3
            10   20    30
            -
            --------------------
            9    18    27



            X    Y    Z
            1    2    3
            1    2    30
            1    29   3
            1    29   30
            28   2    3
            28   2    30
            28   29   3
            28   29   30


            */

            /*

            xEnKucukKordinat[20]
            yEnKucukKordinat[20]
            zEnKucukKordinat[20]

            xEnBuyukKordinat[20]
            yEnBuyukKordinat[20]
            zEnBuyukKordinat[20]







            */
        }
    }
}

void kureIcindeKalanNoktaHesaplama()
{
    //

    //system("cls");
    printf("Lutfen bir X kordinati giriniz...");
    scanf("%f",&kullaniciX);
    printf("Lutfen bir Y kordinati giriniz...");
    scanf("%f",&kullaniciY);
    printf("Lutfen bir Z kordinati giriniz...");
    scanf("%f",&kullaniciZ);
    printf("Lutfen bir Yaricap giriniz...");
    scanf("%f",&yariCap);
    printf("\nBelirlenen kordinat ve yaricap(R) bilgisi\n");
    printf("X: %f\n",kullaniciX);
    printf("Y: %f\n",kullaniciY);
    printf("Z: %f\n",kullaniciZ);
    printf("R: %f\n",yariCap);


    for(int i = 0; i < dosyaSayisi; i++)
    {


        if(okunmayacakDosya[i] != 1)
        {
            int mv = 0;
            //printf("%d Dosyasinda Kurenin icinde olan alanlar\n",i);

            // #pragma omp parallel
            // #pragma omp for
            printf("\nSECIM4\n");
            printf("%s\n",dosyaIsimleri[i]);
            for(int k = 6; k <= DosyaToSatir[i]; k++)
            {

                //printf("============================\n");

                float xFarki,yFarki,zFarki;
                xFarki = kullaniciX-xKordinatlari[i][k];
                yFarki = kullaniciY-yKordinatlari[i][k];
                zFarki = kullaniciZ-zKordinatlari[i][k];

                // printf("Farki : %f  %f  %f\n", xFarki,yFarki,zFarki);
                // printf("============================\n");
                float KureHesapla;
                KureHesapla = sqrt( pow(xFarki,2) + pow(yFarki,2) + pow(zFarki,2)  );
                // printf("==========%f==========\n",KureHesapla);
                if( KureHesapla <= yariCap)
                {
                    //printf("Kure Hesapla %f ",KureHesapla);
                    //   printf("\tGirdi %f\n", xKor);
                    kureXKordinatlari[i][mv] = xKordinatlari[i][k];
                    kureYKordinatlari[i][mv] = yKordinatlari[i][k];
                    kureZKordinatlari[i][mv] = zKordinatlari[i][k];
                    kureRKordinatlari[i][mv] = Kirmizi[i][k];
                    kureGKordinatlari[i][mv] = Yesil[i][k];
                    kureBKordinatlari[i][mv] = Mavi[i][k];

                    if(dosyaAlanlarType[i] == 2002)
                    {
                        printf("%f  %f  %f\n", kureXKordinatlari[i][mv], kureYKordinatlari[i][mv],kureZKordinatlari[i][mv]);
                    }
                    else if(dosyaAlanlarType[i] == 2001)
                    {
                        printf("%f  %f  %f %d %d %d \n", kureXKordinatlari[i][mv], kureYKordinatlari[i][mv],kureZKordinatlari[i][mv],kureRKordinatlari[i][mv],kureGKordinatlari[i][mv], kureBKordinatlari[i][mv]);
                    }

                    mv++;
                    kacSatirKureVar[i] = mv;

                }

            }
        }
    }
}

void outputOlustur()
{
    int check;
    check = system("mkdir outputs");
    if (!check)
        printf("Klasor Olusturuldu.\n");
    else
    {
        printf("Varolan klasor. Icerisine yeni veriler yaziliyor.\n");
    }
    /*
        dosyaAlanlarType[dosyaKodu] = 2001; xyzrgb
        dosyaAlanlarType[dosyaKodu] = 2002;  xyz
        */

    //system("mkdir outputs");
    printf("Cikti dosyalari outputs klasorunun icerisine olusturuluyor.\n");
    printf("Lutfen bekleyiniz. Bu islem uzun surebilir...\n");

    FILE *hedef_dosya;
    hedef_dosya = fopen("outputs/output.nkt", "w+");

    fprintf(hedef_dosya,"SECIM1\n");

    for(int i = 0; i<dosyaSayisi; i++)
{
        if(DosyaController[i] == 1000)
        {
            //Version Hatasi
            fprintf(hedef_dosya,"%s Dosyasinin VERSION basligi hatalidir.\n", dosyaIsimleri[i]);
        }
        else if(DosyaController[i] == 1001)
        {
            //Alanlar Hatasi
            fprintf(hedef_dosya,"%s Dosyasinin ALANLAR basligi hatalidir.\n", dosyaIsimleri[i]);
        }
        else if(DosyaController[i] == 1002)
        {
            //Nokta Hatasi
            fprintf(hedef_dosya,"%s Dosyasinin NOKTALAR  basligi hatalidir.\n", dosyaIsimleri[i]);
        }
        else if(DosyaController[i] == 1003)
        {
            //Data Hatasi
            fprintf(hedef_dosya,"%s Dosyasinin DATA basligi hatalidir.\n", dosyaIsimleri[i]);
        }
        else if(DosyaController[i] == 1004)
        {
            //Kordinat Hatasi
            fprintf(hedef_dosya,"%s Dosyasinin satir numarasi %d olan kordinatinda kordinat hatasi bulunmaktadir.\n",dosyaIsimleri[i],DosyaControllerSatirNo[i]);

        }
        else if(DosyaController[i] == 1021)
        {
            //Kordinat Hatasi
            fprintf(hedef_dosya,"%s Dosyasinin NOKTALAR  basligi hatalidir.\n",dosyaIsimleri[i]);
        }
        else if(DosyaController[i] == 1031)
        {
            //Kordinat Hatasi
            fprintf(hedef_dosya,"%s Dosyasinin  NOKTALAR basligi ile nokta sayisi eslesmemektedir.\n",dosyaIsimleri[i]);

        }
        else if(DosyaController[i] == 1005)
        {
            //Renk
            fprintf(hedef_dosya,"%s Dosyasinin satir numarasi %d olan kordinatinda renk hatasi bulunmaktadir.\n",dosyaIsimleri[i],DosyaControllerSatirNo[i]);

        }
        else if(DosyaController[i] == 2001)
        {

            fprintf(hedef_dosya,"%s Dosyasinin %d  satirinda kurallara uygun olmayan kordinat bulunmaktadir..\n",dosyaIsimleri[i],DosyaControllerSatirNo[i]);
        }

        else
        {
            fprintf(hedef_dosya,"%s Dosyasi uyumludur.\n",dosyaIsimleri[i]);
        }

    }

    fprintf(hedef_dosya,"SECIM2\n");
    for(int i = 0; i<dosyaSayisi; i++)
{
       if(okunmayacakDosya[i] != 1)
       {
        fprintf(hedef_dosya,"%s Dosyasi\n",dosyaIsimleri[i]);
        if(dosyaAlanlarType[i] == 2002)
        {



        fprintf(hedef_dosya,"En uzak mesafe\n");
        fprintf(hedef_dosya,"%f %f %f\n",xKordinatlari[i][uzakKordinatSatirNo[i][0]],yKordinatlari[i][uzakKordinatSatirNo[i][0]],zKordinatlari[i][uzakKordinatSatirNo[i][0]]);
        fprintf(hedef_dosya,"%f %f %f\n",xKordinatlari[i][uzakKordinatSatirNo[i][1]],yKordinatlari[i][uzakKordinatSatirNo[i][1]],zKordinatlari[i][uzakKordinatSatirNo[i][1]]);
        fprintf(hedef_dosya,"En yakin mesafe\n");
        fprintf(hedef_dosya,"%f %f %f\n",xKordinatlari[i][yakinKordinatSatirNo[i][0]],yKordinatlari[i][yakinKordinatSatirNo[i][0]],zKordinatlari[i][yakinKordinatSatirNo[i][0]]);
        fprintf(hedef_dosya,"%f %f %f\n",xKordinatlari[i][yakinKordinatSatirNo[i][1]],yKordinatlari[i][yakinKordinatSatirNo[i][1]],zKordinatlari[i][yakinKordinatSatirNo[i][1]]);
        }
        else if(dosyaAlanlarType[i] == 2001)
        {
        fprintf(hedef_dosya,"En uzak mesafe\n");
        fprintf(hedef_dosya,"%f %f %f %d %d %d\n",xKordinatlari[i][uzakKordinatSatirNo[i][0]],yKordinatlari[i][uzakKordinatSatirNo[i][0]],zKordinatlari[i][uzakKordinatSatirNo[i][0]],Kirmizi[i][uzakKordinatSatirNo[i][0]],Yesil[i][uzakKordinatSatirNo[i][0]],Mavi[i][uzakKordinatSatirNo[i][0]]);
        fprintf(hedef_dosya,"%f %f %f %d %d %d\n",xKordinatlari[i][uzakKordinatSatirNo[i][1]],yKordinatlari[i][uzakKordinatSatirNo[i][1]],zKordinatlari[i][uzakKordinatSatirNo[i][1]],Kirmizi[i][uzakKordinatSatirNo[i][1]],Yesil[i][uzakKordinatSatirNo[i][1]],Mavi[i][uzakKordinatSatirNo[i][1]]);
        fprintf(hedef_dosya,"En yakin mesafe\n");
        fprintf(hedef_dosya,"%f %f %f %d %d %d\n",xKordinatlari[i][yakinKordinatSatirNo[i][0]],yKordinatlari[i][yakinKordinatSatirNo[i][0]],zKordinatlari[i][yakinKordinatSatirNo[i][0]],Kirmizi[i][yakinKordinatSatirNo[i][0]],Yesil[i][yakinKordinatSatirNo[i][0]],Mavi[i][yakinKordinatSatirNo[i][0]]);
        fprintf(hedef_dosya,"%f %f %f %d %d %d\n",xKordinatlari[i][yakinKordinatSatirNo[i][1]],yKordinatlari[i][yakinKordinatSatirNo[i][1]],zKordinatlari[i][yakinKordinatSatirNo[i][1]],Kirmizi[i][yakinKordinatSatirNo[i][1]],Yesil[i][yakinKordinatSatirNo[i][1]],Mavi[i][yakinKordinatSatirNo[i][1]]);
        }
       }



    }


    fprintf(hedef_dosya,"SECIM3\n");
    for(int i = 0; i<dosyaSayisi; i++)
{
        if(okunmayacakDosya[i] != 1)
       {
        fprintf(hedef_dosya,"%s Dosyasi\n",dosyaIsimleri[i]);
        fprintf(hedef_dosya,"%f %f %f\n",xEnKucukKordinat[i],yEnKucukKordinat[i],zEnKucukKordinat[i]);
        fprintf(hedef_dosya,"%f %f %f\n",xEnKucukKordinat[i],yEnKucukKordinat[i],zEnBuyukKordinat[i]);
        fprintf(hedef_dosya,"%f %f %f\n",xEnKucukKordinat[i],yEnBuyukKordinat[i],zEnKucukKordinat[i]);
        fprintf(hedef_dosya,"%f %f %f\n",xEnKucukKordinat[i],yEnBuyukKordinat[i],zEnBuyukKordinat[i]);
        fprintf(hedef_dosya,"%f %f %f\n",xEnBuyukKordinat[i],yEnKucukKordinat[i],zEnKucukKordinat[i]);
        fprintf(hedef_dosya,"%f %f %f\n",xEnBuyukKordinat[i],yEnKucukKordinat[i],zEnBuyukKordinat[i]);
        fprintf(hedef_dosya,"%f %f %f\n",xEnBuyukKordinat[i],yEnBuyukKordinat[i],zEnKucukKordinat[i]);
        fprintf(hedef_dosya,"%f %f %f\n",xEnBuyukKordinat[i],yEnBuyukKordinat[i],zEnBuyukKordinat[i]);
       }
    }

    fprintf(hedef_dosya,"SECIM4\n");
    fprintf(hedef_dosya,"cx = %f\n",kullaniciX);
    fprintf(hedef_dosya,"cy = %f\n",kullaniciY);
    fprintf(hedef_dosya,"cz = %f\n",kullaniciZ);
    fprintf(hedef_dosya,"cr = %f\n",yariCap);
    for(int i = 0; i<dosyaSayisi; i++)
{
           if(okunmayacakDosya[i] != 1)
       {
        fprintf(hedef_dosya,"%s Dosyasi\n",dosyaIsimleri[i]);
        fprintf(hedef_dosya,"ALANLAR ");
        if(dosyaAlanlarType[i] == 2001)
        {
            fprintf(hedef_dosya,"x y z r g b\n");
        }
        else if(dosyaAlanlarType[i] == 2002)
        {
            fprintf(hedef_dosya,"x y z\n");
        }
        fprintf(hedef_dosya,"NOKTALAR %d\n",NoktaSay[i]);
        fprintf(hedef_dosya,"DATA ");
        //int dosyaType[20]; // 1 ascii 2 binary
        if(dosyaType[i] == 1)
        {
            fprintf(hedef_dosya,"ascii\n");
        }
        else if(dosyaType[i] == 2)
        {
            fprintf(hedef_dosya,"binary\n");
        }
        if(kacSatirKureVar[i] > 0 )
        {
            for(int m = 0; m< kacSatirKureVar[i]; m++)
            {
                if(dosyaAlanlarType[i] == 2002)
                {
                    fprintf(hedef_dosya,"%f %f %f\n",kureXKordinatlari[i][m],kureYKordinatlari[i][m],kureZKordinatlari[i][m]);
                }
                else if(dosyaAlanlarType[i] == 2001)
                {
                    fprintf(hedef_dosya,"%f %f %f %d %d %d\n",kureXKordinatlari[i][m],kureYKordinatlari[i][m],kureZKordinatlari[i][m],kureRKordinatlari[i][m],kureGKordinatlari[i][m],kureBKordinatlari[i][m]);
                }
            }
        }
        else
        {
            fprintf(hedef_dosya,"Kurenin icerisinde kalan herhangi bir nokta yoktur.\n");

        }
       }
    }
    fprintf(hedef_dosya,"SECIM5\n");
    for(int i = 0; i<dosyaSayisi; i++)
{
           if(okunmayacakDosya[i] != 1)
       {
        fprintf(hedef_dosya,"%s Dosyasi\n",dosyaIsimleri[i]);
        fprintf(hedef_dosya,"%f\n", ortalamaMesafe[i]);
       }
    }

fclose(hedef_dosya);
}


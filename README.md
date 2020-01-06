
# 3 BOYUTLU GÖRÜNTÜ DOSYALARI PROJESİ
- Projede farklı türdeki 3 boyulu görüntü dosyalarından okuma yapılarak verilecek
problemlerin çözümü istenmektedir.
Amaç: Proje gerçekleştirimi ile beraber öğrencilerin dosyalama ve lineer cebir
konularında program yazabilmesi amaçlamaktadır.
Programlama Dili: Proje C dili kullanılarak gerçekleştirilecektir.
1. Problem Tanımı
Projede sizden istenen, bir klasörün içinde bulunan tüm dosyalardan ayrı ayrı 3 boyutlu nokta
verilerini okuyarak bilgileri bellekte saklamanızdır. Dosyalar .nkt uzantılı olarak
kaydedilmiştir. 3 boyutlu nokta verileri nokta verileri dosyasında aşağıda belirtilen formatta
saklanmaktadır.


>#Noktalar dosya formatı
VERSION 1
ALANLAR x y z r g b
NOKTALAR 213
DATA ascii
0.93773 0.33763 0 124 23 255
0.90805 0.35641 0 114 145 123
0.81915 0.32 0 2 5 250
0.97192 0.278 0 255 255 255




>#Noktalar dosya formatı
VERSION 1
ALANLAR x y z
NOKTALAR 204800
DATA binary
ø €% À àÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
áÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
ÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
ÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá


Dosya 1 Dosya 2
Dosyanın ilk satırı açıklama satırı, ikinci satırı ise dosyanın sürümünü göstermektedir.
ALANLAR x y z # şeklinde belirtilmiş ise noktaların 3 boyutta bilgilerinin verildiği kabul edilir.
ALANLAR x y z r g b # şeklinde belirtilmiş ise noktaların 3 boyutta bilgilerinin yanında renk bilgiside
kırmızı yeşil mavi kodları ile birlikte verildiği kabul edilir. 
NOKTALAR 213 # dosyada bulunan toplam nokta sayısını belirtir.
DATA ascii veya DATA binary satırında ise dosyadaki noktaların koordinat bilgilerinin ASCII formatında
mı yoksa BINARY formatında mı saklandığı belirtilmektedir.
Noktalar float formatında, renk bilgileri ise tam sayı formatında saklanmaktadır.
## # 1.1 Önemli Özellikler
Bir klasörün içinde bilinmeyen sayıda dosyadan noktaları okuyup bellekte saklamanız
gerekmektedir.
- Dosyadan okuma işlemi sırasında veya okuma işleminden sonra kontrol
gerçekleştirmeniz gerekmektedir. Dosyanın başlık bilgileri yukarıda verilen formatlara
uygun değilse dosyadan okuma yapılmaması ve hata mesajı verilmesi gerekir.
- Noktalar dosya formatı
- VERSION 1
- ALANLAR x y z r g b
- NOKTALAR 213
- DATA ascii
Başlık Bilgileri
- Dosyadan okuma yapıldıktan sonra okunan nokta sayısı başlık kısmındaki
“NOKTALAR 123” ile belirtilen sayı ile aynı değilse uygun hata mesajı yazdırılmalıdır.
Başlık alanında “ALANLAR x y z r g b” olarak belirtilen şekilde noktalar verilmemişse
ilgili satırdaki nokta bilgisi ile ilgili hata mesajı verilmelidir.
Örneğin : 156. Nokta verisi r g b bilgileri olmadan verilmiştir.
2. İsterler
Her bir dosyadan okunan noktalar için ayrı ayrı aşağıdaki konular hesaplanmalıdır :
- Birbirine en yakın nokta ve en uzak noktaların bilgileri ve nokta numaraları
- Tüm noktaları içine alacak bir küpün kenar nokta bilgileri
- Merkezinin 3 boyutlu koordinatı ve yarıçapı bilgileri kullanıcıdan istenilen bir kürenin
içinde kalan noktaların bilgileri ve nokta numaraları
- Her bir noktanın birbirlerine olan uzaklıklarının ortalaması
- Tüm istertlerin sonuçlarının “output.nkt” dosyası içerisine kayıt edilmesi
gerekmektedir. Output.nkt dosyasının formatı aşağıdaki gibi olmalıdır:
output.nkt
> SECIM1
Tüm dosyalar uyumludur.
SECIM2
0.93773 0.33763 0 124 23 255
0.90805 0.35641 0 114 145 123
0.93773 0.33763 0 124 23 255
0.90805 0.35641 0 114 145 123
SECIM3
0.93773 0.33763 0 124 23 255
0.90805 0.35641 0 114 145 123
0.81915 0.32 0 2 5 250
0.97192 0.278 0 255 255 255
…
SECIM4
cx=(Kullanıcıdan Alinan Kurenin x Degeri)
cy=(Kullanıcıdan Alinan Kurenin y Degeri)
cz=(Kullanıcıdan Alinan Kurenin z Degeri)
cr=(Kullanıcıdan Alinan Kurenin r Degeri)
ALANLAR x y z r g b
NOKTALAR 213
DATA ascii
0.90805 0.35641 0 114 145 123
0.81915 0.32 0 2 5 250
…
SECIM5
0.93773



> SECIM1
Tüm dosyalar uyumludur.
SECIM2
ø €% À àÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
áÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
ÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
ÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
SECIM3
ø €% À àÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
áÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
ÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
ÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
…
SECIM4
cx=(Kullanıcıdan Alinan Kurenin x Degeri)
cy=(Kullanıcıdan Alinan Kurenin y Degeri)
cz=(Kullanıcıdan Alinan Kurenin z Degeri)
cr=(Kullanıcıdan Alinan Kurenin r Degeri)
ALANLAR x y z r g b
NOKTALAR 213
DATA binary
ø €% À àÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
áÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá
…
SECIM5
àÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿáÿá


## 3. Uygulama Arayüzü
Uygulamaya ait menü aşağıdaki gibi olmalıdır.
1) Dosya Kontrolü: Kullanıcı 1 tuşuna bastığında aşağıdaki işlem gerçekleşecektir.
- Başarılı : Tüm dosyalar uyumludur.
- Başarısız: Dökümanda belirtililen hata mesajları ekrana yazdırılmalıdır:
o “156. Nokta verisi r g b bilgileri olmadan verilmiştir.”
o “A.nkt dosyasındaki nokta sayısı geçerli değildir.”
2) En Yakın/Uzak Noktalar: Kullanıcı 2 tuşuna bastığında aşağıdaki işlem gerçekleşecektir.
- Birbirine en yakın nokta ve en uzak noktaların bilgileri ve nokta numaraları
3) Küp: Kullanıcı 3 tuşuna bastığında aşağıdaki işlem gerçekleşecektir.
- Tüm noktaları içine alacak bir küpün kenar nokta bilgileri
4) Küre: Kullanıcı 4 tuşuna bastığında aşağıdaki işlem gerçekleşecektir.
- Merkezinin 3 boyutlu koordinatı ve yarıçapı bilgileri kullanıcıdan istenilen bir kürenin
içinde kalan noktaların bilgileri ve nokta numaraları
5) Nokta Uzaklıkları: Kullanıcı 5 tuşuna bastığında aşağıdaki işlem gerçekleşecektir.
- Her bir noktanın birbirlerine olan uzaklıklarının ortalaması
## 4. ÖNEMLI NOTLAR
- Proje sunum gününde rapor (hard copy) teslim edilmesi gerekmektedir.
- Proje ile ilgili örnek problem ve dosya E destek üzerinden ulaştırılacaktır.
- Rapor IEEE formatında (önceki yıllarda verilen formatta) 4 sayfa, akış diyagramı veya yalancı
kod içeren, özet, giriş, yöntem, deneysel sonuçlar, sonuç ve kaynakça bölümünden oluşmalıdır.
- Dersin takibi projenin teslimi dahil edestek.kocaeli.edu.tr sistemi üzerinden yapılacaktır.
edestek.kocaeli.edu.tr sitesinde belirtilen tarihten sonra getirilen projeler kabul edilmeyecektir.
- 04.10.2019 Cuma günü saat 14:00 da Büyük Amfi de proje ile ilgili toplantı yapılacaktır. Tüm
sorularınızı toplantıda sorabilirsiniz. Toplantı saatine kadar proje dökümanını inceleyerek
sorularınızı not almanız gerekmektedir.
- Demo tarihleri daha sonra duyurulacaktır.
- Demo sırasında algoritma, geliştirdiğiniz kodun çeşitli kısımlarının ne amaçla yazıldığı ve
geliştirme ortamı hakkında sorular sorulabilir.
- Kullandığınız herhangi bir satır kodu açıklamanız istenebilir.
- Programlama Laboratuvarı I dersine ait kuralları aşağıdaki linkten okumanız
gerekmektedir.

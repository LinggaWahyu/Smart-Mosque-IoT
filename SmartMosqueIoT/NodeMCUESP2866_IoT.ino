#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include  "RTClib.h"

ESP8266WiFiMulti WiFiMulti;
LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS1307 rtc;

int Wifi = D0;
int Kipas = D3;
int Sound = D4;

char namaHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

int jamShubuh = 0, menitShubuh = 0;
int jamDhuhur = 0, menitDhuhur = 0;
int jamAshar = 0, menitAshar = 0;
int jamMaghrib = 0, menitMaghrib = 0;
int jamIsya = 0, menitIsya = 0;

void setup()
{
  Serial.begin(115200);
  lcd.begin();

  // set Wifi SSID dan passwordnya
  WiFiMulti.addAP("AndroidAP8082", "aa11bb22");

  lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  lcd.clear();

  rtc.begin();

  if (! rtc.begin()) {
    Serial.println("RTC TIDAK TERBACA");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  pinMode(Sound, OUTPUT);
  pinMode(Wifi, OUTPUT);
  pinMode(Kipas, OUTPUT);

  digitalWrite(Wifi, HIGH);
  digitalWrite(Sound, HIGH);
  digitalWrite(Kipas, HIGH);
}

void loop()
{
  DateTime now = rtc.now();

  if (jamShubuh == 00 && menitShubuh == 00) {
    ambilWaktu();
  }

  awallcd();
  baris2();
  waktusholat();
  
}

void ambilWaktu() {
  // tunggu koneksi Wifi
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    HTTPClient httpjamShubuh;
    HTTPClient httpmenitShubuh;
    HTTPClient httpjamDhuhur;
    HTTPClient httpmenitDhuhur;
    HTTPClient httpjamAshar;
    HTTPClient httpmenitAshar;
    HTTPClient httpjamMaghrib;
    HTTPClient httpmenitMaghrib;
    HTTPClient httpjamIsya;
    HTTPClient httpmenitIsya;
    HTTPClient httpCrawlingWaktu;

    // ganti dengan URL API Last Feed punyamu sendiri
    httpCrawlingWaktu.begin("http://iotsmartmosque.000webhostapp.com/apiJam.php");
    httpjamShubuh.begin("http://iotsmartmosque.000webhostapp.com/crawlingJamShubuh.php");
    httpmenitShubuh.begin("http://iotsmartmosque.000webhostapp.com/crawlingMenitShubuh.php");
    httpjamDhuhur.begin("http://iotsmartmosque.000webhostapp.com/crawlingJamDhuhur.php");
    httpmenitDhuhur.begin("http://iotsmartmosque.000webhostapp.com/crawlingMenitDhuhur.php");
    httpjamAshar.begin("http://iotsmartmosque.000webhostapp.com/crawlingJamAshar.php");
    httpmenitAshar.begin("http://iotsmartmosque.000webhostapp.com/crawlingMenitAshar.php");
    httpjamMaghrib.begin("http://iotsmartmosque.000webhostapp.com/crawlingJamMaghrib.php");
    httpmenitMaghrib.begin("http://iotsmartmosque.000webhostapp.com/crawlingMenitMaghrib.php");
    httpjamIsya.begin("http://iotsmartmosque.000webhostapp.com/crawlingJamIsya.php");
    httpmenitIsya.begin("http://iotsmartmosque.000webhostapp.com/crawlingMenitIsya.php");

    // mulai koneksi dan ambil HTTP Header
    httpCrawlingWaktu.GET();
    int httpCode = httpjamAshar.GET();
    httpmenitAshar.GET();
    httpjamShubuh.GET();
    httpmenitShubuh.GET();
    httpjamDhuhur.GET();
    httpmenitDhuhur.GET();
    httpjamMaghrib.GET();
    httpmenitMaghrib.GET();
    httpjamIsya.GET();
    httpmenitIsya.GET();
    Serial.printf("\n\n[HTTP] GET... code: %d\n", httpCode);

    // httpCode akan bernilai negatif bila error
    if (httpCode > 0)
    {

      // bila nilai dari server diterima
      if (httpCode == HTTP_CODE_OK)
      {
        // cetak string json dari server
        String json = httpjamShubuh.getString();
        jamShubuh = json.toInt();
        json = httpmenitShubuh.getString();
        menitShubuh = json.toInt();
        Serial.print("Waktu Shubuh = ");
        Serial.print(jamShubuh);
        Serial.print(" : ");
        Serial.print(menitShubuh);
        json = httpjamDhuhur.getString();
        jamDhuhur = json.toInt();
        json = httpmenitDhuhur.getString();
        menitDhuhur = json.toInt();
        Serial.print("\nWaktu Dhuhur = ");
        Serial.print(jamDhuhur);
        Serial.print(" : ");
        Serial.print(menitDhuhur);
        json = httpjamAshar.getString();
        jamAshar = json.toInt();
        Serial.print("\nWaktu Ashar = ");
        Serial.print(jamAshar);
        Serial.print(" : ");
        json = httpmenitAshar.getString();
        menitAshar = json.toInt();
        Serial.print(menitAshar);
        json = httpjamMaghrib.getString();
        jamMaghrib = json.toInt();
        json = httpmenitMaghrib.getString();
        menitMaghrib = json.toInt();
        Serial.print("\nWaktu Maghrib = ");
        Serial.print(jamMaghrib);
        Serial.print(" : ");
        Serial.print(menitMaghrib);
        json = httpjamIsya.getString();
        jamIsya = json.toInt();
        json = httpmenitIsya.getString();
        menitIsya = json.toInt();
        Serial.print("\nWaktu Isya = ");
        Serial.print(jamIsya);
        Serial.print(" : ");
        Serial.print(menitIsya);
      }

    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", httpjamAshar.errorToString(httpCode).c_str());
    }
    // tutup koneksi HTTP
    httpCrawlingWaktu.end();
    httpjamShubuh.end();
    httpmenitShubuh.end();
    httpjamDhuhur.end();
    httpmenitDhuhur.end();
    httpjamAshar.end();
    httpmenitAshar.end();
    httpjamMaghrib.end();
    httpmenitMaghrib.end();
    httpjamIsya.end();
    httpmenitIsya.end();
  }
}

void baris2() {

  lcd.setCursor(4, 2);
  lcd.print("Shubuh ");
  lcd.print(jamShubuh);
  lcd.print(":");
  lcd.print(menitShubuh);
  delay(1000);
  awallcd();
  lcd.setCursor(0, 2);
  lcd.print("                   ");
  lcd.setCursor(4, 2);
  lcd.print("Dhuhur ");
  lcd.print(jamDhuhur);
  lcd.print(":");
  lcd.print(menitDhuhur);
  delay(1000);
  awallcd();
  lcd.setCursor(0, 2);
  lcd.print("                   ");
  lcd.setCursor(5, 2);
  lcd.print("Ashar ");
  lcd.print(jamAshar);
  lcd.print(":");
  lcd.print(menitAshar);
  delay(1000);
  awallcd();
  lcd.setCursor(0, 2);
  lcd.print("                   ");
  lcd.setCursor(3, 2);
  lcd.print("Maghrib ");
  lcd.print(jamMaghrib);
  lcd.print(":");
  lcd.print(menitMaghrib);
  delay(1000);
  awallcd();
  lcd.setCursor(0, 2);
  lcd.print("                   ");
  lcd.setCursor(5, 2);
  lcd.print("Isya ");
  lcd.print(jamIsya);
  lcd.print(":");
  lcd.print(menitIsya);
  delay(1000);
  awallcd();
  lcd.setCursor(0, 2);
  lcd.print("                   ");
}

void printAngka(int digits) {
  if (digits < 10) {
    lcd.print('0');
    lcd.print(digits);
  }
  else lcd.print(digits);
}

void awallcd() {
  DateTime now = rtc.now();

  lcd.setCursor(2, 0);
  lcd.print(namaHari[now.dayOfTheWeek()]);
  lcd.print(",");
  printAngka(now.day());
  lcd.print("-");
  printAngka(now.month());
  lcd.print("-");
  printAngka(now.year());

  lcd.setCursor(6, 1);
  printAngka(now.hour());
  lcd.print(":");
  printAngka(now.minute());
  lcd.print(":");
  printAngka(now.second());

  Serial.println(now.hour());
  lcd.setCursor(1, 3);
  lcd.print("Jangan Lupa Sholat");
}

void waktusholat() {
  DateTime now = rtc.now();

  int jamJamaahShubuh = jamShubuh;
  int menitJamaahShubuh = menitShubuh;

  int jamJamaahDhuhur = jamDhuhur;
  int menitJamaahDhuhur = menitDhuhur;

  int jamJamaahAshar = jamAshar;
  int menitJamaahAshar = menitAshar;

  int jamJamaahMaghrib = jamMaghrib;
  int menitJamaahMaghrib = menitMaghrib;

  int jamJamaahIsya = jamIsya;
  int menitJamaahIsya = menitIsya;

  if ((menitShubuh + 20) > 60) {
    jamJamaahShubuh = jamShubuh + 1;
    menitJamaahShubuh = (menitShubuh + 20) - 60;
  } else {
    jamJamaahShubuh = jamShubuh;
    menitJamaahShubuh = menitShubuh + 20;
  }

  if ((menitDhuhur + 20) > 60) {
    jamJamaahDhuhur = jamDhuhur + 1;
    menitJamaahDhuhur = (menitDhuhur + 20) - 60;
  } else {
    jamJamaahDhuhur = jamDhuhur;
    menitJamaahDhuhur = menitDhuhur + 20;
  }

  if ((menitAshar + 20) > 60) {
    jamJamaahAshar = jamAshar + 1;
    menitJamaahAshar = (menitAshar + 20) - 60;
  } else {
    jamJamaahAshar = jamAshar;
    menitJamaahAshar = menitAshar + 20;
  }

  if ((menitMaghrib + 20) > 60) {
    jamJamaahMaghrib = jamMaghrib + 1;
    menitJamaahMaghrib = (menitMaghrib + 20) - 60;
  } else {
    jamJamaahMaghrib = jamMaghrib;
    menitJamaahMaghrib = menitMaghrib + 20;
  }

  if ((menitIsya + 20) > 60) {
    jamJamaahIsya = jamIsya + 1;
    menitJamaahIsya = (menitIsya + 20) - 60;
  } else {
    jamJamaahIsya = jamIsya;
    menitJamaahIsya = menitIsya + 20;
  }

  if (now.hour() == jamShubuh && now.minute() == (menitShubuh - 6)) {
    digitalWrite(Sound, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(1, 2);
      lcd.print("Akan Masuk Shubuh");
      delay(1000);
    }
  }

  if (now.hour() == jamShubuh && now.minute() == menitShubuh) {
    digitalWrite(Sound, HIGH);
    digitalWrite(Kipas, LOW);
    digitalWrite(Wifi, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(1, 2);
      lcd.print("Masuk Waktu Shubuh");
      delay(1000);
    }
  }

  if (now.hour() == jamJamaahShubuh && now.minute() == menitJamaahShubuh) {
    digitalWrite(Kipas, HIGH);
    digitalWrite(Wifi, HIGH);
  }

  if (now.hour() == jamDhuhur && now.minute() == (menitDhuhur - 6)) {
    digitalWrite(Sound, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(1, 2);
      lcd.print("Akan Masuk Dhuhur");
      delay(1000);
    }
  }

  if (now.hour() == jamDhuhur && now.minute() == menitDhuhur) {
    digitalWrite(Kipas, LOW);
    digitalWrite(Wifi, LOW);
    digitalWrite(Sound, HIGH);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(1, 2);
      lcd.print("Masuk Waktu Dhuhur");
      delay(1000);
    }
  }

  if (now.hour() == jamJamaahDhuhur && now.minute() == menitJamaahDhuhur) {
    digitalWrite(Kipas, HIGH);
    digitalWrite(Wifi, HIGH);
  }
  if (14 == jamAshar && 34 == (menitAshar - 6)) {
    digitalWrite(Sound, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(1, 2);
      lcd.print("Akan Masuk Ashar");
      delay(1000);
    }
  }

  if (now.hour() == jamAshar && now.minute() == menitAshar) {
    digitalWrite(Sound, HIGH);
    digitalWrite(Kipas, LOW);
    digitalWrite(Wifi, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(0, 2);
      lcd.print("Masuk Waktu Ashar");
      delay(1000);
    }
  }

  if (now.hour() == jamJamaahAshar && now.minute() == menitJamaahAshar) {
    digitalWrite(Kipas, HIGH);
    digitalWrite(Wifi, HIGH);
  }
  if (now.hour() == jamMaghrib && now.minute() == (menitMaghrib - 6)) {
    digitalWrite(Sound, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(1, 2);
      lcd.print("Akan Masuk Maghrib");
      delay(1000);
    }
  }

  if (now.hour() == jamMaghrib && now.minute() == menitMaghrib) {
    digitalWrite(Sound, HIGH);
    digitalWrite(Kipas, LOW);
    digitalWrite(Wifi, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(0, 2);
      lcd.print("Masuk Waktu Maghrib");
      delay(1000);
    }
  }

  if (now.hour() == jamJamaahMaghrib && now.minute() == menitJamaahMaghrib) {
    digitalWrite(Kipas, HIGH);
    digitalWrite(Wifi, HIGH);
  }
  if (now.hour() == jamIsya && now.minute() == (menitIsya - 6)) {
    digitalWrite(Sound, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(1, 2);
      lcd.print("Akan Masuk Isya");
      delay(1000);
    }
  }

  if (now.hour() == jamIsya && now.minute() == menitIsya) {
    digitalWrite(Sound, HIGH);
    digitalWrite(Kipas, LOW);
    digitalWrite(Wifi, LOW);
    lcd.setCursor(1, 2);
    lcd.print("                   ");
    for (int i = 0; i < 60; i++) {
      awallcd();
      lcd.setCursor(0, 2);
      lcd.print("Masuk Waktu Isya");
      delay(1000);
    }
  }

  if (now.hour() == jamJamaahIsya && now.minute() == menitJamaahIsya) {
    digitalWrite(Kipas, HIGH);
    digitalWrite(Wifi, HIGH);
  }
}

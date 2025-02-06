/********************************************************************************************************* 
   GUNAKAN BOARD "Board esp32 atau esp8266 Tipe Apa saja Yang Kalian Inginkan "
   Judul   : Telegram BOT Kontrol Relay Dengan Chat
   Fungsi  : Kendali jarak jauh via internet / internet of thingk
   Edisi   : Tutorial
   Request : Subcriber 
   Request Date : 1 April 2020
   Start Date   : 30 April 2020
   Save EEPROM Tidak Termasuk Dalam Tutorial Ini, Untuk Tambah EEPROM Hubungi Admin
   Sketch Made In San @AzkaArduinoShop
   YTC Video Blog : Video Guru MU

   AZKA ARDUINO SHOP / AZKduino Siap Membantu Tugas Sekolah Atau Kulih Kalian, Harga Di sesuaikan Dengan System Yang Akan Di Rancang
   Cara kerja Bisa Custom Sesuai Keinginan Kalian, kita bantu sampai program berjalan sesuai yang di harapkan
   Project Yang Kami Buat Multitasking Tanpa Jeda Atau Delay, Kecuali IOT Pasti Sedikit Delay Karena Proses Sending Data
   jika kalian berminat order project atau cari part komponen pendukung arduino silakan hubungi saya pada kontak di bawah ini

   Chat Konsultasi / Pembelian Via:
   - Telegram       : http://bit.ly/TelegramVGM (Call Yes) <=---=< Prioritas Via Telegram
   - Whatsapp       : http://bit.ly/WhatsappVGM (No Call)
   - WA. Penjualan  : http://bit.ly/BuyAZKDuino (No Call)
   - SMS Only       : 088212806903 (No Call)

   NB: No Call = Call Auto Block For All Number Not Save (Tidak Menerima Voice Call, Kecuali Yang Oder Project / Terdaftar Pada Contact Phone Saya)

   FOLLOW / SUBSCRIBE MEDIA SOSIAL :
   - Instagram : http://bit.ly/InstagramVGM
   - Facebook  : http://bit.ly/FacebookVGM
   - Youtube   : http://bit.ly/YoutubeVGM
   
***********************************************************************************************************/ 


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define Output_Relay1   D0 // Pin D0 = GPIO16
#define Output_Relay2   D1 // Pin D1 = GPIO5
#define Output_Relay3   D2 // Pin D2 = GPIO4
#define Output_Relay4   D3 // Pin D3 = GPIO0
#define Output_Relay5   D4 // Pin D4 = GPIO2

// Atur SSID Dan Password Wifi Router / Wifi Hotspot / Wifi Tethring Dari HP
char ssid[] = "RPL BLUD";     // Masukan Nama SSID (Besar Kecil Pengaruh)
char password[] = "codingmasadepanku";       // Masukan Password Yang Di Pakai Router


// Untuk Setting Perintah Pada Telegram Ganti Nama Dalam Tanda Kutip Sesuai Keinginan Anda 
const char* Perintah_On_1 = "/NyalakanLampuTeras";
const char* Perintah_On_2 = "/NyalakanLampuJalan";
const char* Perintah_On_3 = "/NyalakanLampuBelakang";
const char* Perintah_On_4 = "/NyalakanMesinPompa";
const char* Perintah_On_5 = "/NyalakanSirine";

const char* Perintah_Off_1 = "/MatikanLampuTeras";
const char* Perintah_Off_2 = "/MatikanLampuJalan";
const char* Perintah_Off_3 = "/MatikanLampuBelakang";
const char* Perintah_Off_4 = "/MatikanMesinPompa";
const char* Perintah_Off_5 = "/MatikanSirine";

const char* Perintah_1 = "/StatusLampuTeras";
const char* Perintah_2 = "/StatusLampuJalan";
const char* Perintah_3 = "/StatusLampuBelakang";
const char* Perintah_4 = "/StatusMesinPompa";
const char* Perintah_5 = "/StatusSirine";
const char* Perintah_6 = "/MatikanSemuaSystem";


// Masukan Token Telegram BOT Kalian (JIka Lupa Token Bisa Lihat Pada BotFather Ketikan /token)
#define BOTtoken "6469998501:AAG3hXKc16a-4CvRkaJtUJK4_ZVwqDeHhAQ"  // Masukan Token Kalian (Silakan Copy Dari Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int ON = LOW, OFF = HIGH;

int Bot_mtbs = 1000; //mean time between Untuk Lamanya Scan Pesan Baru
long Bot_lasttime;   // Pesan Terakhir 
bool Start = false;

int ledStatus1 = OFF;
int ledStatus2 = OFF;
int ledStatus3 = OFF;
int ledStatus4 = OFF;
int ledStatus5 = OFF;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String Pesan = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (Pesan == (Perintah_On_1)) {
      digitalWrite(Output_Relay1, ON);  
      ledStatus1 = ON;
      bot.sendMessage(chat_id, "Lampu Teras Sudah Menyala", "");
    }

    else if (Pesan == (Perintah_Off_1)) {
      ledStatus1 = OFF;
      digitalWrite(Output_Relay1, OFF); 
      bot.sendMessage(chat_id, "Lampu Teras Sudah Di Matikan", "");
    }
      else  if (Pesan == (Perintah_On_2)) {
      digitalWrite(Output_Relay2, ON); 
      ledStatus2 = ON;
      bot.sendMessage(chat_id, "Lampu PJU / Lampu Jalan Sudah Di Nyalakan", "");
    }

   else if (Pesan == (Perintah_Off_2)) {
      ledStatus2 = OFF;
      digitalWrite(Output_Relay2, OFF);   
      bot.sendMessage(chat_id, "Lampu PJU / Lampu Jalan Berhasil Di Matikan", "");
    }
   else if (Pesan == (Perintah_On_3)) {
      digitalWrite(Output_Relay3, ON);  
      ledStatus3 = ON;
      bot.sendMessage(chat_id, "Lampu Belakang Rumah Berhasil Di Hidupkan", "");
    }

   else if (Pesan == (Perintah_Off_3)) {
      ledStatus3 = OFF;
      digitalWrite(Output_Relay3, OFF); 
      bot.sendMessage(chat_id, "Lampu Belakang Rumah Telah Di Matikan", "");
    }
   else if (Pesan == (Perintah_On_4)) {
      digitalWrite(Output_Relay4, ON);
      ledStatus4 = ON;
      bot.sendMessage(chat_id, "Mesin Pompa Berhasil Di Hidupkan Dan Akan Automatis OFF Setelah Penuh", "");
    }

   else if (Pesan == (Perintah_Off_4)) {
      ledStatus4 = OFF;
      digitalWrite(Output_Relay4, OFF);  
      bot.sendMessage(chat_id, "Mesin Pompa Telah Di Matikan Manual", "");
    }
  else if (Pesan == (Perintah_On_5)) {
      digitalWrite(Output_Relay5, ON);  
      ledStatus5 = ON;
      bot.sendMessage(chat_id, "Sirine Berhasil Di Hidupkan Selama 5 Menit", "");
    }

   else if (Pesan == (Perintah_Off_5)) {
      ledStatus5 = OFF;
      digitalWrite(Output_Relay5, OFF);   
      bot.sendMessage(chat_id, "Sirine Berhasil Di Matikan Manual", "");
    }

   else if (Pesan == (Perintah_1)) {
        if(ledStatus1){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu Teras Saat Ini Sudah Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu Teras Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_2)) {
        if(ledStatus2){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu PJU Dalam Keadaan Aktif", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu PJU Saat Ini Mati", "");
      }
        }
        else if (Pesan == (Perintah_3)) {
        if(ledStatus3){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu Belakang Rumah Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu Belakang Rumah Saat Ini Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_4)) {
        if(ledStatus4){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Pompa Saat Ini Sedang Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Saat Ini Mesin Pompa Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_5)) {
        if(ledStatus5){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Saat Ini Sirine Dalam Keadaan Hidup Harap Segera Di Matikan Agar Tidak Berisik", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Sirine Saat Ini Mati, Sudah Aman", "");
      }
    }
        else if (Pesan == (Perintah_6)) {
          ledStatus1 = OFF;
          ledStatus2 = OFF;
          ledStatus3 = OFF;
          ledStatus4 = OFF;
          ledStatus5 = OFF;
          digitalWrite(Output_Relay1, OFF);
          digitalWrite(Output_Relay2, OFF);
          digitalWrite(Output_Relay3, OFF);
          digitalWrite(Output_Relay4, OFF);
          digitalWrite(Output_Relay5, OFF);
         bot.sendMessage(chat_id, "Lapor Pak Insan, Semua Relay Sudah Mati, Sekarang Aman", "");
        }

    else if (Pesan == "/start") {
      String welcome = "Selamat Datang Di IOT Versi arthasa.tech, " + from_name + ".\n";
      welcome += "Kontrol Peralatan Electronic Rumah Anda Melalui Telegram\n";
      welcome += "Gunakan Kode Berikut Untuk Mengontrol Relay :\n\n";
      welcome += "# ON/OFF Lampu Teras Depan Rumah:\n";
      welcome += (Perintah_On_1);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_1);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Lampu Jalanan / PJU:\n";
      welcome += (Perintah_On_2);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_2);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Lampu Belakang Rumah:\n";
      welcome += (Perintah_On_3);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_3);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Mesin Pompa:\n";
      welcome += (Perintah_On_4);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_4);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# Bunyikan & Matikan Sirine:\n";
      welcome += (Perintah_On_5);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_5);
      welcome += " <- Tekan OFF\n\n\n\n";
      
      welcome += "# Chek Status Output Realtime:\n";
      welcome += (Perintah_1);
      welcome += " - Lampu Teras\n";
      welcome += (Perintah_2);
      welcome += " - Lampu Jalan / PJU\n";
      welcome += (Perintah_3);
      welcome += " - Lampu Belakang\n";
      welcome += (Perintah_4);
      welcome += " - Mesin Pompa\n";
      welcome += (Perintah_5);
      welcome += " - Sirine\n\n";  
          
      welcome += "# Untuk Mematikan Semua Relay:\n";
      welcome += (Perintah_6);
      welcome += " - Emergency OFF \n\n\n";
      welcome += "Jangan Lupa Follow\n";
      welcome += "Instagram : artha_sa_\n";
      welcome += "https://bit.ly/igarthasa\n";
      welcome += "Website : arthasa.tech\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  client.setInsecure();               // FIX NODEMCU Wajib Board esp8266 version 2.5.0

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.longPoll = 60;   // Panjang Polling

  pinMode(Output_Relay1, OUTPUT); 
  pinMode(Output_Relay2, OUTPUT);
  pinMode(Output_Relay3, OUTPUT);
  pinMode(Output_Relay4, OUTPUT);
  pinMode(Output_Relay5, OUTPUT);    
  delay(10);
  digitalWrite(Output_Relay1, OFF);
  digitalWrite(Output_Relay2, OFF);
  digitalWrite(Output_Relay3, OFF);
  digitalWrite(Output_Relay4, OFF);
  digitalWrite(Output_Relay5, OFF);
  
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      Serial.println(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}

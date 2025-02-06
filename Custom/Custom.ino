
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define Output_Relay1   D0 // Pin D0 = GPIO16
#define Output_Relay2   D1 // Pin D1 = GPIO5
#define Output_Relay3   D2 // Pin D2 = GPIO4
#define Output_Relay4   D3 // Pin D3 = GPIO0
#define Output_Relay5   D4 // Pin D4 = GPIO2
#define Output_Relay6   D5 // Pin D5 = ###
#define Output_Relay7   D6 // Pin D6 = ###
#define Output_Relay8   D7 // Pin D7 = ###
#define Output_Relay9   D8 // Pin D8 = ###


// Atur SSID Dan Password Wifi Router / Wifi Hotspot / Wifi Tethring Dari HP
char ssid[] = "RPL BLUD";     // Masukan Nama SSID (Besar Kecil Pengaruh)
char password[] = "codingmasadepanku";       // Masukan Password Yang Di Pakai Router


// Untuk Setting Perintah Pada Telegram Ganti Nama Dalam Tanda Kutip Sesuai Keinginan Anda 
const char* Perintah_On_1 = "/NyalakanLampu1";
const char* Perintah_On_2 = "/NyalakanLampu2";
const char* Perintah_On_3 = "/NyalakanLampu3";
const char* Perintah_On_4 = "/NyalakanLampu4";
const char* Perintah_On_5 = "/NyalakanLampu5";
const char* Perintah_On_6 = "/NyalakanLampu6";
const char* Perintah_On_7 = "/NyalakanLampu7";
const char* Perintah_On_8 = "/NyalakanLampu8";
const char* Perintah_On_9 = "/NyalakanLampu9";

const char* Perintah_Off_1 = "/MatikanLampu1";
const char* Perintah_Off_2 = "/MatikanLampu2";
const char* Perintah_Off_3 = "/MatikanLampu3";
const char* Perintah_Off_4 = "/MatikanLampu4";
const char* Perintah_Off_5 = "/MatikanLampu5";
const char* Perintah_Off_6 = "/MatikanLampu6";
const char* Perintah_Off_7 = "/MatikanLampu7";
const char* Perintah_Off_8 = "/MatikanLampu8";
const char* Perintah_Off_9 = "/MatikanLampu9";

const char* Perintah_1 = "/StatusLampu1";
const char* Perintah_2 = "/StatusLampu2";
const char* Perintah_3 = "/StatusLampu3";
const char* Perintah_4 = "/StatusLampu4";
const char* Perintah_5 = "/StatusLampu5";
const char* Perintah_6 = "/StatusLampu6";
const char* Perintah_7 = "/StatusLampu7";
const char* Perintah_8 = "/StatusLampu8";
const char* Perintah_9 = "/StatusLampu9";
const char* Perintah_10 = "/NyalakanSemuaSystem";
const char* Perintah_11 = "/MatikanSemuaSystem";


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
int ledStatus6 = OFF;
int ledStatus7 = OFF;
int ledStatus8 = OFF;
int ledStatus9 = OFF;

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
      bot.sendMessage(chat_id, "Lampu 1 Sudah Menyala", "");
    }

    else if (Pesan == (Perintah_Off_1)) {
      ledStatus1 = OFF;
      digitalWrite(Output_Relay1, OFF); 
      bot.sendMessage(chat_id, "Lampu 1 Sudah Di Matikan", "");
    }
      else  if (Pesan == (Perintah_On_2)) {
      digitalWrite(Output_Relay2, ON); 
      ledStatus2 = ON;
      bot.sendMessage(chat_id, "Lampu 2 Sudah Di Nyalakan", "");
    }

   else if (Pesan == (Perintah_Off_2)) {
      ledStatus2 = OFF;
      digitalWrite(Output_Relay2, OFF);   
      bot.sendMessage(chat_id, "Lampu 2 Berhasil Di Matikan", "");
    }
   else if (Pesan == (Perintah_On_3)) {
      digitalWrite(Output_Relay3, ON);  
      ledStatus3 = ON;
      bot.sendMessage(chat_id, "Lampu 3 Berhasil Di Hidupkan", "");
    }

   else if (Pesan == (Perintah_Off_3)) {
      ledStatus3 = OFF;
      digitalWrite(Output_Relay3, OFF); 
      bot.sendMessage(chat_id, "Lampu 3 Telah Di Matikan", "");
    }
   else if (Pesan == (Perintah_On_4)) {
      digitalWrite(Output_Relay4, ON);
      ledStatus4 = ON;
      bot.sendMessage(chat_id, "Lampu 4 Berhasil Di Hidupkan", "");
    }

   else if (Pesan == (Perintah_Off_4)) {
      ledStatus4 = OFF;
      digitalWrite(Output_Relay4, OFF);  
      bot.sendMessage(chat_id, "Lampu 4 Telah Di Matikan", "");
    }
  else if (Pesan == (Perintah_On_5)) {
      digitalWrite(Output_Relay5, ON);  
      ledStatus5 = ON;
      bot.sendMessage(chat_id, "Lampu 5 Berhasil Di Hidupkan", "");
    }
   else if (Pesan == (Perintah_Off_5)) {
      ledStatus5 = OFF;
      digitalWrite(Output_Relay5, OFF);   
      bot.sendMessage(chat_id, "Lampu 5 Berhasil Di Matikan", "");
    }
      else if (Pesan == (Perintah_On_6)) {
      digitalWrite(Output_Relay6, ON);
      ledStatus6 = ON;
      bot.sendMessage(chat_id, "Lampu 6 Berhasil Di Hidupkan", "");
    }

   else if (Pesan == (Perintah_Off_6)) {
      ledStatus6 = OFF;
      digitalWrite(Output_Relay6, OFF);  
      bot.sendMessage(chat_id, "Lampu 6 Telah Di Matikan", "");
    }
      else if (Pesan == (Perintah_On_7)) {
      digitalWrite(Output_Relay7, ON);  
      ledStatus7 = ON;
      bot.sendMessage(chat_id, "Lampu 7 Berhasil Di Hidupkan", "");
    }

      else if (Pesan == (Perintah_Off_7)) {
      ledStatus7 = OFF;
      digitalWrite(Output_Relay7, OFF);   
      bot.sendMessage(chat_id, "Lampu 7 Berhasil Di Matikan", "");
    }
      else if (Pesan == (Perintah_On_8)) {
      digitalWrite(Output_Relay8, ON);  
      ledStatus8 = ON;
      bot.sendMessage(chat_id, "Lampu 8 Berhasil Di Hidupkan", "");
    }

      else if (Pesan == (Perintah_Off_8)) {
      ledStatus8 = OFF;
      digitalWrite(Output_Relay8, OFF);   
      bot.sendMessage(chat_id, "Lampu 8 Berhasil Di Matikan", "");
    }
      else if (Pesan == (Perintah_On_9)) {
      digitalWrite(Output_Relay9, ON);  
      ledStatus9 = ON;
      bot.sendMessage(chat_id, "Lampu 9 Berhasil Di Hidupkan", "");
    }

      else if (Pesan == (Perintah_Off_9)) {
      ledStatus9 = OFF;
      digitalWrite(Output_Relay9, OFF);   
      bot.sendMessage(chat_id, "Lampu 9 Berhasil Di Matikan", "");
    }



   else if (Pesan == (Perintah_1)) {
        if(ledStatus1){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 1 Saat Ini Sudah Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 1 Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_2)) {
        if(ledStatus2){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 2 Dalam Keadaan Aktif", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 2 Saat Ini Mati", "");
      }
        }
        else if (Pesan == (Perintah_3)) {
        if(ledStatus3){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 3 Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 3 Saat Ini Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_4)) {
        if(ledStatus4){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 4 Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 4 Saat Ini Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_5)) {
        if(ledStatus5){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 5 Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 5 Saat Ini Dalam Keadaan Mati", "");
      }
    }
        else if (Pesan == (Perintah_6)) {
        if(ledStatus6){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 6 Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 6 Saat Ini Dalam Keadaan Matin", "");
      }
    }
    else if (Pesan == (Perintah_7)) {
        if(ledStatus7){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 7 Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 7 Saat Ini Dalam Keadaan Mati", "");
      }
    }
    else if (Pesan == (Perintah_8)) {
        if(ledStatus8){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 8 Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 8 Saat Ini Dalam Keadaan Mati", "");
      }
    }
    else if (Pesan == (Perintah_9)) {
        if(ledStatus9){
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 9 Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lapor Pak Artha, Lampu 9 Saat Ini Dalam Keadaan Mati", "");
      }
    }

    else if (Pesan == (Perintah_10)) {
          ledStatus1 = ON;
          ledStatus2 = ON;
          ledStatus3 = ON;
          ledStatus4 = ON;
          ledStatus5 = ON;
          ledStatus6 = ON;
          ledStatus7 = ON;
          ledStatus8 = ON;
          ledStatus9 = ON;
          digitalWrite(Output_Relay1, ON);
          digitalWrite(Output_Relay2, ON);
          digitalWrite(Output_Relay3, ON);
          digitalWrite(Output_Relay4, ON);
          digitalWrite(Output_Relay5, ON);
          digitalWrite(Output_Relay6, ON);
          digitalWrite(Output_Relay7, ON);
          digitalWrite(Output_Relay8, ON);
          digitalWrite(Output_Relay9, ON);
         bot.sendMessage(chat_id, "Lapor Pak Artha, Semua Relay Sudah Menyala", "");
        }
        else if (Pesan == (Perintah_11)) {
          ledStatus1 = OFF;
          ledStatus2 = OFF;
          ledStatus3 = OFF;
          ledStatus4 = OFF;
          ledStatus5 = OFF;
          ledStatus6 = OFF;
          ledStatus7 = OFF;
          ledStatus8 = OFF;
          ledStatus9 = OFF;
          digitalWrite(Output_Relay1, OFF);
          digitalWrite(Output_Relay2, OFF);
          digitalWrite(Output_Relay3, OFF);
          digitalWrite(Output_Relay4, OFF);
          digitalWrite(Output_Relay5, OFF);
          digitalWrite(Output_Relay6, OFF);
          digitalWrite(Output_Relay7, OFF);
          digitalWrite(Output_Relay8, OFF);
          digitalWrite(Output_Relay9, OFF);
         bot.sendMessage(chat_id, "Lapor Pak Artha, Semua Relay Sudah Mati, Sekarang Aman", "");
        }

    else if (Pesan == "/start") {
      String welcome = "Selamat Datang Di IOT Versi arthasa.tech, " + from_name + ".\n";
      welcome += "Kontrol Peralatan Electronic Rumah Anda Melalui Telegram\n";
      welcome += "Gunakan Kode Berikut Untuk Mengontrol Relay :\n\n";
      welcome += "# ON/OFF Lampu 1:\n";
      welcome += (Perintah_On_1);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_1);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Lampu 2:\n";
      welcome += (Perintah_On_2);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_2);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Lampu 3:\n";
      welcome += (Perintah_On_3);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_3);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Lampu 4:\n";
      welcome += (Perintah_On_4);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_4);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Lampu 5:\n";
      welcome += (Perintah_On_5);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_5);
      welcome += " <- Tekan OFF\n\n";

      welcome += "# ON/OFF Lampu 6:\n";
      welcome += (Perintah_On_6);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_6);
      welcome += " <- Tekan OFF\n\n";

      welcome += "# ON/OFF Lampu 7:\n";
      welcome += (Perintah_On_7);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_7);
      welcome += " <- Tekan OFF\n\n";

      welcome += "# ON/OFF Lampu 8:\n";
      welcome += (Perintah_On_8);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_8);
      welcome += " <- Tekan OFF\n\n";

      welcome += "# ON/OFF Lampu 9:\n";
      welcome += (Perintah_On_9);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_9);
      welcome += " <- Tekan OFF\n\n\n";
      
      welcome += "# Chek Status Output Realtime:\n";
      welcome += (Perintah_1);
      welcome += " - Lampu 1\n\n";
      welcome += (Perintah_2);
      welcome += " - Lampu 2\n\n";
      welcome += (Perintah_3);
      welcome += " - Lampu 3\n\n";
      welcome += (Perintah_4);
      welcome += " - Lampu 4\n\n";
      welcome += (Perintah_5);
      welcome += " - Lampu 5\n\n";
      welcome += (Perintah_6);
      welcome += " - Lampu 6\n\n";
      welcome += (Perintah_7);
      welcome += " - Lampu 7\n\n";
      welcome += (Perintah_8);
      welcome += " - Lampu 8\n\n";
      welcome += (Perintah_9);
      welcome += " - Lampu 9\n\n\n";  

      welcome += "# Untuk Menyalakan Semua Relay:\n";
      welcome += (Perintah_10);
      welcome += " - Emergency ON \n\n";
      welcome += "# Untuk Mematikan Semua Relay:\n";
      welcome += (Perintah_11);
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
  pinMode(Output_Relay6, OUTPUT);
  pinMode(Output_Relay7, OUTPUT);
  pinMode(Output_Relay8, OUTPUT);
  pinMode(Output_Relay9, OUTPUT);    
  delay(10);
  digitalWrite(Output_Relay1, OFF);
  digitalWrite(Output_Relay2, OFF);
  digitalWrite(Output_Relay3, OFF);
  digitalWrite(Output_Relay4, OFF);
  digitalWrite(Output_Relay5, OFF);
  digitalWrite(Output_Relay6, OFF);
  digitalWrite(Output_Relay7, OFF);
  digitalWrite(Output_Relay8, OFF);
  digitalWrite(Output_Relay9, OFF);
  
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

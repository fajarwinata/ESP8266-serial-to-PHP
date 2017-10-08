/*
 * EEPROM ESP8266 BASE ALGORITHM
 * SEND TO SQL
 * USING WIFI NETWORK
 * BY MR. FAJAR WINATA
 * 
 */
 
#include<SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>

//-----------------------------------KONFIGURASI UTAMA-------------------------------------------------------//
            // Konfigurasi koneksi Wifi
            
            const char* ssid = "SSID_WIFI"; 
            const char* password = "SSID_PASSWORD";
            // Akhir konfigurasi Koneksi ke Wifi
            
            //WiFiClient client;
            char server[] = "CLIENT_PC_OR_SERVER_DOMAIN";   //eg: 192.168.0.222
            
            WiFiClient client;
          
            //WiFiServer server(80);
            SoftwareSerial mySerial(8,9);     
            
//-----------------------------------KONFIGURASI VOID SETUP-------------------------------------------------------//

void setup()
{
  Serial.begin(115200);
  delay(10);
  mySerial.begin(115200);
  SPI.begin();
      
  // Menghubungkan ke Jaringan Wifi
      Serial.println();    
      Serial.print("Menghubungkan ke ");
      Serial.println(ssid);
     
    WiFi.begin(ssid, password);
    
        while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");
        }
        
      Serial.println("");
      Serial.println("WiFi connected");
 
  // Memanggil server
  // server.begin();
      
  Serial.println("STANDBY");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("READY TO SEND DATA");
 }
//-----------------------------------MEMULAI PENGIRIMAN DATA-------------------------------------------------------// 
void loop()
{  
                    // memeriksa klien jika terhubung
                    Serial.print("DATA SIAP DIKIRIM");
                    Sending_To_DB(); //PROSEDUR PENGIRIMAN
                    return; 
 }

//-----------------------------------FUNGSI PENGHUBUNG KE MYSQL-------------------------------------------------------//
 void Sending_To_DB()
 {
   if (client.connect(server, 80)) {
        Serial.println("Terhubung ke Applikasi");
        
        // Meminta protokol HTTP:
        Serial.println("GET /HOST_FOLDER/FILE.php?q=");   //YOUR URL ON PRINT SERIAL
        client.print("GET /HOST_FOLDER/FILE.php?q=");     //YOUR URL ON CLIENT COMPUTER
        
          //STATUS
            Serial.println('1'); //DATA DISPLAY AS "1"
            client.print('1'); //DATA SEND
           
                    Serial.println("TERKIRIM");
    
                     
    client.print(" ");                    //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");             //HTTP REQUEST
    client.println();                     
    client.println("Host: 192.168.0.103");//eg: 192.168.0.222
    client.println("Connection: close");
    client.println();             
    
  } else {
    // if you didn't get a connection to the server:
                Serial.println("Gagal Menghubungkan ke Server App");
                delay(500); 
  }
  client.stop();
 }

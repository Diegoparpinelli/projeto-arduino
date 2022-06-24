/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 
 */
#define en "en"
#define caminho "produto.descprod()"
#define btn "btn"
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include<IRremote.h>
String ren;
int statusLight = HIGH;
int statusAir = HIGH;
int tempAIR = 24;
IRsend irsend;
unsigned long liga, desliga, mais, menos;



// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 120);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
 pinMode(8,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(4,OUTPUT);
  
 
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

   Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

 
void loop() {
digitalWrite(8,statusLight);
delay(1);
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (ren.length() < 100) {
          ren += c;
        }
//controle da luz
         
         if (c == '\n' && currentLineIsBlank && ren.indexOf("luzon") > -1 ){
                      statusLight = LOW;

                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-Type: text/html");
                      client.println("Connection: close"); 
                      client.println("");
                      client.println("<script>console.log(\u0022LUZ ON\u0022)</script>");
            
                      break;
            }
                else if(c == '\n' && currentLineIsBlank && ren.indexOf("luzoff") > -1 ){
                      statusLight = HIGH;

                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-Type: text/html");
                      client.println("Connection: close"); 
                      client.println("");
                      client.println("<script>console.log(\u0022LUZ OFF\u0022)</script>");
              
                      break;
            }

//controle do ar
                else if (c == '\n' && currentLineIsBlank && ren.indexOf("airon") > -1 ){
                      irsend.sendRC5(liga,12);

                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-Type: text/html");
                      client.println("Connection: close"); 
                      client.println("");
                      client.println("<script>console.log(\u0022AR ON\u0022)</script>");

                      break;
            }
                else if (c == '\n' && currentLineIsBlank && ren.indexOf("airoff") > -1 ){
                      irsend.sendRC5(desliga,12);

                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-Type: text/html");
                      client.println("Connection: close"); 
                      client.println("");
                      client.println("<script>console.log(\u0022AR OFF\u0022)</script>");

                      break;       
           }


               else if (c == '\n' && currentLineIsBlank && ren.indexOf("tempup") > -1 ){
                      //alguma coisa
                      irsend.sendRC5(mais,12);
                      
                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-Type: text/html");
                      client.println("Connection: close"); 
                      client.println("");
                      client.println("<script>console.log(\u0022AR OFF\u0022)</script>");

                      break;
           }

                else if (c == '\n' && currentLineIsBlank && ren.indexOf("tempdown") > -1 ){
                      //alguma coisa
                      irsend.sendRC5(menos,12);

                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-Type: text/html");
                      client.println("Connection: close"); 
                      client.println("");
                      client.println("<script>console.log(\u0022AR OFF\u0022)</script>");

                      break;
           }


           
        
       
                else if (c == '\n' && currentLineIsBlank) {
                      //pagina principal
         
                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-Type: text/html");
                      client.println("Connection: close");
                      client.println();
                      File txt = SD.open("midex.htm");
                      if(txt){
                      while(txt.available()){
                        
                        client.write(txt.read());
                        
                        }
                      }
                      txt.close();


                      break;
            }
            
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(5);
    // close the connection:
    client.stop();
    ren = "";
    Serial.println("client disconnected");
  }

}

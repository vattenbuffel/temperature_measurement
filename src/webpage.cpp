/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/



#include <WiFi.h>
#include "webpage.h"

//#define R1 6800.0
#define R1 6000.0
#define u_in 3.3
//#define c -0.00000001794237955
#define c_val -0.00000001794237955
#define b 0.0002509871139
#define a 0.001049960637
#define read_res 11


double read_temp_main(int pin);
double calc_resistance(int pin);

// Replace with your network credentials
//const char* ssid     = "Noa 2.5 GHz";
//const char* password = "rumpnisse";
const char* ssid     = "4G-Gateway-5002";
const char* password = "Emanuelsson123";
//const char* ssid     = "Noa";
//const char* password = "hejhejhej";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;


void webpage_init(){
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void webpage_update(){
    WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Lollos temperatur</h1>");
            
            // Display current temps
            disp_temps(client);

            // If the output26State is off, it displays the ON button       
            /*if (true) {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } */
           
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void disp_temps(WiFiClient client){
  //int pins[6] = {36, 39, 34, 35, 32, 33};
  int pins[4] = {34, 35, 32, 33};

  for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++){
    double temp = read_temp(pins[i]);
    //Serial.println(read_temp(34));
    //client.println("<p>Temp " + String(i+1) + ": " + String(temp) + "</p>");
    client.println("<p>Temp " + String(pins[i]) + ": " + String(temp) + "</p>");
  }

  for (int i = 32; i < 36; i++){
    double temp = read_temp(i);
    Serial.printf("temp on pin %d : %0.4f \n", i, (double)temp);
  }
  Serial.println("");

            
}

double read_temp(int pin){
  double R = calc_resistance(pin);
  return 1/(a + b*log(R) + c_val*pow(log(R), 3)) - 273.15; // -273.15 to convert from Kelvin to Celsius
}

double calc_resistance(int pin){
  double u = analogRead(pin) * 3.3 / (pow(2, read_res) - 1);
  printf("Voltage is: %f \n", u);
  return R1*u_in/u - R1;
}

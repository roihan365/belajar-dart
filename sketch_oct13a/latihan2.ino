/
* Program : Kontrol LED via web
* Input : -
* Output : LED1
* ************* /
#include <ESP8266WiFi.h>
const char* ssid = "realme C17";
const char* password = "bannedbyme";
#define LED1 2
WiFiServer server (80);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);

  //Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() !=WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
Serial.println("");  
Serial.println("WiFi connected");
Serial.begin();
Serial.println("Server started");
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.println(WiFi.localIP());
Serial.println("/");
}
void loop(){
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
if (request.indexOf("/led1on") > 0){
  digitalWrite(LED1, LOW);
}
if (request.indexOf("/led1off") > 0){
  digitalWrite(LED1, HIGH);
}

//Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head>");
client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
client.println("</head>");
client.println("<body bgcolor = \"#f7e6ec\">");
client.println("<hr/><hr>");
client.println("<h4><center> MODUL 1 IOT POLIBAN : Kontrol LED via web </center></h4>");
client.println("<h1><center> POLIBAN </center> </h1>");
client.println("<hr/><hr>");
client.println("<br><br>");
client.println("<br><br>");
client.println("<center>");
client.println("LED 1");
client.println("<a href=\"/led1on\"\"><button>Turn On </button></a>");
client.println("<a href=\"/led1off\"\"><button>Turn Off </button></a><br/>");
client.println("</center>");
client.println("<br><br>");
client.println("<center>");
client.println("<table border=\"5\">");
client.println("<tr>");

if (digitalRead(LED1))
{
  client.print("<td> LED 1 = OFF</td>");
}
else
{
  client.print("<td> LED 1 = ON</td>");
}
  client.println("<br />");

client.println("<td>");
client.println("</tabel>");
client.println("</center>");
client.println("</html>");
delay(1);
Serial.println("Client disonnected");
Serial.println("");
}
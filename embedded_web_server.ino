#include <ESP8266WiFi.h>            
#include <ESP8266WebServer.h>


int redPin = 14;
int greenPin = 12;
int bluePin = 13;

double lampBright=1;

int redState=0;
int greenState=0;
int blueState=0;


ESP8266WebServer server(80);    //Webserver Object
String ipaddress = "";

int RH =0;
int BH =0;
int GH =0;

int RC =1;
int BC =1;
int GC =1;

bool R_On =false;
bool B_On =false;
bool G_On =false;

void setColor(int R, int G, int B)
{
  RH=R;
  GH=G;
  BH=B;
}

void updateLights(int elapsed)
{

  RC-=elapsed;
  GC-=elapsed;
  BC-=elapsed;

  if(RC<=0)
  {
    if(R_On)
    {
      R_On=false;
      if(RH!=100)
      {
        digitalWrite(redPin, HIGH);
      }
      RC=100-RH;
    }
    else
    {
      R_On=true; 
      digitalWrite(redPin, LOW);
      RC=RH;
    }
  }
  if(BC<=0)
  {
    if(B_On)
    {
      B_On=false;
      if(BH!=100)
      {
        digitalWrite(bluePin, HIGH);   
      }
      BC=100-BH;
    }
    else
    {
      B_On=true;  
      digitalWrite(bluePin, LOW);
      BC=BH;
    }
  }
  if(GC<=0)
  {
    if(G_On)
    {
      G_On=false;
      if(GH!=100)
      {
        digitalWrite(greenPin, HIGH);      
      }
      GC=100-GH;
    }
    else
    {
      G_On=true;  
      
      digitalWrite(greenPin, LOW);
      GC=GH;
    }
  }
  
}

int prevTime=0;
int curTime =0;
int state = 0;

String javascriptCode = " <!DOCTYPE html> "

"<html> "

"<style>"
"body {"
    "background-color: #abb2b5;"
"}"
"</style>"
"<body> "

"<style>"
".button {"
    "border: none;"
    "color: white;"
    "padding: 15px 32px;"
    "text-align: center;"
    "text-decoration: none;"
    "display: inline-block;"
    "font-size: 16px;"
    "margin: 8px 4px;"
    "cursor: pointer;"
    "width: 192px;"
    "height: 150px;"
"}"

".border {"
    "border-style: solid;"
    "border-color: #7d8284;"
    "margin: 4px 2px;"
    "width: 600px;"
"}"
".content {"
  "max-width: 600px;"
  "margin: auto;"
  "background: #7d8284;"
  "padding: 0px;"
"}"

".buttonOff {background-color: #3a3c3d;"
    "width: 592px;"
    "height: 100px;"
"}" 

".buttonWhite {background-color: #ffffff;"
    "width: 592px;"
    "height: 150px;"
"}"

".buttonBrightOff {background-color: #2f3133;"
    "width: 142px;"
    "height: 150px;"
"}" 
".buttonBrightLow {background-color: #5d6163;"
    "width: 142px;"
    "height: 150px;"
"}" 
".buttonBrightMid {background-color: #9ba3a5;"
    "width: 142px;"
    "height: 150px;"
"}" 
".buttonBrightHigh {background-color: #ced8db;"
    "width: 142px;"
    "height: 150px;"
"}" 
".buttonRed {background-color: #f44336;}" 
".buttonGreen {background-color: #4CAF50;}" 
".buttonBlue {background-color: #008CBA;}"
".buttonPink {background-color: #ff00ff;}"
".buttonLightGreen {background-color: #ffff00;}"
".buttonLightBlue {background-color: #00ffff;}"
".buttonOrange {background-color: #ff9000;}"
".buttonTeal {background-color: #0090ff;}"
".buttonPurple {background-color: #9000ff;}"
".buttonDarkPink {background-color: #ff0090;}"
".buttonBlueGreen {background-color: #00ff90;}"
".buttonGreenYellow {background-color: #90ff00;}"
"</style>"

"<div class=\"content\">"
"<h2>Select Light Color</h2>"
"<p>Press a color to change the lights!</p>"

"<div class=\"border\">"
"<h2>Lamp</h2>"

"<div>"
"<button class=\"button buttonGreen\" id=\"bGreen\"></button>"
"<button class=\"button buttonBlue\" id=\"bBlue\"></button>"
"<button class=\"button buttonRed\" id=\"bRed\"></button>"
"</div>"

"<div>"
"<button class=\"button buttonPink\" id=\"bPink\"></button>"
"<button class=\"button buttonLightGreen\" id=\"bLGreen\"></button>"
"<button class=\"button buttonLightBlue\" id=\"bLBlue\"></button>"
"</div>"

"<div>"
"<button class=\"button buttonDarkPink\" id=\"bDPink\"></button>"
"<button class=\"button buttonBlueGreen\" id=\"bBGreen\"></button>"
"<button class=\"button buttonGreenYellow\" id=\"bGYellow\"></button>"
"</div>"

"<div>"
"<button class=\"button buttonOrange\" id=\"bOrange\"></button>"
"<button class=\"button buttonTeal\" id=\"bTeal\"></button>"
"<button class=\"button buttonPurple\" id=\"bPurple\"></button>"
"</div>"

"<div>"
"<button class=\"button buttonWhite\" id=\"bWhite\"></button>"
"</div>"

"<div>"
"<button class=\"button buttonBrightOff\" id=\"bLamp_off\">Off</button>"
"<button class=\"button buttonBrightLow\" id=\"bLamp_low\">Low</button>"
"<button class=\"button buttonBrightMid\" id=\"bLamp_mid\">Mid</button>"
"<button class=\"button buttonBrightHigh\" id=\"bLamp_high\">High</button>"
"</div>"

"</div>"

"</div>"

"<script>"

"document.getElementById(\"bWhite\").addEventListener(\"click\", function(){"
"location.replace(\"/white\")"
"});"
"document.getElementById(\"bRed\").addEventListener(\"click\", function(){"
"location.replace(\"/red\")"
"});"
"document.getElementById(\"bBlue\").addEventListener(\"click\", function(){"
"location.replace(\"/blue\")"
"});"
"document.getElementById(\"bGreen\").addEventListener(\"click\", function(){"
"location.replace(\"/green\")"
"});"

"document.getElementById(\"bPink\").addEventListener(\"click\", function(){"
"location.replace(\"/pink\")"
"});"
"document.getElementById(\"bLGreen\").addEventListener(\"click\", function(){"
"location.replace(\"/lGreen\")"
"});"
"document.getElementById(\"bLBlue\").addEventListener(\"click\", function(){"
"location.replace(\"/lBlue\")"
"});"

"document.getElementById(\"bOrange\").addEventListener(\"click\", function(){"
"location.replace(\"/orange\")"
"});"
"document.getElementById(\"bTeal\").addEventListener(\"click\", function(){"
"location.replace(\"/teal\")"
"});"
"document.getElementById(\"bPurple\").addEventListener(\"click\", function(){"
"location.replace(\"/purple\")"
"});"

"document.getElementById(\"bDPink\").addEventListener(\"click\", function(){"
"location.replace(\"/dPink\")"
"});"
"document.getElementById(\"bBGreen\").addEventListener(\"click\", function(){"
"location.replace(\"/bGreen\")"
"});"
"document.getElementById(\"bGYellow\").addEventListener(\"click\", function(){"
"location.replace(\"/gYellow\")"
"});"

"document.getElementById(\"bLamp_off\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_off\")"
"});"
"document.getElementById(\"bLamp_low\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_low\")"
"});"
"document.getElementById(\"bLamp_mid\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_mid\")"
"});"
"document.getElementById(\"bLamp_high\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_high\")"
"});"


"</script>"

"</body> "

"</html> ";


void setup() {

pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);  

prevTime=micros()/100;

Serial.begin(115200);                                             //Open Serial connection

WiFi.begin("Light-WiFi", "MorganBrown1234");
IPAddress ip(192,168,0,123);   
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0);   
WiFi.config(ip, gateway, subnet);  

//IPAddress ip(10,0,0,123);   
//IPAddress gateway(10,0,0,1);   
//IPAddress subnet(255,0,0,0);   
//WiFi.config(ip, gateway, subnet);                    

while (WiFi.status() != WL_CONNECTED) {    //Wait for connection

delay(500);
Serial.println("Waiting to connect…");

}

Serial.print("IP address: ");
ipaddress = WiFi.localIP().toString();
Serial.println(ipaddress);  //Print the local IP

server.on("/", []() {                     //Define the handling function for root path (HTML message)
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=0;
blueState=0;
lampBright=0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/red", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=0;
blueState=0;
lampBright=1;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/blue", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=0;
blueState=100;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/green", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=100;
blueState=0;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/lGreen", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=100;
blueState=0;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/lBlue", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=100;
blueState=100;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/pink", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=0;
blueState=100;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/orange", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=50;
blueState=0;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/teal", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=50;
blueState=100;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/purple", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=50;
greenState=0;
blueState=100;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/dPink", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=0;
blueState=50;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/bGreen", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=100;
blueState=50;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/gYellow", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=50;
greenState=100;
blueState=0;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/white", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=100;
blueState=100;
lampBright=1;

setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});


server.on("/lamp_off", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = 0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});
server.on("/lamp_low", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = .3;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});
server.on("/lamp_mid", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = .6;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});
server.on("/lamp_high", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = 1;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

lampBright=0;
server.begin(); //Start the server

Serial.println("Server listening");
lampBright=0;
}

void loop() {
  
  curTime=micros()/100;
  updateLights(curTime-prevTime);
  server.handleClient(); //Handling of incoming requests

  prevTime=curTime;
}

#include <ESP8266WiFi.h>            
#include <ESP8266WebServer.h>

int auxPin1 = 4;
int auxPin2 = 5;

int redPin = 14;
int greenPin = 12;
int bluePin = 13;

double lampBright=1;
double aux1Bright=1;
double aux2Bright=1;

int redState=0;
int greenState=0;
int blueState=0;
int aux1State=0;
int aux2State=0;

ESP8266WebServer server(80);    //Webserver Object
String ipaddress = "";

int RH =0;
int BH =0;
int GH =0;
int Aux1H =0;
int Aux2H =0;

int RC =1;
int BC =1;
int GC =1;
int Aux1C =1;
int Aux2C =1;

bool R_On =false;
bool B_On =false;
bool G_On =false;
bool Aux1_On =false;
bool Aux2_On =false;

void setColor(int R, int G, int B)
{
  RH=R;
  GH=G;
  BH=B;
}
void setAux(int aux1, int aux2)
{
  Aux1H=aux1;
  Aux2H=aux2;
}

void updateLights(int elapsed)
{

  RC-=elapsed;
  GC-=elapsed;
  BC-=elapsed;
  Aux1C-=elapsed;
  Aux2C-=elapsed;
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
  if(Aux1C<=0)
  {
    if(Aux1_On)
    {
      Aux1_On=false;
      if(Aux1H!=100)
      {
        digitalWrite(auxPin1, HIGH);      
      }
      Aux1C=100-Aux1H;
    }
    else
    {
      Aux1_On=true;  
      digitalWrite(auxPin1, LOW);      
      Aux1C=Aux1H;
    }
  }
  if(Aux2C<=0)
  {
    if(Aux2_On)
    {
      Aux2_On=false;
      if(Aux2H!=100)
      {
        digitalWrite(auxPin2, HIGH);      
      }
      Aux2C=100-Aux2H;
    }
    else
    {
      Aux2_On=true;  
      digitalWrite(auxPin2, LOW);      
      Aux2C=Aux2H;
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

".buttonOff {background-color: #3a3c3d;"
    "width: 592px;"
    "height: 100px;"
"}" 

".buttonWhite {background-color: #ffffff;"
    "width: 592px;"
    "height: 100px;"
"}"

".buttonBrightControl {background-color: #ced8db;"
    "width: 92px;"
    "height: 92px;"
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

"<h2>Select Light Color</h2>"
"<p>Press a color to change the lights!</p>"

"<div class=\"border\">"
"<button class=\"button buttonOff\" id=\"bOff\">Off</button>"
"</div>"

"<div class=\"border\">"
"<h2>Aux 1</h2>"
"<button class=\"button buttonBrightControl\" id=\"bAux1_0\">0%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux1_20\">20%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux1_40\">40%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux1_60\">60%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux1_80\">80%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux1_100\">100%</button>"
"</div>"

"<div class=\"border\">"
"<h2>Aux 2</h2>"
"<button class=\"button buttonBrightControl\" id=\"bAux2_0\">0%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux2_20\">20%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux2_40\">40%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux2_60\">60%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux2_80\">80%</button>"
"<button class=\"button buttonBrightControl\" id=\"bAux2_100\">100%</button>"
"</div>"

"<div class=\"border\">"
"<h2>Lamp</h2>"

"<div>"
"<button class=\"button buttonBrightControl\" id=\"bLamp_0\">0%</button>"
"<button class=\"button buttonBrightControl\" id=\"bLamp_20\">20%</button>"
"<button class=\"button buttonBrightControl\" id=\"bLamp_40\">40%</button>"
"<button class=\"button buttonBrightControl\" id=\"bLamp_60\">60%</button>"
"<button class=\"button buttonBrightControl\" id=\"bLamp_80\">80%</button>"
"<button class=\"button buttonBrightControl\" id=\"bLamp_100\">100%</button>"
"</div>"

"<div>"
"<button class=\"button buttonWhite\" id=\"bWhite\"></button>"
"</div>"

"<div>"
"<button class=\"button buttonGreen\" id=\"bGreen\">Green</button>"
"<button class=\"button buttonBlue\" id=\"bBlue\">Blue</button>"
"<button class=\"button buttonRed\" id=\"bRed\">Red</button>"
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

"</div>"

"<script>"
"document.getElementById(\"bOff\").addEventListener(\"click\", function(){"
"location.replace(\"/\")"
"});"
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

"document.getElementById(\"bAux1_0\").addEventListener(\"click\", function(){"
"location.replace(\"/aux1_0\")"
"});"
"document.getElementById(\"bAux1_20\").addEventListener(\"click\", function(){"
"location.replace(\"/aux1_20\")"
"});"
"document.getElementById(\"bAux1_40\").addEventListener(\"click\", function(){"
"location.replace(\"/aux1_40\")"
"});"
"document.getElementById(\"bAux1_60\").addEventListener(\"click\", function(){"
"location.replace(\"/aux1_60\")"
"});"
"document.getElementById(\"bAux1_80\").addEventListener(\"click\", function(){"
"location.replace(\"/aux1_80\")"
"});"
"document.getElementById(\"bAux1_100\").addEventListener(\"click\", function(){"
"location.replace(\"/aux1_100\")"
"});"

"document.getElementById(\"bAux2_0\").addEventListener(\"click\", function(){"
"location.replace(\"/aux2_0\")"
"});"
"document.getElementById(\"bAux2_20\").addEventListener(\"click\", function(){"
"location.replace(\"/aux2_20\")"
"});"
"document.getElementById(\"bAux2_40\").addEventListener(\"click\", function(){"
"location.replace(\"/aux2_40\")"
"});"
"document.getElementById(\"bAux2_60\").addEventListener(\"click\", function(){"
"location.replace(\"/aux2_60\")"
"});"
"document.getElementById(\"bAux2_80\").addEventListener(\"click\", function(){"
"location.replace(\"/aux2_80\")"
"});"
"document.getElementById(\"bAux2_100\").addEventListener(\"click\", function(){"
"location.replace(\"/aux2_100\")"
"});"

"document.getElementById(\"bLamp_0\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_0\")"
"});"
"document.getElementById(\"bLamp_20\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_20\")"
"});"
"document.getElementById(\"bLamp_40\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_40\")"
"});"
"document.getElementById(\"bLamp_60\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_60\")"
"});"
"document.getElementById(\"bLamp_80\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_80\")"
"});"
"document.getElementById(\"bLamp_100\").addEventListener(\"click\", function(){"
"location.replace(\"/lamp_100\")"
"});"

"</script>"

"</body> "

"</html> ";


void setup() {

pinMode(auxPin1, OUTPUT);
pinMode(auxPin2, OUTPUT);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);  

prevTime=micros()/100;

Serial.begin(115200);                                             //Open Serial connection

WiFi.begin("Uncle Rick", "Hollywood_Jack");                          //Connect to the WiFi network

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
aux1State=0;
aux2State=0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});

server.on("/red", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=0;
blueState=0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/blue", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=0;
blueState=100;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/green", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=100;
blueState=0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/lGreen", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=100;
blueState=0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/lBlue", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=100;
blueState=100;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/pink", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=0;
blueState=100;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/orange", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=50;
blueState=0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/teal", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=50;
blueState=100;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/purple", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=50;
greenState=0;
blueState=100;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/dPink", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=0;
blueState=50;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/bGreen", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=0;
greenState=100;
blueState=50;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/gYellow", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=50;
greenState=100;
blueState=0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/white", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
redState=100;
greenState=100;
blueState=100;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});

server.on("/aux1_0", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux1State=100;
aux1Bright=0;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux1_20", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux1State=100;
aux1Bright=.2;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux1_40", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux1State=100;
aux1Bright=.4;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux1_60", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux1State=100;
aux1Bright=.6;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux1_80", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux1State=100;
aux1Bright=.8;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux1_100", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux1State=100;
aux1Bright=1;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});

server.on("/aux2_0", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux2State=100;
aux2Bright=0;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux2_20", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux2State=100;
aux2Bright=.2;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux2_40", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux2State=100;
aux2Bright=.4;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux2_60", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux2State=100;
aux2Bright=.6;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux2_80", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux2State=100;
aux2Bright=.8;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});
server.on("/aux2_100", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
aux2State=100;
aux2Bright=1;
setAux(100-(aux1State*aux1Bright),100-(aux2State*aux2Bright));
});

server.on("/lamp_0", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = 0;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});
server.on("/lamp_20", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = .2;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});
server.on("/lamp_40", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = .4;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});
server.on("/lamp_60", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = .6;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});
server.on("/lamp_80", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = .8;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});
server.on("/lamp_100", []() { //Define the handling function for the javascript path
server.send(200, "text/html", javascriptCode);
lampBright = 1;
setColor(100-(redState*lampBright),100-(greenState*lampBright),100-(blueState*lampBright));
});



server.begin(); //Start the server

Serial.println("Server listening");

}

void loop() {
  
  curTime=micros()/100;
  updateLights(curTime-prevTime);
  server.handleClient(); //Handling of incoming requests

  prevTime=curTime;
}

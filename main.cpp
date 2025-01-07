// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "ESP8266";
const char* password = "ebusch";

const char* PARAM_INPUT_1 = "state";

const int output = 2;
const int buttonPin = 4;

// Variables will change:
int ledState = LOW;          // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
  <head lang="en"> <title>Elijah's Website</title> <meta name="viewport" content="width=device-width, height=device-height, initial-scale=1.0" charset="UTF-8"> <link rel="icon" href="https://cdn4.iconfinder.com/data/icons/whsr-january-flaticon-set/512/servers.png" type="image/x-icon"/> <link href="style.css" type="text/css" rel="stylesheet"> <link href="https://github.com/ebusch8/Elijahs-Website/blob/56b1768799baf61017a97443129c87f3caef7e42/style.css" type="text/css" rel="stylesheet"> <script src="script.js"></script> <script src="https://github.com/ebusch8/Elijahs-Website/blob/56b1768799baf61017a97443129c87f3caef7e42/script.js"></script> </head> <body> <a href="https://sites.google.com/cps.edu/elijahs-website/home">My Google Sites Website</a> <a href="https://eaglercraft.com/mc/1.8.8-wasm/">Eaglercraft</a> <button href="index-v1.html">My Website V1</button> <button onclick="welcome()">Welcome message</button> <button onclick="getLocation()">Location Test</button> <button type="button" class="collapsible">The absolutely true diary of a part time indian</button> <div class="content"> <p>Chapter 26</p> <iframe width="560" height="315" src="https://www.youtube.com/embed/WxqLi1XZxPQ?si=eH-jjyJM6Ongwwzw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen>Chapter 26</iframe> <p>Chapter 27</p> <video controls href=''>Chapter 27</video> <p>Chapter 28</p> <iframe width="560" height="315" src="https://www.youtube.com/embed/vP4g5qpYoV8?si=ZSDhCSd0tYzxSJph" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen>Chapter 28</iframe> <p>Chapter 29</p> <iframe width="560" height="315" src="https://www.youtube.com/embed/wYZ1_99nmAs?si=gFVgOBtAZkzPVPMX" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen>Chapter 29</iframe> <p>Chapter 30</p> <iframe width="560" height="315" src="https://www.youtube.com/embed/YzsKB6ggqgc?si=M4UMFIdQZNBem6LU" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen>Chapter 30</iframe> </div> <div id="Main"> <h1>ESP8266 Web Server</h1> <h2>About me</h2> <p>I am a 12 year old boy who enjoys programming, electronics, and occasionally enjoy Video games. </p> <p>And guess what? I'm learning to code!</p> <p>I am hoping to start running this on my esp8266.</p> <p>Does anyone else think goguardian is annoying?</p> <meta charset="utf-8"><b style="font-weight:normal;" id="docs-internal-guid-78206dbe-7fff-bfd4-c91e-44d2a881f2fe"><img width="263px;" height="175px;" src="https://lh7-rt.googleusercontent.com/slidesz/AGV_vUcYolJaI9rd7AoImYeOxwTtjE8yQI-eZ1nL4YtPINjqWdDa8G4O0Zzd20fsYmSoyUUyYDGaAm_P9m8OLik0RtgaRBULCvbDY7NsnRReBpFR0NDZfXt1WeB4s-cF6TOWlkt42KELEg=s2048?key=1UacCEU8L3p2GiBFrahHrhGt" /></b> </div> <script type="text/c#"> System.string foo = "This was printed using C#!"; public void Check(string username, string pass) { } </script> <h1>Hello world!</h1> <p>These are the Python interpreters in PyScript _VERSION_:</p> <script type="py"> <!-- Pyodide --> from pyscript import display import sys display(sys.version) </script> <script type="mpy"> <!-- MicroPython --> from pyscript import display import sys display(sys.version) </script> <?PHP echo "This was printed using PHP!"; ?> <?PHP echo shell_exec("python test.py 'parameter1'"); ?> <h1>My VR Escape Room (works with any viewer)</h1> <embed type="text/html" src="https://vr-escaperoom-by-elijah.glitch.me/" width="500" height="200"> <div class="keys"> <div data-key="65" class="key"> <kbd>A</kbd> <span class="sound">clap</span> </div> <div data-key="83" class="key"> <kbd>S</kbd> <span class="sound">hihat</span> </div> <div data-key="68" class="key"> <kbd>D</kbd> <span class="sound">kick</span> </div> <div data-key="70" class="key"> <kbd>F</kbd> <span class="sound">openhat</span> </div> <div data-key="71" class="key"> <kbd>G</kbd> <span class="sound">boom</span> </div> <div data-key="72" class="key"> <kbd>H</kbd> <span class="sound">ride</span> </div> <div data-key="74" class="key"> <kbd>J</kbd> <span class="sound">snare</span> </div> <div data-key="75" class="key"> <kbd>K</kbd> <span class="sound">tom</span> </div> <div data-key="76" class="key"> <kbd>L</kbd> <span class="sound">tink</span> </div> </div> <audio data-key="65" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/clap.wav"></audio> <audio data-key="83" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/hihat.wav"></audio> <audio data-key="68" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/kick.wav"></audio> <audio data-key="70" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/openhat.wav"></audio> <audio data-key="71" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/boom.wav"></audio> <audio data-key="72" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/ride.wav"></audio> <audio data-key="74" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/snare.wav"></audio> <audio data-key="75" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/tom.wav"></audio> <audio data-key="76" src="file:///media/fuse/drivefs-5fc36cdec9b55a8aba5617de4626951f/root/Coding/My%20website/Sounds/tink.wav"></audio> </body>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons ="";
    String outputStateValue = outputState();
    buttons+= "<h4>Output - GPIO 2 - State <span id=\"outputState\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}

String outputState(){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
  return "";
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(output, OUTPUT);
  digitalWrite(output, LOW);
  pinMode(buttonPin, INPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?state=<inputMessage>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/update?state=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      digitalWrite(output, inputMessage.toInt());
      ledState = !ledState;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

  // Send a GET request to <ESP_IP>/state
  server.on("/state", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(digitalRead(output)).c_str());
  });
  // Start server
  server.begin();
}
  
void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(output, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

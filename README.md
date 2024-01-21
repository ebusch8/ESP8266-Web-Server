# ESP Web Server with Toggle Switch

This repository contains Arduino code for a simple web server running on an ESP8266/ESP32 microcontroller. The web server allows you to control the state of a digital output pin (connected to an LED or any other device) using a toggle switch on a web page.

## Getting Started

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- [ESPAsyncWebServer library](https://github.com/me-no-dev/ESPAsyncWebServer)

### Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/your-username/esp-web-server.git
   ```

2. Open the Arduino IDE.

3. Install the required libraries:
   - ESPAsyncWebServer: In the Arduino IDE, go to Sketch > Include Library > Manage Libraries, search for "ESPAsyncWebServer" and install it.

4. Connect your ESP8266/ESP32 to your computer.

5. Open the `esp-web-server.ino` file in the Arduino IDE.

6. Replace the following placeholder values in the code:
   - `Network_name` and `Newtor_password` with your WiFi network credentials.

7. Upload the code to your ESP8266/ESP32.

8. Open the Serial Monitor (Tools > Serial Monitor) to view the ESP's IP address once connected to the WiFi network.

9. Open a web browser and navigate to the provided IP address. You should see a web page with a toggle switch to control the connected device.

## Usage

- The main web page allows you to toggle the state of the connected device using a switch.
- The state of the connected device is updated in real-time on the web page.
- You can also check the current state of the device by sending a GET request to `/state`.

## Customization

Feel free to customize the HTML, CSS, and JavaScript in the `index_html` variable to match your specific requirements.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

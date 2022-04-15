/*
  Title:      FurbyHack
  
  Author:     Constantin Scholz IMEC & VUB BruBotics
  
  Email:      constantin.scholz@imec.be | constantin.florian.scholz@vub.be
  
  Code 
  Purpose:    This code allows to hack into a Furby Connect Bluetooth Low Energy and control its behaviour. 
  
  References: The code is inspired by the GitHub repository BlueFluff: https://github.com/Jeija/bluefluff also 
              I am using the Arduino Bluetooth Low Energy Library: https://github.com/arduino-libraries/ArduinoBLE
              
  Liscence:   MIT © Constantin Scholz
              THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
              INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
              PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
              DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
              OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 Hardware:    ARDUINO UNO WiFi REV2 -> http://store.arduino.cc/products/arduino-uno-wifi-rev2
              Furby Connect BLE -> https://furby.hasbro.com/en-us            
*/

//Library Includes:
#include <ArduinoBLE.h>

//Convenience Variables: 
char COMMAND = 'o';

// Byte arrays to trigger specific Furby behaviour via BLE.
// Full list of actions can be found here -> https://github.com/Jeija/bluefluff/blob/master/doc/generalplus.md and https://github.com/Jeija/bluefluff/blob/master/doc/actionlist.md
// Important: When reading the action list and making your byte array below ensure you calculate dec -> hex
// Let's look at an example: To trigger a specific action we need to send a command with the following structure -> 0x13:0x00:Input:Index:Subindex:Specific
// Let's say I want to make Furby say "yippie! -> From the action list we see that Input: 18 Index: 0 Subindex: 1 Specific: 4
// Build the hex array for the action and calculate dec to hex. See below

// Actions definitions
byte yippieAction[6] = {0x13,0x00,0x12,0x00,0x01,0x04};
byte breakfastAction[6] = {0x13,0x00,0x17,0x01,0x00,0x01};
byte earsUp[6] = {0x13,0x00,0x37,0x02,0x11,0x00};
//ADD whatever you want -> https://github.com/Jeija/bluefluff/blob/master/doc/actionlist.md

// Keep furby quiet:
byte keepQuiet[6] = {0x00,0x00,0x00,0x00,0x00,0x00};

// Antenna colours Last three bytes RGB in DEC 0-255> HEX 0x00-0xFF
byte AntennaBlue[4] = {0x14,0x00,0x00,0xFF};
byte AntennaRED[4] = {0x14,0xFF,0x00,0x00};

//Open up serial connection and start bluetooth BLE
void setup() {
  //
  Serial.begin(9600);
  while (!Serial);

  // Start up Bluetooth Low Energy 
  if (!BLE.begin()) {
    Serial.println("Could not start up Bluetooth Low Energy");
    while (1);
  }

  Serial.println("Started Blutooth, Let's find Furby... ");
  Serial.println("Make sure to turn on the Furby");

  // start scanning for Bluetooth low energy peripherals around
  BLE.scan();
}

void loop() {
  // Query for a discovered BLE device that was found during scanning.
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // convenience print out to see peripherals dicovered
    Serial.print("Discovered the following peripherals ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();

    // Once a Furby has been discovered with the Service UUID -> dab91435-b5a1-e29c-b041-bcd562613bde stop the scan for other peripherals
    if (peripheral.advertisedServiceUuid() == "dab91435-b5a1-e29c-b041-bcd562613bde") {
      // stop scanning
      BLE.stopScan();

      furbyIAmYourMasterThisIsMyCommand(peripheral);

      // peripheral disconnected, start scanning again
      BLE.scan();
    }
  }
}

void furbyIAmYourMasterThisIsMyCommand(BLEDevice peripheral) {
  // connect to the Furby
  Serial.println("Connecting to Furby ");
  if (peripheral.connect()) {
    Serial.println("Connected to Furby");
  } else {
    Serial.println("Failed to connect to Furby!");
    Serial.println("It could help to remove the Furby Batteries");
    return;
  }

  // Discover peripheral attributes of the Service
  Serial.println("Let's find the GeneralPlusWrite Characteristic: dab91435-b5a1-e29c-b041-bcd562613bde");
  if (peripheral.discoverService("dab91435-b5a1-e29c-b041-bcd562613bde")) {
    Serial.println("GeneralPlusWrite discovered");
  } else {
    Serial.println("GeneralPlusWrite discovery failed.");
    peripheral.disconnect();

    while (1);
    return;
  }

  // subscribe to the simple key characteristic
  BLECharacteristic FurbyGeneralPlusWriteCharacteristic = peripheral.characteristic("dab91383-b5a1-e29c-b041-bcd562613bde");

  Serial.println("Subscribing to Furby GeneralPlusWrite characteristic ...");
  if (!FurbyGeneralPlusWriteCharacteristic) {
    Serial.println("no GeneralPlusWrite characteristic found!");
    peripheral.disconnect();
    return;
    
  } else if (!FurbyGeneralPlusWriteCharacteristic.canWrite()) {
    Serial.println("GeneralPlusWrite characteristic is not writable!");
    peripheral.disconnect();
    return;
    
  } else {
    Serial.println("Hacked, we are connected to your soul Furby");
  }

  while (peripheral.connected()) {

    if(Serial.available() > 0){
      
      COMMAND = Serial.read();  
    }
// Commands to trigger actions
    switch(COMMAND) {
      case 'b':
        Serial.println("BReakfast");
        FurbyGeneralPlusWriteCharacteristic.writeValue(breakfastAction,6);
        COMMAND = 'o';
        break;

      case 'e':
        Serial.println("Ears Up");
        FurbyGeneralPlusWriteCharacteristic.writeValue(earsUp,6);
        COMMAND = 'o';
        break;
        
      case 'y':
        Serial.println("Yippie");
        FurbyGeneralPlusWriteCharacteristic.writeValue(yippieAction,6);
        COMMAND = 'o';
        break;

     case 'a':
        Serial.println("Antenna Blue");
        FurbyGeneralPlusWriteCharacteristic.writeValue(AntennaBlue,6);
        COMMAND = 'o';
        break;

      case 'd':
        Serial.println("Furby characteristic disconnected!");
        peripheral.disconnect();
        COMMAND = 'o';
        return;
        break;

     case 'o':
        FurbyGeneralPlusWriteCharacteristic.writeValue(keepQuiet,6);
        break;
        
      default:
        COMMAND = 'o';
    }

  }

  Serial.println("Furby disconnected!");
}

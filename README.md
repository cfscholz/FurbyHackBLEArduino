# FurbyHackBLEAaduino
```
███████╗██╗░░░██╗██████╗░██████╗░██╗░░░██╗  ██╗░░██╗░█████╗░░█████╗░██╗░░██╗  ██████╗░██╗░░░░░███████╗
██╔════╝██║░░░██║██╔══██╗██╔══██╗╚██╗░██╔╝  ██║░░██║██╔══██╗██╔══██╗██║░██╔╝  ██╔══██╗██║░░░░░██╔════╝
█████╗░░██║░░░██║██████╔╝██████╦╝░╚████╔╝░  ███████║███████║██║░░╚═╝█████═╝░  ██████╦╝██║░░░░░█████╗░░
██╔══╝░░██║░░░██║██╔══██╗██╔══██╗░░╚██╔╝░░  ██╔══██║██╔══██║██║░░██╗██╔═██╗░  ██╔══██╗██║░░░░░██╔══╝░░
██║░░░░░╚██████╔╝██║░░██║██████╦╝░░░██║░░░  ██║░░██║██║░░██║╚█████╔╝██║░╚██╗  ██████╦╝███████╗███████╗
╚═╝░░░░░░╚═════╝░╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░  ╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝  ╚═════╝░╚══════╝╚══════╝

░█████╗░██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗░█████╗░
██╔══██╗██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██╔══██╗
███████║██████╔╝██║░░██║██║░░░██║██║██╔██╗██║██║░░██║
██╔══██║██╔══██╗██║░░██║██║░░░██║██║██║╚████║██║░░██║
██║░░██║██║░░██║██████╔╝╚██████╔╝██║██║░╚███║╚█████╔╝
╚═╝░░╚═╝╚═╝░░╚═╝╚═════╝░░╚═════╝░╚═╝╚═╝░░╚══╝░╚════╝░                                                                                          
```
------------------------------------------------------- 

#This repository allows you to control a Furby Connect BLE with an Arduino Uno Wifi 2

  **Title**:      FurbyHack
  
  **Author**:     Constantin Scholz IMEC & VUB BruBotics
  
  **Email**:      constantin.scholz@imec.be | constantin.florian.scholz@vub.be
  
  **Code 
  Purpose**:    This code allows to hack into a Furby Connect Bluetooth Low Energy and control its behaviour. 
  
  **References**: The code is inspired by the GitHub repository [BlueFluff](https://github.com/Jeija/bluefluff)  also 
              I am using the [Arduino Bluetooth Low Energy Library](https://github.com/arduino-libraries/ArduinoBLE)
              
  **Liscence**:   MIT © Constantin Scholz
              THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
              INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
              PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
              DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
              OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 **Hardware**:    [ARDUINO UNO WiFi REV2](http://store.arduino.cc/products/arduino-uno-wifi-rev2)
              [Furby Connect BLE](https://furby.hasbro.com/en-us) 
              
              
 -------------------
 
#  Getting started: 
1. Install the [Arduino IDE](https://www.arduino.cc/en/software). 
2. Connect to your ARDUINO UNO WiFi REV2 board. Upload the [FurbyHackCode](../FurbyHackCode/FurbyHackCode.ino) script to the Arduino.
3. Open the serial monitor of the Arduino IDE.
4. Power on the Furby. 
5. The code will automatically stay connected with the Furby and ensures it stays quiet.
6. You can now send commands to the Furby. Sending the character 'b' will change the antenna to blue.
7. If you want to disconnect to the Furby send the character 'd'.
              
 -------------------
 
 #  Example Video
 I am demonstrating how to run a few action commands, change the antenna colour and also disconnect from the Furby. See the video below.
 [DEMO1](https://user-images.githubusercontent.com/102663526/163571439-bf7a826e-5fbd-4e12-882c-3567c12152d6.mov)
 


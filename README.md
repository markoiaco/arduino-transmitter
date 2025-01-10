# arduino-transmitter
DISCLAIMER
I developed this project about 7 years ago, when I was in the 3rd year of high school.
I know the code is poorly written and won't be perfect, I was 16 and I wanted to share it with you so I hope you appreciate it anyway :)


It is a controller made to manage a 4 output 220v - 230v relay over 900mt distance.
- In this repo you will find two source file, one must be flashed on the first module TRANSMITTER and the second one on the RECEIVER. -

## Transmitter ##
Which connects to the home internet network and creates a web server with a basic interface to control the outputs.
Made of:
 - arduino uno
 - ethernet shield
 - HC12 transmitter 443 Mhz

## Receiver ##
The second module 
 - arduino nano 
 - hc12 443Mhz
 - 4 output relay 220-230v

## The working scheme I developed some time ago is the following: ##

- Transmitter module receives inputs from the webserver and transmits a signal (string) with the HC12 at 443Mhz at a max distance of 1km (also depends on the quality of the product manufacturer)

- Receiver module captures the signal received remotely with the second HC12 443Mhz set as listener.
  And based on the string received, the output for the relay to be turned on/off is decoded and managed


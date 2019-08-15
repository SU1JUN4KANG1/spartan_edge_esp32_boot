## spartan_edge_esp32_boot a Library for Spartan Edge Accelerator Board  
The purpose of this article is to show how to load FPGA LOGIC to Spartan Edge Accelerator Board by arduino IDE  

## Contents
- [Spartan Edge Accelerator Board description](#Spartan-Edge-Accelerator-Board-description)
- [Installation instructions](#Installation-instructions)
- [Library instructions](#Library-instructions)
- [other Libraries](#other-Libraries)

## Spartan Edge Accelerator Board description
It can be used independently as an Arduino compatible board, or plugged into an Arduino as an auxiliary accelerator board.  
(picture)  

## Installation instructions 
___using Arduino IDE Boards Manager___  
Starting with 1.6.4, Arduino allows installation of third-party platform packages using Boards Manager. We have packages available for Windows, Mac OS, and Linux (32 and 64 bit).

- Install the current upstream Arduino IDE at the 1.8 level or later. The current version is at the [Arduino website](http://www.arduino.cc/en/main/software).
- Start Arduino and open Preferences window.
- Enter ```https://dl.espressif.com/dl/package_esp32_index.json``` into *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install *esp32* platform (and don't forget to select your ESP32 board from Tools > Board menu after installation).
- select ___tool->board->DOIT ESP32 DEVKIT___   
Stable release link: `https://dl.espressif.com/dl/package_esp32_index.json`

Development release link: `https://dl.espressif.com/dl/package_esp32_dev_index.json`
If you want more details ,you can click the [link](https://github.com/espressif/arduino-esp32)

## Library instructions  
#### - FPGA LOGIC  
We provide some FPGA_LOGIC files to load.you can dowmload them in dir ___overlay___  
	+ #### color_detect.bit  
	To detect color blocks, RPi MIPI camera v1.3 version is required.  
	+ #### hdmi_v1.bit  
	Displays moving color stripes on HDMI  
	+ #### mipi_camera.bit  
	The RPi MIPI camera v1.3 is required to capture images and display them on the HDMI display.  
	+ #### spi2gpio.bit  
	SPI interface GPIO extension logic, which supporting the operation of ADC/DAC/ rgb-led.  

- #### example Instructions  
if you want to use this example, you should copy the dir ___overay___ to your SDcard rootdir.  
And copy this Repository to ___arduino/libraries___.  
	+ 01LoadDefaultBitstream  
	this example will load the spi2gpio.bit as FPGA LOGIC  
	+ 02LoadConfigBitstream  
	this example will read a ___ini___ format file, getting the value of overlay_on_boot,and ESP32 will load the FPGA LOGIC.  
	you can get the ___inifile___ from this example

## other Libraries
+ ### Library __spartan_edge_ioex__ (loading spi2gpio.bit)
if you loading spi2gpio.bit, this library makes it easier for you to control spartan-edge-accelerator board
if you want to use it, you can click this [link](https://github.com/SU1JUN4KANG1/spartan_edge_ioex)




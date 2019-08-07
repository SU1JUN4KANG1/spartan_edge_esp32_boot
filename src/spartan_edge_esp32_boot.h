/*
 * spartan_edge_esp32_boot.h - for spartan_edge board
 * 
 */
 
// ensure this library description is only included once
#ifndef SPARTAN_EDGE_ESP32_BOOT_H
#define SPARTAN_EDGE_ESP32_BOOT_H 
 
#include <sd_defines.h>
#include <Arduino.h>
#include "FS.h"
#include "SD_MMC.h"
#include "IniFile.h"

/* pin define */
#define XFPGA_CCLK_PIN 17
#define XFPGA_DIN_PIN 27
#define XFPGA_PROGRAM_PIN 25
#define XFPGA_INTB_PIN 26
#define XFPGA_DONE_PIN 34
 
// the sizes about one time reading
// If this value is too high, which will result result in failure
#define READ_SIZE 256

class spartan_edge_esp32_boot {
  public:
	// initialization
    void begin(void);
	
	// loading bitstream
    void xfpgaGPIOInit(void);
    int xlibsSstream(const char* path);
	
	// SD_MMC directory control 
	void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
	void createDir(fs::FS &fs, const char * path);
	void removeDir(fs::FS &fs, const char * path);
	
	// SD_MMC file control 
	void readFile(fs::FS &fs, const char * path);
	void writeFile(fs::FS &fs, const char * path, const char * message);
	void appendFile(fs::FS &fs, const char * path, const char * message);
	void renameFile(fs::FS &fs, const char * path1, const char * path2);
	void deleteFile(fs::FS &fs, const char * path);
  private:  
};

 #endif

 
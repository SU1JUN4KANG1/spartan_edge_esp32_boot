/*
 * 04SDControl
 * 
 * control the SDCard,
 * read/write/rename/append/delete file
 * list/creat/remove directory
 * 
 * The MIT License (MIT)
 * Copyright (C) 2019  Seeed Technology Co.,Ltd.
 */

// include the library:
#include <spartan_edge_esp32_boot.h>

// initialize the spartan_edge_esp32_boot library
spartan_edge_esp32_boot esp32Cla;

// the setup routine runs once when you press reset:
void setup() {
  // initialization 
  esp32Cla.begin();  

  // Mount SD Card
  if(!SD_MMC.begin()){
    Serial.println("Card Mount Failed,please reboot the board");
    return;
  }

  // output the SDCard size
  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

  esp32Cla.listDir(SD_MMC, "/", 0);
  esp32Cla.createDir(SD_MMC, "/mydir");
  esp32Cla.listDir(SD_MMC, "/", 0);
  esp32Cla.removeDir(SD_MMC, "/mydir");
  esp32Cla.listDir(SD_MMC, "/", 2);
  esp32Cla.writeFile(SD_MMC, "/hello.txt", "Hello ");
  esp32Cla.appendFile(SD_MMC, "/hello.txt", "World!\n");
  esp32Cla.readFile(SD_MMC, "/hello.txt");
  esp32Cla.deleteFile(SD_MMC, "/foo.txt");
  esp32Cla.renameFile(SD_MMC, "/hello.txt", "/foo.txt");
  esp32Cla.readFile(SD_MMC, "/foo.txt");
}

// the loop routine runs over and over again forever:
void loop() {
  // nothink to do
}

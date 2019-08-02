/*
 * 02DynamicLoadBitstream
 *  
 * loading the Bitstream dynamicly
 *
 * The MIT License (MIT)
 * Copyright (C) 2019  Seeed Technology Co.,Ltd.
 */

// include the library:
#include <spartan_edge_esp32_boot.h>

// initialize the spartan_edge_esp32_boot library
spartan_edge_esp32_boot esp32Cla;

void setup() {
  // Sent Serial Configuration Data
  if(!SD_MMC.begin()) {
    Serial.println("Card Mount Failed");
    return;
    }
}

// the loop routine runs over and over again forever:
void loop() {

  Serial.println("run");
  delay(3000);
}

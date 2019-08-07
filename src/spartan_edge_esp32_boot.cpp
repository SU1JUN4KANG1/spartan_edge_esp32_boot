#include <spartan_edge_esp32_boot.h>

// initialization
void spartan_edge_esp32_boot::begin(void) {
  // initialize serial communication at 115200 bits per second: 
  Serial.begin(115200); 
}

// XFPGA pin Initialize
void spartan_edge_esp32_boot::xfpgaGPIOInit(void) {
  // GPIO Initialize
  pinMode(XFPGA_INTB_PIN, OUTPUT | PULLUP);
  digitalWrite(XFPGA_INTB_PIN, HIGH);
  pinMode(XFPGA_PROGRAM_PIN, OUTPUT);
  digitalWrite(XFPGA_PROGRAM_PIN, HIGH);
  delay(50);

  // FPGA configuration start sign
  digitalWrite(XFPGA_INTB_PIN, LOW);
  digitalWrite(XFPGA_PROGRAM_PIN, LOW);
  delay(50);
  digitalWrite(XFPGA_INTB_PIN, HIGH);
  digitalWrite(XFPGA_PROGRAM_PIN, HIGH);
}


int spartan_edge_esp32_boot::xlibsSstream(const char* path) {
  unsigned char byte_buff[1024];
  int byte_len;
  unsigned char byte;
  int i = 0;
  int j = 0;
	
  // Sent Serial Configuration Data
  File file = SD_MMC.open(path);
  if(!file) {
    Serial.println("Failed to open");
    Serial.println("please check the file exists ");
    return -1;
  }
   
  // seek 100 byte
  int ret = file.seek(100, SeekSet);
  if(!ret) {
    Serial.println("Failed to seek");
    return -1;
  }

  /* put pins down for Configuration */
  pinMode(XFPGA_CCLK_PIN, OUTPUT);
  pinMode(XFPGA_DIN_PIN, OUTPUT);
  digitalWrite(XFPGA_CCLK_PIN, LOW);
  digitalWrite(XFPGA_DIN_PIN, LOW);
  
  /* read data form bitstream */
  byte_len = file.read(byte_buff, READ_SIZE);
   /*
   * loading the bitstream
   * If you want to know the details,you can Refer to the following documentation
   * https://www.xilinx.com/support/documentation/user_guides/ug470_7Series_Config.pdf
   */
  while ((byte_len != 0)&&(byte_len != -1)) {
    for (i = 0;i < byte_len;i++) {
      byte = byte_buff[i];

      for(j = 0;j < 8;j++) {
        digitalWrite(XFPGA_CCLK_PIN, LOW);
        if ((byte&0x80) == 0x80)
          digitalWrite(XFPGA_DIN_PIN, HIGH);
        else
          digitalWrite(XFPGA_DIN_PIN, LOW);
        byte = byte << 1;
        digitalWrite(XFPGA_CCLK_PIN, HIGH);
      }
    }
    byte_len = file.read(byte_buff, READ_SIZE);
  }
  digitalWrite(XFPGA_CCLK_PIN, LOW); 
	
  if(byte_len == -1) Serial.println("read error");
	
  // check the result
  pinMode(XFPGA_DONE_PIN, INPUT);
  if(0 == digitalRead(XFPGA_DONE_PIN)) {
    Serial.println("FPGA Configuration Failed");
  }
  else {
    Serial.println("FPGA Configuration success");
  }
}

// list the files in the directory 
void spartan_edge_esp32_boot::listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
      return;
    }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
        }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
      file = root.openNextFile();
  }
}

// creat a directory
void spartan_edge_esp32_boot::createDir(fs::FS &fs, const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

// remove a directory
void spartan_edge_esp32_boot::removeDir(fs::FS &fs, const char * path){
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)){
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

// read a file and output data by Serial
void spartan_edge_esp32_boot::readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while(file.available()){
    Serial.write(file.read());
  }
}

// write a file, it will recover data
void spartan_edge_esp32_boot::writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
}

// append message in file end
void spartan_edge_esp32_boot::appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)){
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
}

// rename a file
void spartan_edge_esp32_boot::renameFile(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

// delete a file 
void spartan_edge_esp32_boot::deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

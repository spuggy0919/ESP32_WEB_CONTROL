#include "ESP32_8266.h"

/* You only need to format LITTLEFS the first time you run a
   test or else use the LITTLEFS plugin to create a partition
   https://github.com/lorol/arduino-esp32littlefs-plugin 

.pio/libdeps/esp32/LittleFS_esp32/src/LITTLEFS.cpp:44:28: error: no matching function for call to 'LITTLEFSImpl::open(const char*&, const char [2])'
     File f = open(path, "r");  ==>  File f = open(path, "r", false); 

   Warning:This example is from above link but the original 
   library source has has one bug in open declared
*/
void setup(){
    Serial.begin(115200);
     if(!initLittleFS()){
        return;
    }
    Serial.println("LITTLEFS testing .....");
    
    Serial.println(">ls -lR /");
    Serial.println(listDir(LittleFS, "/", 4));
    Serial.println(">rmdir /new1");
  	removeDir(LittleFS, "/new1");
    Serial.println(">mkdir /mydir");
    createDir(LittleFS, "/mydir");
    Serial.println(">mkdir /newdir1");
    createDir(LittleFS, "/newdir1");
    Serial.println(">ls -lR /");
    Serial.println(listDir(LittleFS, "/", 4));
    Serial.println(">echo \"Hello1\" > /mydir/hello1.txt  ");
	  writeFile(LittleFS, "/mydir/hello1.txt", "Hello1");
    Serial.println(">cat /mydir/hello1.txt");
	  Serial.println(readFile(LittleFS, "/mydir/hello1.txt"));
    Serial.println(">echo \"Hello2\" > /hello2.txt ");
    writeFile(LittleFS, "/hello2.txt", "Hello2");
    Serial.println(">cat /mydir/hello2.txt");
	  Serial.println(readFile(LittleFS, "/hello2.txt"));
    Serial.println(">ls -lR /");
    Serial.println(listDir(LittleFS, "/", 4));
  // writeFile(LittleFS, "/mydir/newdir2/newdir3/hello3.txt", "Hello3");
    Serial.println(">echo  \"Hello3\" > /newdir1/newdir2/newdir3/hello3.txt  ");
    writeFile2(LittleFS, "/newdir1/newdir2/newdir3/hello3.txt", "Hello3");
    Serial.println(">cat /mydir/hello3.txt");
    Serial.println(readFile(LittleFS, "/newdir1/newdir2/newdir3/hello3.txt"));
    Serial.println(">ls -lR /");
    Serial.println(listDir(LittleFS, "/", 4));

    Serial.println(">rm /mydir/hello1.txt");
  	deleteFile(LittleFS, "/mydir/hello1.txt");
    Serial.println(">rm /hello2.txt");
  	deleteFile(LittleFS, "/hello2.txt");
    Serial.println(">ls -lR /");
    Serial.println(listDir(LittleFS, "/", 4));
    Serial.println(">rmdir /mydir");
  	removeDir(LittleFS, "/mydir");
    Serial.println(">ls -lR /");
    Serial.println(listDir(LittleFS, "/", 4));
    Serial.println(">echo \"Hello \" > /hello.txt  ");
    writeFile(LittleFS, "/hello.txt", "Hello ");
    Serial.println(">echo \"World!\\r\\n\" >> /hello.txt  ");
    appendFile(LittleFS, "/hello.txt", "World!\r\n");
    Serial.println(">cat /hello.txt");
    Serial.println(readFile(LittleFS, "/hello.txt"));
    Serial.println(">mv /hello.txt /foo.txt");
    renameFile(LittleFS, "/hello.txt", "/foo.txt");
    Serial.println(listDir(LittleFS, "/", 4));
    Serial.println(">cat /foo.txt");
    Serial.println(readFile(LittleFS, "/foo.txt"));
    Serial.println(">rm /foo.txt");
    deleteFile(LittleFS, "/foo.txt");
    Serial.println(">rm /newdir1/newdir2/newdir3/hello3.txt");
    deleteFile(LittleFS, "/newdir1/newdir2/newdir3/hello3.txt");
    Serial.println(">rmdir /newdir1/newdir2/newdir3");
    removeDir(LittleFS, "/newdir1/newdir2/newdir3");
    Serial.println(">rmdir /newdir1/newdir2");
    removeDir(LittleFS, "/newdir1/newdir2");
    Serial.println(">rmdir /newdir1");
    removeDir(LittleFS, "/newdir1");
    testFileIO(LittleFS, "/test.txt");
    Serial.println(">ls -lR /");
    Serial.println(listDir(LittleFS, "/", 4));
    Serial.println(">rm /test.txt");
	  deleteFile(LittleFS, "/test.txt");
    Serial.println( "Test complete" );

    // turn on blue led
    // pwminit();
    // pwmled(64);
}
void loop(){
   
}

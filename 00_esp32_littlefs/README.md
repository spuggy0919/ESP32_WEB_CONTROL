# [中文](./讀我.md)
# *LittleFS* Tutorial 
Let both ESP32 and ESP8266 support *LittleFS*.
*LittleFS* has been in Arduino core library, this Tutorial, modifies listDir of lorol/LittleFS PIO Example, 
and it displays subdriectory recusivly.
## Two fuctions are String return, others are void.
```
String listDir(fs::FS &fs, const char * dirname, uint8_t levels);
String readFile(fs::FS &fs, const char * path);
```
# Platform.IO IDE Choose env
 *Platform.io* will check dependecy and download libraries automatically.
 Tool bar at bottom , click Switch  env icon to select Project and env
#### For ESP32
```
*env:esp32dev (01_esp32_Hello) folder*
```
#### For ESP8266
```
*env:nodemcuv3 (01_esp32_Hello) folder*
```
# Edit *platform.ini*.
 Select esp32 and nodemcu environment 

#### For ESP32
```
[platformio]
default_envs = esp32dev
; default_envs = nodemcuv3
```
#### For ESP8266
```
[platformio]
; default_envs = esp32dev
default_envs = nodemcuv3
```
 We also define *lib_extra_dirs* in *platform.ini* , then *platform.io* will search this path.
 It is located in same Project dir, *00_esp32_littlefs/lib* folder, so does not need to define.

```
;lib_extra_dirs = ../00_esp32_littlefs/lib
```
# In main.cpp, some statements call *littlefsfun* which are defined in *lib* folder.
```
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
```
# Build and Upload, need to push EN button.
 Click the pio tool bar upload icon, for clean build, you can delete *.pio* sub folder in explorer Window at first.

# upload file system, and need to push EN button.
 It will upload data folder to partition SPIFFS, it is OK.
 Click the pio tool bar terminal icon, then cli terminal will display, make sure path with your data then run command in terminal.
```
00_ESP32_Littlefs % pio run -t uploadfs [enter]
```

# Running, serial Monitor Output, it not press reset button on board.
```
rst:0x1 (POWESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:1184
load:0x40078000,len:13132
load:0x40080400,len:3036
entry 0x400805e4
LITTLEFS testing .....
>ls -lR /
directory: /
 file1.txt      3       2021-07-31 12:56:14
 file2.txt      5       2022-09-27 15:46:55
*testfolder
         test1.txt      3       2021-07-31 12:56:14

>rmdir /new1
[   166][E][vfs_api.cpp:237] rmdir(): /new1 does not exists or is a file
>mkdir /mydir
>mkdir /newdir1
>ls -lR /
directory: /
 file1.txt      3       2021-07-31 12:56:14
 file2.txt      5       2022-09-27 15:46:55
*mydir
*newdir1
*testfolder
         test1.txt      3       2021-07-31 12:56:14

>echo "Hello1" > /mydir/hello1.txt  
>cat //mydir/hello1.txt
Hello1
>echo "Hello2" > /hello2.txt 
>cat //mydir/hello2.txt
Hello2
>ls -lR /
directory: /
 file1.txt      3       2021-07-31 12:56:14
 file2.txt      5       2022-09-27 15:46:55
 hello2.txt     6       1970-01-01 00:00:00
*mydir
         hello1.txt     6       1970-01-01 00:00:00
*newdir1
*testfolder
         test1.txt      3       2021-07-31 12:56:14

>echo  "Hello3" > /newdir1/newdir2/newdir3/hello3.txt  
[   798][E][vfs_api.cpp:104] open(): /littlefs/newdir1/newdir2/newdir3/hello3.txt does not exist, no permits for creation
[   814][E][vfs_api.cpp:104] open(): /littlefs/newdir1/newdir2 does not exist, no permits for creation
[   899][E][vfs_api.cpp:104] open(): /littlefs/newdir1/newdir2/newdir3 does not exist, no permits for creation
>cat /mydir/hello3.txt
Hello3
>ls -lR /
directory: /
 file1.txt      3       2021-07-31 12:56:14
 file2.txt      5       2022-09-27 15:46:55
 hello2.txt     6       1970-01-01 00:00:00
*mydir
         hello1.txt     6       1970-01-01 00:00:00
*newdir1
        *newdir2
                *newdir3
                         hello3.txt     6       1970-01-01 00:00:00
*testfolder
         test1.txt      3       2021-07-31 12:56:14

>rm /mydir/hello1.txt
>rm /hello2.txt
>rm /test.txt
[  1365][E][vfs_api.cpp:175] remove(): /test.txt does not exists or is directory
- delete failed
>ls -lR /
directory: /
 file1.txt      3       2021-07-31 12:56:14
 file2.txt      5       2022-09-27 15:46:55
*mydir
*newdir1
        *newdir2
                *newdir3
                         hello3.txt     6       1970-01-01 00:00:00
*testfolder
         test1.txt      3       2021-07-31 12:56:14

>rmdir /mydir
>ls -lR /
directory: /
 file1.txt      3       2021-07-31 12:56:14
 file2.txt      5       2022-09-27 15:46:55
*newdir1
        *newdir2
                *newdir3
                         hello3.txt     6       1970-01-01 00:00:00
*testfolder
         test1.txt      3       2021-07-31 12:56:14

>echo "Hello " > /hello.txt  
>echo "World!\r\n" >> /hello.txt  
>cat /hello.txt
Hello World!

>mv /hello.txt /foo.txt
directory: /
 file1.txt      3       2021-07-31 12:56:14
 file2.txt      5       2022-09-27 15:46:55
 foo.txt        14      1970-01-01 00:00:02
*newdir1
        *newdir2
                *newdir3
                         hello3.txt     6       1970-01-01 00:00:00
*testfolder
         test1.txt      3       2021-07-31 12:56:14

>cat /foo.txt
Hello World!

>rm /foo.txt
>rm /newdir1/newdir2/newdir3/hello3.txt
>rmdir /newdir1/newdir2/newdir3
>rmdir /newdir1/newdir2
>rmdir /newdir1
Testing file I/O with /test.txt
- writing................................................................
 - 1048576 bytes written in 18584 ms
- reading 1048576................................................................
- 1048576 bytes read in 469 ms
>ls -lR /
directory: /
 file1.txt      3       2021-07-31 12:56:14
 file2.txt      5       2022-09-27 15:46:55
 test.txt       1048576 1970-01-01 00:00:02
*testfolder
         test1.txt      3       2021-07-31 12:56:14

>rm /test.txt
Test complete
```
# TODO
### cd command
### pwd command
### shell interface

# [Back to Top](../README.md)
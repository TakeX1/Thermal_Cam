# Thermal_Cam 3X  Rspberry PI3 side
This program is exclusively for Raspberry PI 3 Model B+ to run our iOS app "Thermal Cam3X".
Temperature accuracy can be improved by using Raspberry PI 3 Model B+.

# 1. Hardware
・Raspberry PI3 (does not work on PI4)
・Flir Lepton3.5 (only for LEPTON3.5, for for LEPTON3.0 or the others)
・Flir Lepton Breakout Board (one of the following two types is required)
<https://www.flir.com/products/lepton-breakout-board-v2.0/>  

<https://store.groupgets.com/collections/flir-lepton-accessories/products/purethermal-breakout-board>  


・8 jumper wires (Please match the outlet to your own environment)
# 2.connection between Raspberry PI and breakout Board.
・ Make the cable as short as possible.  
     For stability, we recommend connect via printed circuit board instead of wiring to the board.
    (We will provide you Eagle file after we checked connection later.)  
PastedGraphic-2.png  
・LEPTON shutters are fragile and may come off during use(attach or detach many time) , so it is recommended 
   to protect them with wrap.  
・Be careful about static electricity with it.  

# 3. Program installation method

## A. OS installation
・Connect the keyboard, mouse and display to the Raspberry PI  
Since it does not work well with the latest version of Raspbian, "Buster", you need to download the previous version of "Stretch" from the following URL.  

In Japan.(mirror server)  
<http://ftp.jaist.ac.jp/pub/raspberrypi/raspbian/images/raspbian-2019-04-09/>  
Other countries.  
<https://downloads.raspberrypi.org/raspbian/images/raspbian-2019-04-09/>  

Copy to SD card (about 16Gb) and perform normal installation work  
・When Rasbian starts  
    Turn on i2c, ssh, and spi, and set GPU memory to 128Mb.  
    
・Add the following 4 lines to /boot/config.txt  
    arm_freq=1100  
    over_voltage=4  
    sdram_freq=400  
    core_freq=400  
    gpu_freq=400  

Reboot after the setting is completed.

## B.openFrameworks installation

#### (1) openFrameworks is required.
From the following URL
Index of /versions/v0.10.1/
Download <https://openframeworks.cc/versions/v0.10.1/> Please note that the latest version is not 0.11.0

#### (2) Compile openFrameworks.
<https://openframeworks.cc/setup/raspberrypi/>
After the compilation is complete, move the downloaded and unzipped folder to Your_Openframeworks_Folder/apps/myApps.

#### (3) Build the program
Enter Your_Openframeworks_Folder/apps/myApps/PI_Lepton3.X  
make -j4  

#### (4) Operation check  
After compilation is complete, Your_Openframeworks_Folder/apps/myApps/ PI_Lepton3.X/bin/ PI_Lepton3.X xxx.xxx.xxx.xxx(IP address)

Try to start the program with. xxx.xxx.xxx.xxx is the IP address of iPhone or iPad.
Check the iPhone or iPad iP address in "Settings". When the LEPTON image is displayed on the screen, you are ready.

PastedGraphic-3.png

After confirming the startup, put the Raspberry PI in command line (CLI) mode. This is for stable operation of LEPTON. Images may be cut off frequently in desktop mode. From the terminal screen of Raspberry PI
sudo raspi-config  
 3 Boot Options --> B1 Desktop / CLI --> B2 Console Autologin  

## C. How to connect with iPhone or iPad

You need to install the Thermal Cam 3X app on your device. Please search with w&t or kansaidenki from apple apps store.

#### (1) When connecting with WIFI  
・Connect iPhone or iPad and Raspberry PI 3 to the same WIFI  

#### (2) For tethering connection  
・Turn on the tethering setting of iPhone  
・Set PI to desktop mode and connect to iPhone or iPad  

sudo raspi-config  
   3 Boot Options --> B1 Desktop / CLI --> B4 Desktop Autologin  
・Restart PI in CLI mode. After that, tethering is automatically selected  

sudo raspi-config  
   3 Boot Options --> B1 Desktop / CLI --> B2 Console Autologin  

・Start the program from PI. iP addressing is limited to 172.20.10.1 for iOS.  
・Start Thermal Cam 3X  

#### (3) Lan Wired connection (not recommended for PI beginners)  
・Set PI to host mode  
・Connect the power connector to iPhone and connect it with PI and LAN cable  
・Connect from iPhone to PI  
・Check the iP address of the iPhone and start the PI application.  
Launch the Thermal Cam 3X app.  

# 4. Other
・The PI should ideally be equipped with a small display, but after setting up, the keyboard, display and mouse are not required.
・Automatic connection is possible if each user devises a script.

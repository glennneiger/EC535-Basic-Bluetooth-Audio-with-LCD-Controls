Background:
This is the my groups final project for the Spring 2016 offering of EC 535 at Boston University. The objective of the project was to connect a Gumstix Verdex Pro board with a Bluetooth speaker and play music stored on an SD card from the speaker. We also incorporated a touch screen interface to provide basic Start, Stop, Play, Pause controls. Major challenges were installing the proper packages for audio decoding and playback, installing and configuring the Bluetooth connection, and installing and coding the touch screen interface.

Group Members:
Sam Beaulieu 
Matthew Beach
Wasim Kahn

License:
TBD

How To Install and Run:
0. Collect Required Hardware and Assemble
- Gumstix Boards
- Serial and power cables
- Bluetooth Antenna
- SD card
- LCD touch screen
- Bluetooth Speaker

1. Installing Packages and Libraries:
- Located in the ipks folder are a variety of packages which must be installed to the gumstix.
- Copy all these files to the SD card on the gumstix and, using ipkg, install them to the SD card using a command like so:

ipkg -d external install libaudiofile0_0.2.6-r6_armv5te.ipk

where external is the path to some folder on the SD card such as /media/card/installed_packages. 

- While installing, some libraries will request other libaries on the gumstix saying they could not be found. These need to be symbolically linked from the external folder to the /usr/lib folder. For example, for the following problem, fix with the command after it (followed by the $):

Installing libaudiofile0 (0.2.6-r6) to external...
ipkg: Cannot create symlink from ./usr/lib/libaudiofile.so.0 to 'libaudiofile.so.0.0.2': Operation not permitted
Configuring libaudiofile0

$ ln -s /media/card/installed_packages/usr/lib/libaudiofile.so.0.0.2 /usr/lib/libaudiofile.so.0.0.2


- Once all packages are installed, symbolically link aplay and madplay to the PATH like so:

$ ln -s /media/card/installed_packages/usr/bin/aplay /usr/bin/aplay
$ ln -s /media/card/installed_packages/usr/bin/madplay /usr/bin/madplay

2. Setting up Bluetooth
- Run hcitool scan to search for the MAC address of the speaker you are trying to connect to. Record the address for further use.
- Edit /etc/asound.conf to include the following. Where d80 is an arbitrary name of the speaker and the MAC address is the hex number following "device":

pcm.d80{                                                                        
    type bluetooth                                                              
    device "00:02:3C:41:87:EF"                                                  
}

- Run "passkey-agent 0000 00:02:3C:41:87:EF &" using your MAC address
- Run aplay for the first time using the name of your speaker: "aplay -D d80" 

3. Setting up control scripts
- Copy the two files in the scripts folder to /media/card/project/scripts/ on the gumstix.

4. Compiling QT User Interface
- Open the qt folder
- Make sure you've sourced the EC535 bash script like so:
"source /ad/eng/courses/ec/ec535/bashrc_ec535"
- Run "make" which should make the qt executable
- Copy the executable (titled "qt") to the /media/card/project/scripts/ folder on the gumstix
- Ensure all libraries are loaded to the SD card and symbolic links are created as explained in appendix A below.

5. Fill with mp3 files
- Copy songs to the /media/card/project/mp3s folder on the gumstix. Make sure none of the songs have spaces in their titles. 
- The program will automatically load all the song names.

6. Run
- Enter the scripts directory like so "cd /media/card/project/scripts/"
- Run the boot script: "ash boot.sh"

7. Play music
- Use the LCD touchscreen to play music through the speaker


Appendix A:

copy libraries into a sd card via zmodem:
	sd card is in /media/card on gumstix
	create a folder called lib
	copy following: "fonts libQtCore.so.4 libQtGui.so.4 libQtNetwork.so.4 ld-uClibc.so.0 libc.so.0 libm.so.0 libstdc++.so.6"
		from folder: /ad/eng/courses/ec/ec535/gumstix/oe/qt/lib
		from folder: /ad/eng/courses/ec/ec535/arm-linux/lib
		into /media/card/lib/
create library links in gumstix:
	cd /usr/lib
	ln -s /media/card/lib/libQtCore.so.4 libQtCore.so.4
	ln -s /media/card/lib/libQtGui.so.4 libQtGui.so.4
	ln -s /media/card/lib/libQtNetwork.so.4 libQtNetwork.so.4
	ln -s /media/card/lib/ld-uClibc.so.0 ld-uClibc.so.0
	ln -s /media/card/lib/libc.so.0 libc.so.0
	ln -s /media/card/lib/libm.so.0 libm.so.0
	ln -s /media/card/lib/libstdc\+\+.so.6 libstdc\+\+.so.6
export some variables in gumstix:
	export QWS_MOUSE_PROTO='tslib:/dev/input/touchscreen0'
	export TSLIB_CONFFILE=/etc/ts.conf
	export TSLIB_PLUGINDIR=/usr/lib
	export TSLIB_TSDEVICE=/dev/input/event0
	export TSLIB_FBDEVICE=/dev/fb0
	export TSLIB_CONSOLEDEVICE=/dev/tty
	export QT_QWS_FONTDIR=/media/card/lib/fonts
	export TSLIB_PLUGINDIR=/usr/lib/ts


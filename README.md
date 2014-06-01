#Waveform Image Creator

Waveform Image Creator is a command-line tool for creating an audio waveform image from an audio file. It's a basic version at the moment, but v1.0.0 should be released soon.

It could be useful in a variety of ways, such as creating a waveform display for a custom jPlayer skin. You can always call it from your PHP script with the `exec()` command.

##Usage
Simply run the binary, with the audio file as argument 1, and the image file as argument 2. 
It currently only supports a PNG output, but can read WAV, FLAC, AIFF and OGG.
You can use arguments to style the waveform image...

```-w Image width
-h Image height
-c Waveform colour (AARRGGBB)
``` 

You can also get full help with `-help` and a list of error codes with `-errorcodes`.

##Building
To build, simply...
```cd ./Builds/Linux 
sudo make
``` 

You can then run the binary from the build directory
```./build/AudioWaveformImage audiofile imagefile [arguments]
``` 

##Changelog
v0.0.2
Added waveform colour option
Can now be used via command line

v0.0.1
Initial release

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDrawer.h"


//==============================================================================
int main (int argc, char* argv[])
{
	// Helps shut down JUCE properly
	ScopedJuceInitialiser_GUI sj;

	// File to save
	File waveformImageFile("~/Desktop/WaveformPOO.png");
	if (waveformImageFile.existsAsFile())
		waveformImageFile.deleteFile();
	
    // The class that does the drawing etc.
    WaveformDrawer wfDrawer;
    wfDrawer.setSoundFile("/home/bex/Desktop/ADAM/JUCE/MyApps/drum.wav");
    wfDrawer.normaliseAndAbsolute();
	
	// Take snapshot of WaveformDrawer and save to file
	Image waveformImage = wfDrawer.renderWaveform(600,200);
	FileOutputStream stream (waveformImageFile);
    PNGImageFormat pngWriter;
    pngWriter.writeImageToStream(waveformImage, stream);


	//delete wfDrawer;
    return 0;
}

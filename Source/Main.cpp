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
	
	//DBG("Number of Args: " + String(argc));
	
	//for (int args = 0; args < argc; args++
	
	/**
	 * Ideas for arguments
	 * 
	 * arg[1]			audio file
	 * arg[2]			image file
	 * 
	 * -help			shows help file
	 * -colour			colour of waveform (e.g #353535)
	 * -colour2			colour of second waveform (e.g. #353535) (peak colour if using -rmspeak option)
	 * -o				draws outline
	 * -o-colour		outline colour (e.g #353535)
	 * -mode		peak		peak values
	 * 				rms			rms valus
	 * 				both		both values overlayed		
	 * -normalise		normalise file
	 * -style		regular		regular shape waveform
	 * 				single		single sided waveform
	 * 				bars		bars
	 * -bars-size		bars size in pixels
	 * 
	 */
	
	
	
	
	// Helps shut down JUCE properly
	ScopedJuceInitialiser_GUI sj;

	// File to save
	File waveformImageFile("~/Desktop/Waveform.png");
	if (waveformImageFile.existsAsFile())
		waveformImageFile.deleteFile();
	
    // The class that does the drawing etc.
    WaveformDrawer wfDrawer;
    wfDrawer.setSoundFile("~/Desktop/ADAM/JUCE/MyApps/Streets.wav");
    
    wfDrawer.setColour("ff232323");
    //wfDrawer.normaliseAndAbsolute();
	
	// Take snapshot of WaveformDrawer and save to file
	Image waveformImage = wfDrawer.renderWaveform(600,100);
	FileOutputStream stream (waveformImageFile);
    PNGImageFormat pngWriter;
    pngWriter.writeImageToStream(waveformImage, stream);


	//delete wfDrawer;
    return 0;
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDrawer.h"


//==============================================================================

void printHelp()
{
	printf("AudioWaveformImage by Arctican Audio\n\n"); 
	printf("usage: AudioWaveformImage audiofile imagefile [args]\n"); 
	
}


int main (int argc, char* argv[])
{	
	// Check there's enough arguments
	if (argc < 2)
	{
		printHelp();
		return 1; 
	}
	
	// Get file paths, and setup default variables
	String audioFilePath = argv[1];		//~/Desktop/Waveform.png
	String imageFilePath = argv[2];		//~/Desktop/ADAM/JUCE/MyApps/Streets.wav
	String mainColour = "FFFFFFFF";
	String imageWidth = "600";
	String imageHeight = "200";
	
	// Get arguments
	if (argc > 2)
	{
		for (int args = 3; args < argc; args++)
		{
			String argument = argv[args];
			
			// Main colour argument
			if (argument == "-c")
			{
				mainColour = argv[args+1];
				args++;
			}

			// Image width
			if (argument == "-w")
			{
				imageWidth = argv[args+1];
				args++;
			}				

			// Image height
			if (argument == "-h")
			{
				imageHeight = argv[args+1];
				args++;
			}	
			
		}
	}
	
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
	File waveformImageFile(imageFilePath);
	if (waveformImageFile.existsAsFile())
		waveformImageFile.deleteFile();
	
    // The class that does the drawing etc.
    WaveformDrawer wfDrawer;
    wfDrawer.setSoundFile(audioFilePath);
    
    wfDrawer.setColour(mainColour);
    //wfDrawer.normaliseAndAbsolute();
	
	// Take snapshot of WaveformDrawer and save to file
	Image waveformImage = wfDrawer.renderWaveform(imageWidth.getIntValue(),imageHeight.getIntValue());
	FileOutputStream stream (waveformImageFile);
    PNGImageFormat pngWriter;
    pngWriter.writeImageToStream(waveformImage, stream);


	//delete wfDrawer;
    return 0;
}

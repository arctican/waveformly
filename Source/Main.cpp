/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDrawer.h"


//==============================================================================

void printInfo()
{
	printf("AudioWaveformImage by Arctican Audio\n\n"); 

}

void printUsage()
{
	printf("usage: AudioWaveformImage audiofile imagefile [options]\n"); 
	printf("Use -help to get full help\n"); 	
}

void printHelp(String helpMode, String error)
{
	printInfo();
	
	if (helpMode != "ALL")
		printUsage();
		
	// Print passed error message
	if (error.isNotEmpty())
		printf("%s\n", error.toRawUTF8());
	
	
	// Main colour help
	if (helpMode == "-c" || helpMode == "ALL")
	{
		printf("-c\t<string>\tThe main waveform colour in alpha hex format - AARRGGBB.\n"); 
		printf("\t\t\t(e.g. FF00FF00 for opaque blue).\n");	
	} 

	// Image width help
	if (helpMode == "-w" || helpMode == "ALL")
		printf("-w\t<int>\t\tThe image width in pixels.\n");	
		
	// Image height help
	if (helpMode == "-h" || helpMode == "ALL")
		printf("-h\t<int>\t\tThe image height in pixels.\n");
		
		
	// Print error codes
	if (helpMode == "-errorcodes")
	{
		printf("0\t\tAll OK!.\n");
		printf("1\t\tNot enough arguments.\n");
		printf("10\t\tIncorrect colour argument.\n");
		printf("11\t\tIncorrect width argument.\n");
		printf("12\t\tIncorrect height argument.\n");		
		
	}	
		
}








int main (int argc, char* argv[])
{	
	// Show help
	String argument = argv[1];
	if (argument == "-help")
	{
		printHelp("ALL", "");
		return 0;
	}	
	if (argument == "-errorcodes")
	{
		printHelp(argument, "");
		return 0;
	}		
	
	
	// Check there's enough arguments
	if (argc < 3)
	{
		printInfo();
		printUsage();
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
				if (mainColour.length() != 8 || ! mainColour.containsOnly("0123456789abcdefABCDEF"))
				{
					printHelp(argument, "That's not a correct colour!");
					return 10;
				}
				args++;
			}

			// Image width
			if (argument == "-w")
			{
				imageWidth = argv[args+1];
				if (imageWidth.getIntValue() < 1)
				{
					printHelp(argument, "You need a width of more than 1 pixel!");
					return 11;
				}
				args++;
			}				

			// Image height
			if (argument == "-h")
			{
				imageHeight = argv[args+1];
				if (imageHeight.getIntValue() < 1)
				{
					printHelp(argument, "You need a height of more than 1 pixel!");
					return 12;
				}
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
	
	// Take snapshot of WaveformDrawer and save to file
	Image waveformImage = wfDrawer.renderWaveform(imageWidth.getIntValue(),imageHeight.getIntValue());
	FileOutputStream stream (waveformImageFile);
    PNGImageFormat pngWriter;
    pngWriter.writeImageToStream(waveformImage, stream);

    return 0;
}

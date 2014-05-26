/*
  ==============================================================================

    WaveformDrawer.cpp
    Created: 26 May 2014 5:16:34pm
    Author:  bex

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDrawer.h"

//==============================================================================
WaveformDrawer::WaveformDrawer()
{
}

WaveformDrawer::~WaveformDrawer()
{
}




Image WaveformDrawer::renderWaveform(int width, int height)
{
	
	// Create a blank Image
	Image myImage (Image::RGB, 500, 500, true);
	Graphics g (myImage);
	g.setColour (Colours::red);
	g.fillEllipse (20, 20, 300, 200);  // draws a red ellipse in our image.
	g.drawText(String(buffer.getNumSamples()), 0,0,100,100,Justification::left,true);
	

	
	return myImage;
	
}


void WaveformDrawer::setSoundFile(String soundFile)
{
	// Audio File
    File audioFile(soundFile); 
    
    // Get a format manager and set it up with the basic types (wav and aiff).
	AudioFormatManager formatManager;
	formatManager.registerBasicFormats();
	 
	// Create reader for file
    AudioFormatReader* reader = formatManager.createReaderFor (audioFile);
		
	// Load data to AudioBuffer
	AudioSampleBuffer readBuffer(reader->numChannels, reader->lengthInSamples);
	reader->read(&readBuffer, 0, reader->lengthInSamples, 0, true, true);
	buffer = readBuffer;
	delete reader;
	
	
	
	
}

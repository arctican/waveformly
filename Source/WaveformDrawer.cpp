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
	Image myImage (Image::RGB, width, height, true);
	Graphics g (myImage);
	g.setColour (Colours::red);
	
	// Get samples as floats
	float* samples = buffer.getSampleData(0);
	
    // Create path to show waveform
    Path waveformPath;
	waveformPath.startNewSubPath (0.0f, height);
    
    // Find sample incrementer
    float inc = buffer.getNumSamples()/width;
    
    // Loop through all pixels of width
    for (int i=0; i<width; i++)
    {
		// Find sample to select 
		int sample = (int) i*inc;
		float value = 0.0;
		
		// Find peak of block for this pixel
		for (int x=0; x<inc; x++)
			if ( fabs(samples[x+sample]) > value)	value = fabs(samples[x+sample]);

		// Draw point on Y axis for peak of block
		float y = (value*-height) + height;
		waveformPath.lineTo (i, y); 
	}
	
	g.strokePath (waveformPath, PathStrokeType (1.0f));   
	
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


void WaveformDrawer::normaliseAndAbsolute()
{
	// Normalise the buffer
	float maximumLevel = buffer.getMagnitude ( 0, 0, buffer.getNumSamples());
	float gainFactor = 1 / maximumLevel;
	buffer.applyGain	(0, 0, buffer.getNumSamples(), gainFactor); 
	
	// Get samples as floats
	float* samples = buffer.getSampleData(0);
	
	// Absolute entire buffer
	for (int i=0; i<buffer.getNumSamples(); i++)
		samples[i] = fabs(samples[i]);

	
}

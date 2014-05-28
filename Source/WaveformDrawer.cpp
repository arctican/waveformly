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
	g.setColour (Colours::yellow);
	
	// Get samples as floats
	float* samples = buffer.getSampleData(0);
	
    // Create path to show waveform
    Path waveformPath;
	waveformPath.startNewSubPath (0.0f, height);
    
    // Split buffer into blocks (1 per pixel)
    Array<float> arrayBlock = splitIntoBlocks(buffer, width);
    normalise(arrayBlock);
    
    // Loop through all pixels of width
    for (int i=0; i<width; i++)
    {
		// Draw point on Y axis
		float value = arrayBlock[i];
		float y = (value*-height) + height;
		waveformPath.lineTo (i, y); 
	}
	
	// Close path back to start
	waveformPath.lineTo (width, height);
	waveformPath.closeSubPath();
	
	g.strokePath (waveformPath, PathStrokeType (1.0f));   
	g.fillPath(waveformPath);
	
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
	{
		samples[i] = fabs(samples[i]);
		//samples[i] = samples[i] * samples[i] * samples[i];
	}
	
	DBG("Max Level: " + String(maximumLevel));
	DBG("Gain Factor: " + String(gainFactor));
	
}





Array<float> WaveformDrawer::splitIntoBlocks(AudioSampleBuffer buffer, int numberOfBlocks)
{
	// Get samples as floats
	float* samples = buffer.getSampleData(0);
	
	// The data
	Array<float> arrayBlock;
    
    // Find sample incrementer
    int inc = buffer.getNumSamples()/numberOfBlocks;
    
    // Loop through all blocks
    for (int i=0; i<numberOfBlocks; i++)
    {
		// Find sample of start of block
		int sample = i*inc;
		float value = 0.0;
		
		// Find peak of block for this pixel
//		for (int x=0; x<inc; x++)
//			if ( fabs(samples[x+sample]) > value)	value = fabs(samples[x+sample]);
			
			
		// Find RMS value of this block
		float meanAverage = 0.0;
		for (int x=0; x<inc; x++)
			meanAverage += (fabs(samples[x+sample]) * fabs(samples[x+sample]));	
		meanAverage = meanAverage / inc;
		value = sqrt (meanAverage);

		// Add value to array
		arrayBlock.add(value);
		
	}	
	
	// Return the array
	return arrayBlock;
}



void WaveformDrawer::normalise(Array<float> &arrayToNormailse)
{
	// Find max value
	float maxVal = 0.0;
	for (int i=0; i<arrayToNormailse.size(); i++)
	{
		if ( fabs(arrayToNormailse[i] > maxVal)	)	maxVal = fabs(arrayToNormailse[i]);
	}
	
	// Normalise
	float gainFactor = 1 / maxVal;
	for (int i=0; i<arrayToNormailse.size(); i++)
	{
		arrayToNormailse.set(i, arrayToNormailse[i] * gainFactor);
	}
	
}

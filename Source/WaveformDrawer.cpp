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
	
	// Get array of positive values
	Array<float> posBlocks = getPositiveBlocks(width);

	// Get array of negative values
	Array<float> negBlocks = getNegativeBlocks(width);
	absoluteArray(negBlocks);
 
	// Create paths to show waveform
    Path waveformPathPlus;
	waveformPathPlus.startNewSubPath (0.0f, height/2);
    Path waveformPathMinus;
	waveformPathMinus.startNewSubPath (0.0f, height/2); 
	   
    // Loop through all pixels of width
    for (int i=0; i<width; i++)
    {
		// Draw point on Y axis
		float value = posBlocks[i];
		float y = (value*(-height/2)) + (height/2);
		waveformPathPlus.lineTo (i, y); 
		
		value = negBlocks[i];
		float y2 = (value*(height/2)) + (height/2);
		waveformPathMinus.lineTo (i, y2); 
		
	}
	
	// Close path back to start
	waveformPathPlus.lineTo (width, height/2);
	waveformPathPlus.closeSubPath();
	waveformPathMinus.lineTo (width, height/2);
	waveformPathMinus.closeSubPath();
		
	// Draw path to image
//	g.strokePath (waveformPathPlus, PathStrokeType (1.0f));   
//	g.strokePath (waveformPathMinus, PathStrokeType (1.0f));   
	
	
	g.setColour (Colours::cyan);
	g.fillPath(waveformPathPlus);
	g.fillPath(waveformPathMinus);	
	return myImage;
	
}
//----------------------------------------------------------------------






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
//----------------------------------------------------------------------















void WaveformDrawer::normaliseArray(Array<float> &arrayToNormailse)
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
//----------------------------------------------------------------------



void WaveformDrawer::absoluteArray(Array<float> &arrayToAbsolute)
{
	for (int i=0; i<arrayToAbsolute.size(); i++)
	{
		arrayToAbsolute.set(i, fabs(arrayToAbsolute[i]));
	}
}
//----------------------------------------------------------------------








Array<float> WaveformDrawer::getPositiveBlocks(int numberOfBlocks)
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
		
		// Find Positive RMS value of this block
		float meanAverage = 0.0;
		int numberOfValues = 0;
		for (int x=sample; x<inc+sample; x++)
		{
			if (samples[x] > 0.0)
			{
				meanAverage += samples[x] * samples[x];
				numberOfValues++;
			}	
		}
		if (numberOfValues > 0)
		{
			meanAverage = meanAverage / numberOfValues;
			value = sqrt (meanAverage);
		}
		
		// Add value to array
		arrayBlock.add(value);
	}	
	
	// Return the array
	return arrayBlock;	
}
//----------------------------------------------------------------------








Array<float> WaveformDrawer::getNegativeBlocks(int numberOfBlocks)
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
		
		// Find Negative RMS value of this block
		float meanAverage = 0.0;
		int numberOfValues = 0;
		for (int x=sample; x<inc+sample; x++)
		{
			if (samples[x] < 0.0)
			{
				meanAverage += samples[x] * samples[x];
				numberOfValues++;
			}	
		}
		if (numberOfValues > 0)
		{
			meanAverage = meanAverage / numberOfValues;
			value = sqrt (meanAverage);
		}
		
		// Add value to array
		arrayBlock.add(value * -1.0);
	}	
	
	// Return the array
	return arrayBlock;	
}
//----------------------------------------------------------------------






Array<float> WaveformDrawer::getAbsoluteBlocks(int numberOfBlocks)
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
		
		// Find Absolute RMS value of this block
		float meanAverage = 0.0;
		int numberOfValues = 0;
		
		for (int x=sample; x<inc+sample; x++)
		{
			if (samples[x] != 0.0)
			{
				meanAverage += (fabs(samples[x+sample]) * fabs(samples[x+sample]));
				numberOfValues++;
			}	
		}
		if (numberOfValues > 0)
		{
			meanAverage = meanAverage / numberOfValues;
			value = sqrt (meanAverage);
		}
		
		// Add value to array
		arrayBlock.add(value);
	}	
	
	// Return the array
	return arrayBlock;		
}
//----------------------------------------------------------------------

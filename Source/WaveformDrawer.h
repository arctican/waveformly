/*
  ==============================================================================

    WaveformDrawer.h
    Created: 26 May 2014 5:16:34pm
    Author:  bex

  ==============================================================================
*/

#ifndef WAVEFORMDRAWER_H_INCLUDED
#define WAVEFORMDRAWER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDrawer
{
public:
	
    WaveformDrawer();
    ~WaveformDrawer();
    
    /**
     * Renders the waveform
     * 
     * @ return 	The waveform as a JUCE::Image
     */
    Image renderWaveform(int width, int height);
    
    /**
     * Set the source file of the sound to draw.
     * 
     * @ param 	soundFile	A string of the path if the file
     */    
    void setSoundFile(String soundFile);
    
    /**
     * Set the colour of the waveform
     * 
     * @ param 	colourToSet	A string of the colour in hex format with alpha (e.g. #FF232323);
     */  
    void setColour(String colourToSet);
    

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDrawer)
    
	AudioSampleBuffer buffer;
	Colour mainColour;
	
	
	/** 
	 * Normalise the array
	 */
	void normaliseArray(Array<float> &arrayToNormailse);
	
	/** 
	 * Absolute the array
	 */	
	void absoluteArray(Array<float> &arrayToAbsolute);
	
	
	
	
	
	
	
	/**
     * Returns a float array of the positive RMS values of each block
     */				
	Array<float> getPositiveBlocks(int numberOfBlocks);
	
	/**
     * Returns a float array of the ngative RMS values of each block
     */	
	Array<float> getNegativeBlocks(int numberOfBlocks);
	
	/**
     * Returns a float array of the absolute RMS values of each block
     */	
	Array<float> getAbsoluteBlocks(int numberOfBlocks);
};


#endif  // WAVEFORMDRAWER_H_INCLUDED

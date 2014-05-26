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
     * Normalises and absolutes the values to make sure values are between 0-1
     */
    void normaliseAndAbsolute();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDrawer)
    
	AudioSampleBuffer buffer;
  
};


#endif  // WAVEFORMDRAWER_H_INCLUDED

/*
  ==============================================================================

    WaveformDrawer.h
    Created: 13 Jun 2016 8:17:19pm
    Author:  Adam Rogers

  ==============================================================================
*/

#ifndef WAVEFORMDRAWER_H_INCLUDED
#define WAVEFORMDRAWER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDrawer    : public Component
{
public:
    WaveformDrawer()
    {
		File audioFile("~/Desktop/drumloop.mp3");
		AudioFormatManager formatManager;
		formatManager.registerBasicFormats();
		ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(audioFile);
		if (reader != 0)
		{
			buffer = AudioSampleBuffer(reader->numChannels, reader->lengthInSamples);
			reader->read (&buffer, 0, reader->lengthInSamples, 0, true, true);
		}

	}

    ~WaveformDrawer()
    {
    }

    void paint (Graphics& g) override
    {
		Path waveformPath;
		waveformPath.startNewSubPath(0, 0);
		const float* samples = buffer.getReadPointer(0);
		for (int xPixel = 0; xPixel < getWidth(); xPixel++)
		{
			int samplesPerPixel = buffer.getNumSamples() / getWidth();
			double levelOfPixel = 0.0;
			for (int sample = xPixel * samplesPerPixel; sample <  xPixel * samplesPerPixel + samplesPerPixel; sample++)
			{
				if (fabs(samples[sample]) > levelOfPixel)
					levelOfPixel = fabs(samples[sample]);
			}
			waveformPath.lineTo(xPixel, levelOfPixel * getHeight());
		}
		waveformPath.lineTo(getWidth(), 0);
		
		
		g.fillAll (Colour(0xffF36C3D));
		g.setColour(Colours::black);
		g.fillPath(waveformPath);//, PathStrokeType(0.2));
		
	
    }

    void resized() override
    {
	}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDrawer)
	
	AudioSampleBuffer buffer;
};


#endif  // WAVEFORMDRAWER_H_INCLUDED

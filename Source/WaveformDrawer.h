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
class WaveformDrawer    :	public Component,
							public FileDragAndDropTarget
{
public:
    WaveformDrawer()
    {
		isDragAndDropping = false;
		loadFile("~/Desktop/drumloop.mp3");
	}

    ~WaveformDrawer()
    {
    }

    void paint (Graphics& g) override
    {
		int midPoint = getHeight() / 2;
		Path waveformPathPos;
		Path waveformPathNeg;
		
		waveformPathPos.startNewSubPath(0, midPoint);
		waveformPathNeg.startNewSubPath(0, midPoint);
		
		const float* samples = buffer.getReadPointer(0);
		for (int xPixel = 0; xPixel < getWidth(); xPixel++)
		{
			int samplesPerPixel = buffer.getNumSamples() / getWidth();
			
			double levelOfPixelPos = 0.0;
			double levelOfPixelNeg = 0.0;
			for (int sample = xPixel * samplesPerPixel; sample <  xPixel * samplesPerPixel + samplesPerPixel; sample++)
			{
				if (samples[sample] > levelOfPixelPos)
					levelOfPixelPos = samples[sample];
				if (samples[sample] < levelOfPixelNeg)
					levelOfPixelNeg = samples[sample];
			}
			
			
			float yPixelPos = levelOfPixelPos * midPoint + midPoint;
			float yPixelNeg = midPoint - (fabs(levelOfPixelNeg) * midPoint);
			
			waveformPathPos.lineTo(xPixel, yPixelPos);
			waveformPathNeg.lineTo(xPixel, yPixelNeg);
		}
		waveformPathPos.lineTo(getWidth(), midPoint);
		waveformPathNeg.lineTo(getWidth(), midPoint);
		
		g.fillAll (Colour(0xffF36C3D));
		g.setColour(Colours::black);
		g.fillPath(waveformPathPos);
		g.fillPath(waveformPathNeg);
		
		if (isDragAndDropping)
			g.fillAll(Colour::fromFloatRGBA(255, 255, 255, 0.15));
		
	
    }

    void resized() override
    {
	}
	
	bool isInterestedInFileDrag(const juce::StringArray &files) override
	{
		return true;
	}
	
	void filesDropped (const StringArray &files, int x, int y) override
	{
		isDragAndDropping = false;

		if (files.size() > 1)
		{
			AlertWindow::showNativeDialogBox(	"Too many files!",
												"You can only load one waveform at a time.",
												false);
		}
		else
		{
			if (loadFile(files[0]))
				repaint();
			else
				AlertWindow::showNativeDialogBox(	"Can't load file!",
													"Are you trying to load uncompatible file.",
													false);
		}
	}
	
	bool loadFile (String filePath)
	{
		File audioFile(filePath);
		AudioFormatManager formatManager;
		formatManager.registerBasicFormats();
		ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(audioFile);
		if (reader != 0)
		{
			buffer = AudioSampleBuffer(reader->numChannels, reader->lengthInSamples);
			reader->read (&buffer, 0, reader->lengthInSamples, 0, true, true);
			return true;
		}
		else
			return false;
	}

	void fileDragExit (const StringArray& files) override
	{
		isDragAndDropping = false;
		repaint();
	}
	void fileDragEnter (const StringArray& files, int x, int y) override
	{
		isDragAndDropping = true;
		repaint();
	}
	
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDrawer)
	
	AudioSampleBuffer buffer;
	bool isDragAndDropping;
};


#endif  // WAVEFORMDRAWER_H_INCLUDED

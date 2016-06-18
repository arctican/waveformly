/*
  ==============================================================================

    WaveformlyLookAndFeel.h
    Created: 18 Jun 2016 9:08:30pm
    Author:  Adam Rogers

  ==============================================================================
*/

#ifndef WAVEFORMLYLOOKANDFEEL_H_INCLUDED
#define WAVEFORMLYLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformlyLookAndFeel    : public LookAndFeel_V3
{
public:
	WaveformlyLookAndFeel()
	{
		
	}
	
	Typeface::Ptr getTypefaceForFont(const Font &font) override
	{
		Typeface::Ptr lato = Typeface::createSystemTypefaceFor(BinaryData::LatoLight_ttf, BinaryData::LatoLight_ttfSize);
		
		Typeface::Ptr fontAwesome = Typeface::createSystemTypefaceFor(BinaryData::fontawesomewebfont_ttf, BinaryData::fontawesomewebfont_ttfSize);
		
		if (font.getTypefaceName() == "FontAwesome")
			return fontAwesome;
		else
			return lato;
	}
	
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformlyLookAndFeel)
};


#endif  // WAVEFORMLYLOOKANDFEEL_H_INCLUDED

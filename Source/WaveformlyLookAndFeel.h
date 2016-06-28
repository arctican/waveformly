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
	
	virtual void drawLinearSliderBackground (Graphics& g,
											 int x, int y, int width, int height,
											 float sliderPos,
											 float minSliderPos,
											 float maxSliderPos,
											 const Slider::SliderStyle style,
											 Slider& slider) override
	{
		const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
		const int trackHeight = 3;
		if (slider.isHorizontal())
		{
			g.setColour(Colours::white);
			g.fillRoundedRectangle(sliderRadius * 0.5,
								   (height / 2.0) - (trackHeight / 2.0),
								   width + (sliderRadius * 0.5),
								   trackHeight,
								   trackHeight );
		}
		else
		{
			g.setColour(Colours::white);
			g.fillRoundedRectangle(sliderRadius * 0.5,
								   (height / 2.0) - (trackHeight / 2.0),
								   width + (sliderRadius * 0.5),
								   trackHeight,
								   trackHeight );
			
			g.fillRoundedRectangle((width / 2.0) - (trackHeight / 2.0),
								   sliderRadius * 0.5,
								   trackHeight,
								   height + (sliderRadius * 0.5),
								   trackHeight);

		}
		
	}
	
	virtual void drawLinearSliderThumb (Graphics& g,
										int x, int y, int width, int height,
										float sliderPos,
										float minSliderPos,
										float maxSliderPos,
										const Slider::SliderStyle style,
										Slider& slider) override
	{
		const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
		
		if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
		{
			float kx, ky;
			
			if (style == Slider::LinearVertical)
			{
				kx = x + width * 0.5f;
				ky = sliderPos;
			}
			else
			{
				kx = sliderPos;
				ky = y + height * 0.5f;
			}
			
			g.setColour(Colours::white);
			g.fillEllipse(kx - sliderRadius, ky - sliderRadius, sliderRadius * 2.0f, sliderRadius * 2.0f);
		}
	}
	
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformlyLookAndFeel)
};


#endif  // WAVEFORMLYLOOKANDFEEL_H_INCLUDED

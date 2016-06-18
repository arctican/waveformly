/*
  ==============================================================================

    FontAwesomeButton.cpp
    Created: 18 Jun 2016 9:17:46pm
    Author:  Adam Rogers

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FontAwesomeButton.h"

//==============================================================================
FontAwesomeButton::FontAwesomeButton()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FontAwesomeButton::~FontAwesomeButton()
{
}

void FontAwesomeButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
	if (isMouseOverButton)
	{
		g.fillAll (Colours::white);
		g.setColour (Colours::black);
	}
	else
	{
		g.fillAll (Colours::black);
		g.setColour (Colours::white);
	}
	
	g.setFont (Font("FontAwesome", 16.0f, Font::FontStyleFlags::plain));
    g.drawText (getButtonText(), getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void FontAwesomeButton::resized()
{
}

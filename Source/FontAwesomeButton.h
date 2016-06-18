/*
  ==============================================================================

    FontAwesomeButton.h
    Created: 18 Jun 2016 9:17:46pm
    Author:  Adam Rogers

  ==============================================================================
*/

#ifndef FONTAWESOMEBUTTON_H_INCLUDED
#define FONTAWESOMEBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class FontAwesomeButton    : public TextButton
{
public:
    FontAwesomeButton();
    ~FontAwesomeButton();

    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
    void resized();
	
	

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FontAwesomeButton)
};


#endif  // FONTAWESOMEBUTTON_H_INCLUDED

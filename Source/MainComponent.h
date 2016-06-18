/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDrawer.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   :	public Component,
								public Button::Listener,
								public Slider::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
	void buttonClicked(Button*) override;
	void sliderValueChanged(Slider*) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
	
	WaveformDrawer drawer;
	
	TextButton saveButton;
	TextButton openButton;
	
	Slider hueSlider;
	Label hueLabel;
	
};


#endif  // MAINCOMPONENT_H_INCLUDED

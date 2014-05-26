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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveformDrawer::~WaveformDrawer()
{
}

void WaveformDrawer::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("WaveformDrawer", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void WaveformDrawer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

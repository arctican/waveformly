/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
	addAndMakeVisible(drawer);
    setSize (600, 400);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
}

void MainContentComponent::resized()
{
	drawer.setBounds(0, 0, getWidth(), getHeight());
}

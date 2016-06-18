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
	
	addAndMakeVisible(saveButton);
	saveButton.setButtonText("S");
	saveButton.addListener(this);
	
	addAndMakeVisible(openButton);
	openButton.setButtonText("O");
	openButton.addListener(this);
	
	
	addAndMakeVisible(hueSlider);
	hueSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	hueSlider.setRange(0, 1.0);
	hueSlider.setValue(0.0430403, dontSendNotification);
	hueSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	hueSlider.addListener(this);
	
	addAndMakeVisible(hueLabel);
	hueLabel.setColour(Label::ColourIds::textColourId, Colours::white);
	hueLabel.setText("Background Hue", dontSendNotification);
	hueLabel.setJustificationType(Justification::centred);
}

MainContentComponent::~MainContentComponent()
{
	saveButton.removeListener(this);
	openButton.removeListener(this);
	hueSlider.removeListener(this);
}

void MainContentComponent::paint (Graphics& g)
{
	g.fillAll(Colours::black);
}



void MainContentComponent::resized()
{
	int toolbarHeight = 30;
	drawer.setBounds(0, toolbarHeight, getWidth(), getHeight() - toolbarHeight);
	openButton.setBounds(0, 0, toolbarHeight, toolbarHeight);
	saveButton.setBounds(30, 0, toolbarHeight, toolbarHeight);
	hueSlider.setBounds(60, toolbarHeight / 2, 200, toolbarHeight / 2.0);
	hueLabel.setBounds(60, 0, 200, toolbarHeight / 2.0);
}


void MainContentComponent::buttonClicked(Button* button)
{
	if (button == & saveButton)
	{
		FileChooser myChooser ("Save Waveform...",
							   File::getSpecialLocation (File::userDesktopDirectory),
							   "*.png");
		
		if (myChooser.browseForFileToSave (true))
		{
			Image waveformImage(Image::PixelFormat::RGB, drawer.getWidth(), drawer.getHeight(), true);
			Graphics g(waveformImage);
			drawer.paint(g);
			
			File savedFile(myChooser.getResult());
			//savedFile = savedFile.withFileExtension("png");
			
			savedFile.deleteFile();
			
			FileOutputStream stream (savedFile);
			PNGImageFormat writer;
			writer.writeImageToStream(waveformImage, stream);
			
		}
	}
	else if (button == &openButton)
	{
		FileChooser myChooser ("Open Audio File...",
							   File::getSpecialLocation (File::userDesktopDirectory),
							   "*.wav;*.mp3;");
		
		if (myChooser.browseForFileToOpen())
		{
			drawer.loadFile(myChooser.getResult().getFullPathName());
		}
	}
}


void MainContentComponent::sliderValueChanged(Slider* slider)
{
	drawer.setHue(slider->getValue());
	drawer.repaint();
}
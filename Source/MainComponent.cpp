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
	saveButton.setButtonText("Save");
	saveButton.addListener(this);
	
	addAndMakeVisible(openButton);
	openButton.setButtonText("Open");
	openButton.addListener(this);
	
	
	addAndMakeVisible(hueSlider);
	hueSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	hueSlider.setRange(0, 1.0);
	hueSlider.setValue(0.0430403, dontSendNotification);
	hueSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	hueSlider.addListener(this);
	
	addAndMakeVisible(hueLabel);
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
}



void MainContentComponent::resized()
{
	drawer.setBounds(0, 0, getWidth(), getHeight());
	openButton.setBounds(0, 0, 50, 50);
	saveButton.setBounds(50, 0, 50, 50);
	hueSlider.setBounds(100, 25, 200, 25);
	hueLabel.setBounds(100, 0, 200, 25);
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
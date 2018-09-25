/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HardClippingAudioProcessorEditor::HardClippingAudioProcessorEditor (HardClippingAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 300);
	setResizable(true, true);
	AudioProcessorEditor::setResizeLimits(100, 100, 1800, 1000);

	for (int i = 0; i < sliderCount; i++)
	{
		sliders[i].setSliderStyle(Slider::LinearBarVertical);
		sliders[i].setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		sliders[i].setPopupDisplayEnabled(true, false, this);
		addAndMakeVisible(&sliders[i]);
		sliders[i].addListener(this);

		switch (i)
		{
		case gainSlider:
			sliders[i].setRange(1.0, 100.0, 1.0);
			sliders[i].setValue(1.0);
			sliderLabels[i] = "Gain";
			break;
		case volumeSlider:
			sliders[i].setRange(0.0, 1.0, 0.01);
			sliders[i].setValue(0.0001);
			sliderLabels[i] = "Volume";
			break;
		case gateSlider:
			sliders[gateSlider].setRange(0.0, 0.001, 0.00001);
			sliders[gateSlider].setValue(0.0);
			sliderLabels[i] = "Gate";
			break;
		}
	}

	addAndMakeVisible(distortionList);
	distortionList.addItem("Hard Clipping", p.hardClipping);
	distortionList.addItem("Inverse-Power", p.inversePower);

	distortionList.onChange = [this] {distortionChanged(); };
	
}

HardClippingAudioProcessorEditor::~HardClippingAudioProcessorEditor()
{
}

//==============================================================================
void HardClippingAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);

	for (int i = 0; i < sliderCount; i++)
	{
		g.drawFittedText(sliderLabels[i], (int)(((i + 1) * gapWidth + (i + 0.5) * sliderWidth - (gapWidth + sliderWidth) / 2 + sliderAreaCornerX) * getWidth()),
			(int)((sliderHeight + sliderVerticalMargin + sliderAreaCornerY) * getHeight()),
			(int)(sliderLabelWidth * getWidth()), (int)(sliderLabelHeight * getHeight()),
			Justification::centred, 1);
	}
}

void HardClippingAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	for (int i = 0; i < sliderCount; i++)
	{
		sliders[i].setBounds((int)(((i + 1) * gapWidth + i * sliderWidth + sliderAreaCornerX) * getWidth()), (int)((sliderVerticalMargin + sliderAreaCornerY) * getHeight()),
			(int)(sliderWidth * getWidth()), (int)(sliderHeight * getHeight()));
	}

	distortionList.setBounds((int)(getWidth() / 6.0), 0.05 * getHeight(), (int)(2 * getWidth() / 3), (int)(0.1 * getHeight()));
}

void HardClippingAudioProcessorEditor::distortionChanged()
{
	processor.distortionAlgorithm = (HardClippingAudioProcessor::DistortionType)distortionList.getSelectedId();
}

void HardClippingAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	processor.gainLevel = sliders[gainSlider].getValue();
	processor.volumeLevel = sliders[volumeSlider].getValue();
	processor.gateThreshold = sliders[gateSlider].getValue();
}

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

	gainSlider.setSliderStyle(Slider::LinearBarVertical);
	gainSlider.setRange(1.0, 100.0, 1.0);
	gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	gainSlider.setPopupDisplayEnabled(true, false, this);
	//gainSlider.setTextValueSuffix(" Gain");
	gainSlider.setValue(1.0);

	addAndMakeVisible(&gainSlider);

	volumeSlider.setSliderStyle(Slider::LinearBarVertical);
	volumeSlider.setRange(0.0, 1.0, 0.01);
	volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	volumeSlider.setPopupDisplayEnabled(true, false, this);
	//volumeSlider.setTextValueSuffix(" Volume");
	volumeSlider.setValue(0.1);

	addAndMakeVisible(&volumeSlider);

	gateSlider.setSliderStyle(Slider::LinearBarVertical);
	gateSlider.setRange(0.0, 0.001, 0.00001);
	gateSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	gateSlider.setPopupDisplayEnabled(true, false, this);
	gateSlider.setValue(0.0);

	addAndMakeVisible(&gateSlider);

	gainSlider.addListener(this);
	volumeSlider.addListener(this);
	gateSlider.addListener(this);

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
	//g.drawFittedText("Distortion Plugin", 0, 0, getWidth(), 30, Justification::centred, 1);
	g.drawFittedText("Gain", (int)((getWidth() - 60.0) / 4.0 - 15.0), getHeight() - 30, 50, 30, Justification::centred, 1);
	g.drawFittedText("Volume", (int)(getWidth() / 2.0 - 25.0), getHeight() - 30, 50, 30, Justification::centred, 1);
	g.drawFittedText("Gate", (int)(3.0 * (getWidth() - 60.0) / 4.0 + 25.0), getHeight() - 30, 50, 30, Justification::centred, 1);
}

void HardClippingAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	gainSlider.setBounds((int)((getWidth() - 60.0) / 4.0), 60, 20, getHeight() - 90);
	volumeSlider.setBounds((int)(2.0 * (getWidth() - 60.0) / 4.0 + 20.0), 60, 20, getHeight() - 90);
	gateSlider.setBounds((int)(3.0 * (getWidth() - 60.0) / 4.0 + 40.0), 60, 20, getHeight() - 90);
	distortionList.setBounds(getWidth() / 2 - 100, 15, 200, 30);
}

void HardClippingAudioProcessorEditor::distortionChanged()
{
	processor.distortionAlgorithm = (HardClippingAudioProcessor::DistortionType)distortionList.getSelectedId();
}

void HardClippingAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	processor.gainLevel = gainSlider.getValue();
	processor.volumeLevel = volumeSlider.getValue();
	processor.gateThreshold = gateSlider.getValue();
}

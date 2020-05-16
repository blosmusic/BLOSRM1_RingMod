/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MajorRingModAudioProcessorEditor::MajorRingModAudioProcessorEditor (MajorRingModAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
    sinMixAttach(processor.valueTree, "sinmix", sinMixSlider),
    sinRateAttach(processor.valueTree, "sinrate", sinRateSlider),
    triMixAttach(processor.valueTree, "trimix", triMixSlider),
    triRateAttach(processor.valueTree, "trirate", triRateSlider),
    ioAttach(processor.valueTree, "io", ioButton)
{
    //window size
    setSize (200, 300);
    //slider details
    sinMixSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sinMixSlider.setColour(Slider::thumbColourId, Colours::black);
    addAndMakeVisible(sinMixSlider);
    
    sinRateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sinRateSlider.setColour(Slider::thumbColourId, Colours::black);
    addAndMakeVisible(sinRateSlider);
    
    triMixSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triMixSlider.setColour(Slider::thumbColourId, Colours::black);
    addAndMakeVisible(triMixSlider);
    
    triRateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triRateSlider.setColour(Slider::thumbColourId, Colours::black);
    addAndMakeVisible(triRateSlider);
    
    //power button
    ioButton.setColour(TextButton::ColourIds::buttonColourId, Colours::darkred);
    ioButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red);
    ioButton.setClickingTogglesState(true);
    ioButton.onClick = [this]() {};
    addAndMakeVisible(ioButton);
    
    sinMixSlider.setLookAndFeel(&otherLookAndFeelEQ);
    sinRateSlider.setLookAndFeel(&otherLookAndFeelEQ);
    
    triMixSlider.setLookAndFeel(&otherLookAndFeel);
    triRateSlider.setLookAndFeel(&otherLookAndFeel);
}

MajorRingModAudioProcessorEditor::~MajorRingModAudioProcessorEditor()
{
}

//==============================================================================
void MajorRingModAudioProcessorEditor::paint (Graphics& g)
{
    //background colour
    g.fillAll (Colours::silver);
    //PINK COLOURED ITEMS (DESIGN)
    g.setColour (Colours::hotpink);
    g.fillRect(2.5, 5, 97.5, 180);
    g.setColour (Colours::yellow);
    g.fillRect(102.5, 5, 95, 180);
//    g.fillRect(2.5, 245, 195, 50);
    //GREEN COLOURED ITEMS (DESIGN)
    g.setColour (Colours::darkgreen);
    g.fillRect(2.5, 190, 195, 105);
    //BLACK COLOURED ITEMS (DESIGN)
    g.setColour (Colours::black);
    g.drawEllipse(90, 225, 20, 20, 10);
    g.setColour (Colours::yellow);
    g.setFont (15.0f);
    g.drawFittedText("MIX", 25, 60, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("RATE", 25, 145, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("SINE", 25, 180, 50, 50, Justification::horizontallyCentred , 1);
    g.setColour (Colours::hotpink);
    g.drawFittedText("MIX", 125, 60, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("RATE", 125, 145, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("TRI", 125, 180, 50, 50, Justification::horizontallyCentred , 1);
    g.setFont (30.0f);
    g.drawFittedText ("BLOS FX", 10, 265, 180, 20, Justification::centredBottom , 1);
    g.setColour (Colours::silver);
    g.setFont (15.0f);
    g.drawFittedText ("RM-1", 5, 275, 180, 20, Justification::bottomLeft, 1);
}

void MajorRingModAudioProcessorEditor::resized(){

    //SLIDERS & BUTTONS
    //sin wave
    sinMixSlider.setBounds(20, 15, 60, 60);
    sinMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sinRateSlider.setBounds(20, 100, 60, 60);
    sinRateSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    //tri wave
    triMixSlider.setBounds(120, 15, 60, 60);
    triMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    triRateSlider.setBounds(120, 100, 60, 60);
    triRateSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    
    //power button
    ioButton.setBounds(90, 225, 20, 20);
}

void MajorRingModAudioProcessorEditor::sliderValueChanged(Slider *slider){

}

void MajorRingModAudioProcessorEditor::comboBoxChanged(ComboBox *comboBox){

}



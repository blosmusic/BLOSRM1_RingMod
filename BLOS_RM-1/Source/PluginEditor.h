/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
class OtherLookAndFeel : public LookAndFeel_V4{
public:
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override {
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::darkgreen);
        g.fillEllipse (rx, ry, rw, rw);
         
        // outline
        g.setColour (Colours::hotpink);
        g.drawEllipse (rx, ry, rw, rw, 2.0f);
        
        Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::hotpink);
        g.fillPath (p);
    }
};
//==============================================================================
class OtherLookAndFeelEQ : public LookAndFeel_V4{
public:
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override {
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::darkgreen);
        g.fillEllipse (rx, ry, rw, rw);
         
        // outline
        g.setColour (Colours::yellow);
        g.drawEllipse (rx, ry, rw, rw, 2.0f);
        
        Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::yellow);
        g.fillPath (p);
    }
};
//==============================================================================
class MajorRingModAudioProcessorEditor  : public AudioProcessorEditor,
public Slider::Listener, public ComboBox::Listener
{
public:
    MajorRingModAudioProcessorEditor (MajorRingModAudioProcessor&);
    ~MajorRingModAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider *slider) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* button);
    
    OtherLookAndFeel otherLookAndFeel;
    OtherLookAndFeelEQ otherLookAndFeelEQ;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MajorRingModAudioProcessor& processor;
    
    //sliders for control dials
    Slider sinMixSlider;
    Slider sinRateSlider;
    Slider triMixSlider;
    Slider triRateSlider;
    
    TextButton ioButton;
    
    //slider attachment for valueTrees **will destruct first**
    AudioProcessorValueTreeState::SliderAttachment sinMixAttach;
    AudioProcessorValueTreeState::SliderAttachment sinRateAttach;
    AudioProcessorValueTreeState::SliderAttachment triMixAttach;
    AudioProcessorValueTreeState::SliderAttachment triRateAttach;
    AudioProcessorValueTreeState::ButtonAttachment ioAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MajorRingModAudioProcessorEditor)
};

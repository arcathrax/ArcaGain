#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/ArcaGainLookAndFeel.h"


class ArcaGainAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ArcaGainAudioProcessorEditor (ArcaGainAudioProcessor&);
    ~ArcaGainAudioProcessorEditor() override;


    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ArcaGainLookAndFeel lookAndFeel;
    ArcaGainAudioProcessor& audioProcessor;
    
    juce::Label titleLabel;
    
    juce::Slider gainSlider;
    juce::AudioProcessorValueTreeState::SliderAttachment gainSliderAttachment
    {
        audioProcessor.apvts, "Gain", gainSlider
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArcaGainAudioProcessorEditor)
};

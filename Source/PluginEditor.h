#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class ArcaGainAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ArcaGainAudioProcessorEditor (ArcaGainAudioProcessor&);
    ~ArcaGainAudioProcessorEditor() override;


    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ArcaGainAudioProcessor& audioProcessor;
    
    juce::Slider gainSlider;
    juce::AudioProcessorValueTreeState::SliderAttachment gainSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArcaGainAudioProcessorEditor)
};

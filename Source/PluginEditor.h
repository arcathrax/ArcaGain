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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ArcaGainAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArcaGainAudioProcessorEditor)
};

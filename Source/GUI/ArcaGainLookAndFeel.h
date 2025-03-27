#pragma once
#include <JuceHeader.h>

class ArcaGainLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ArcaGainLookAndFeel();
    static ArcaGainLookAndFeel* get()
    {
        static ArcaGainLookAndFeel instance;
        return &instance;
    }
    
    void drawLinearSlider (juce::Graphics&, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           juce::Slider::SliderStyle, juce::Slider&) override;
private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArcaGainLookAndFeel)
};

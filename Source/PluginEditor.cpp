#include "PluginProcessor.h"
#include "PluginEditor.h"


ArcaGainAudioProcessorEditor::ArcaGainAudioProcessorEditor (ArcaGainAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    titleLabel.setText("ArcaGain", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    
    gainSlider.setLookAndFeel(&lookAndFeel);
    
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(gainSlider);
    setSize (400, 300);
}

ArcaGainAudioProcessorEditor::~ArcaGainAudioProcessorEditor()
{
}


void ArcaGainAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void ArcaGainAudioProcessorEditor::resized()
{
    auto fullBounds = getBounds();
    auto titleBounds = fullBounds.removeFromTop(fullBounds.getHeight()*0.25);
    auto sliderBounds = fullBounds;
    
    titleLabel.setBounds(titleBounds);
    gainSlider.setBounds(sliderBounds);
}

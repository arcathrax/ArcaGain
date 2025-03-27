#include "PluginProcessor.h"
#include "PluginEditor.h"


ArcaGainAudioProcessorEditor::ArcaGainAudioProcessorEditor (ArcaGainAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
gainSliderAttachment(audioProcessor.apvts, "Gain", gainSlider)
{
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
    gainSlider.setBounds(getBounds());
}

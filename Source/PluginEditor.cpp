#include "PluginProcessor.h"
#include "PluginEditor.h"


ArcaGainAudioProcessorEditor::ArcaGainAudioProcessorEditor (ArcaGainAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
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
}

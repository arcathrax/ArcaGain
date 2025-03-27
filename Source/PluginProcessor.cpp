#include "PluginProcessor.h"
#include "PluginEditor.h"


ArcaGainAudioProcessor::ArcaGainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),params(apvts)
#endif
{
}

ArcaGainAudioProcessor::~ArcaGainAudioProcessor()
{
}


const juce::String ArcaGainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ArcaGainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ArcaGainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ArcaGainAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ArcaGainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ArcaGainAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ArcaGainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ArcaGainAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ArcaGainAudioProcessor::getProgramName (int index)
{
    return {};
}

void ArcaGainAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


void ArcaGainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    spec.sampleRate = sampleRate;

    leftChain.prepare(spec);
    rightChain.prepare(spec);
}

void ArcaGainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ArcaGainAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ArcaGainAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    
    juce::dsp::AudioBlock<float> block(buffer);
    
    auto& leftGainProcessor = leftChain.template get<GainProcessorIndex>();
    auto& rightGainProcessor = rightChain.template get<GainProcessorIndex>();
    
    float gain = params.gainParam->get();
    
    leftGainProcessor.setGainDecibels(gain);
    rightGainProcessor.setGainDecibels(gain);
    
    juce::dsp::ProcessContextReplacing<float> context(block);
    
    leftChain.process(context);
    rightChain.process(context);
}


bool ArcaGainAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ArcaGainAudioProcessor::createEditor()
{
    return new ArcaGainAudioProcessorEditor(*this);
    // return new juce::GenericAudioProcessorEditor(*this);
}


void ArcaGainAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void ArcaGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        apvts.replaceState(tree);
    }
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ArcaGainAudioProcessor();
}

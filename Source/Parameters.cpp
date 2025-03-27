#include "Parameters.h"

static juce::String stringFromDecibels(float value, int)
{
return juce::String(value, 1) + " dB";
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    auto* param = apvts.getParameter(gainParamID.getParamID());
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(param);
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    auto parameter = std::make_unique<juce::AudioParameterFloat>
    (
        gainParamID,
        "Gain",
        juce::NormalisableRange<float>
        (
            -12.f,
            24.0f,
            0.000001f,
            1.25f
        ),
        0.f,
     juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)
    );;

    auto parameters = std::make_unique<
        juce::AudioProcessorParameterGroup>(
            "parameters",
            "PARAMETERS",
            "|",
            std::move(parameter)
        );

    layout.add
    (
        std::move(parameters)
    );

    return layout;
}

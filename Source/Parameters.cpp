#include "Parameters.h"

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    auto* param = apvts.getParameter(gainParamID.getParamID());
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(param);
}


juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    auto parameter = std::make_unique<juce::AudioParameterFloat>(
        gainParamID,
        "Gain",
        juce::NormalisableRange<float>
        (
            0.75f,
            12.0f,
            0.000001f,
            0.5f
        ),
        1.0f
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

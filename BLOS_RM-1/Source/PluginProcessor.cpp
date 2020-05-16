/*
  ==============================================================================
 BLOS RM-1 Ring Modulator submitted as part of the Masters in Music program in DKIT
 
 References for code in this project are based on examples from the following:
 
 "Audio Effects: Theory, Implementation and Application" by Joshua D. Reiss and Andrew P. McPherson.
 https://ccrma.stanford.edu/~dattorro/EffectDesignPart2.pdf
 "Introduction to Signal Processing" by Sophocles J. Orfanidis

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MajorRingModAudioProcessor::MajorRingModAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
, valueTree(*this, nullptr, "PARAMETERS",
AudioProcessorValueTreeState::ParameterLayout(
    std::make_unique<AudioParameterBool>("io", "IO", true),
    std::make_unique<AudioParameterFloat>("sinrate", "SINRATE", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
    std::make_unique<AudioParameterFloat>("sinmix", "SINMIX", NormalisableRange<float>(20.0f, 100.0f), 50.0f),
    std::make_unique<AudioParameterFloat>("trirate", "TRIRATE", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
    std::make_unique<AudioParameterFloat>("trimix", "TRIMIX", NormalisableRange<float>(0.1f, 1.0f), 0.5f)))
{
}

MajorRingModAudioProcessor::~MajorRingModAudioProcessor()
{
    //create log to save setings between uses
    valueTree.state = ValueTree("SavedParameters");
}

//==============================================================================
const String MajorRingModAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MajorRingModAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MajorRingModAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MajorRingModAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MajorRingModAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MajorRingModAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MajorRingModAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MajorRingModAudioProcessor::setCurrentProgram (int index)
{
}

const String MajorRingModAudioProcessor::getProgramName (int index)
{
    return {};
}

void MajorRingModAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MajorRingModAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //==============================================================================

}

void MajorRingModAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MajorRingModAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

//==============================================================================
void MajorRingModAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //Check number of channels ***DO NOT TOUCH***
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer (channel);
            
            //Parameters for ring modulator
            for (int i = 0; i < buffer.getNumSamples(); i++){
                
                //ring mod parameters
                float sinrate = valueTree.getParameter("sinrate")->getValue(); //rate of ring mod for sinWave
                float trirate = valueTree.getParameter("trirate")->getValue(); //rate of ring mod for triWave
                //wave lengths
                float phase = (MathConstants<float>::twoPi * i) / buffer.getNumSamples();
                float sinWave = sin(phase*int(sinrate*10)) * valueTree.getParameter("sinmix")->getValue();
                float triWave = (-1 + (sin(2 * (phase*int(trirate*10)))) / (2 * float_Pi)) * valueTree.getParameter("trimix")->getValue();
                float io = valueTree.getParameter("io")->getValue();
                
                //io decides whether FX is live or not
                if(io == 1){
                    //output signal ring modulator
                    channelData[i] = channelData[i] + (sinWave * channelData[i]) + ((2 * triWave) * channelData[i]);
                } else{ channelData[i] = channelData[i]; }
            }
    }
}

//==============================================================================
bool MajorRingModAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MajorRingModAudioProcessor::createEditor()
{
    return new MajorRingModAudioProcessorEditor (*this);
}

//==============================================================================
void MajorRingModAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // log XML to save values to
    std::unique_ptr  <XmlElement> xml (valueTree.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MajorRingModAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // recall xml when reopening plugin
    std::unique_ptr  <XmlElement> reloadXml (getXmlFromBinary(data, sizeInBytes));
    if (reloadXml != nullptr){
        if (reloadXml -> hasTagName(valueTree.state.getType())){
            valueTree.state = ValueTree::fromXml(*reloadXml);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MajorRingModAudioProcessor();
}

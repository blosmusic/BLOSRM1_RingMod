# BLOSRM1_RingMod

This plugin simulates a ring modulator with two wavelengths at the users disposal.

### INSTALLATION

To install & use, place the VST file into the plugin directory of your chosen DAW.

In your chosen DAW, add the VST to your signal chain.

Set your parameters and play!

NOTE: Some DAWs may require you to refresh the VST path before using.

### GENERAL

This plugin takes audio as input, you can use existing audio samples or place the VST into your recording chain.

### BLOS RM-1 - Ring Modulator

This plugin simulates a ring modulator with two wavelengths at the users disposal.
The rate control for each waveform controls the level of oscillation and intensity of the effect.
The mix dials act as a blend between the clean signal and each wavelength.
By blending small amounts of each wavelength the user can get a tremolo effect or using a large amount to acheive a robotic chime.

### DEMO

A demonstration of the VSTs can be found [here](https://www.youtube.com/watch?v=gu4198DzCO4&t=1s).

### HOW IT WORKS

Taking audio input the RM-1 blends the signal controlled by each mix dial with a sine and/or triangle waveform. The mix is done as the modulating signal is added to the original signal. Similarly, each waveform is controlled by the parameters rate dial which is multiplied by the phase to create the effect.

The processing for this is achieved in the processBlock (PluginProcessor.cpp) where the mix and waveform amount are called by each parameters valuetree. The valueTree for each parameter ties the required parameter with the respective GUI control. In addition, the inclusion and state of the I/O button gives the user the option to either use the VST or bypass it in their signal chain as per their use. This is typical of how a stompbox FX on/off would work.

For user simplification, the XML code in setStateInformation (PluginProcessor.cpp) is used to retain the VSTs settings between sessions or uses. 

The GUI is setup up to echo a typical guitar VST outline with each waveform outlined by its coloured section (sine wave left in the pink box, triangle wave right in the yellow box), this also includes a custom slider class which makes the VST appear more like a pedal as described.

### CONTRIBUTING

If you would like to contribute to this repository, please contact me first via [email](hi@benlambosullivan.com).
This repository does not include the builds folder for JUCE, as such contributions would need to be built via Projucer first.

### LICENSE

This project was developed under the [General Public License (GNU)](https://www.gnu.org/licenses/gpl-3.0.en.html)

### ACKNOWLEDGEMENTS

These VSTs were developed for submission as part of a submission for the [Masters in Music Technology](https://www.dkit.ie/courses/school-of-informatics-and-creative-arts/creative-arts-media-and-music/ma/msc-in-music-technology.html) in Dundalk Institute of Technology, Ireland.

Special thanks to the courses lecturer Rory Walsh for his help & input.

Further resources which assisted the development of this project:

[The Audio Programmer YouTube Channel](https://www.youtube.com/theaudioprogrammer)

[JUCE Tutorials](https://juce.com/learn/tutorials)




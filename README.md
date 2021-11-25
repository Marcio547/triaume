# Triaume - An augmented triangle
### by  Marcio Albano Hermelino Ferreira

### Introduction

In this project, we used capacitive sensing techniques to test new
musical gesture possibilities for an triangle - an old instrument
that is widely used on Brazilian traditional music.

Our goal is the development of  a non-invaisve instrument augmenting approach,
that could retain the triangle acoustic sounds, but giving additional functionalities to it through digital sound synthesis

This project was developed as my Master Thesis and I published an article that was presented in the 15th International Symposium on Computer Music Multidisciplinary Research. You can check a short video demonstration [here](https://youtu.be/M-RomVwF37w)

### Resources

On its most recent version, the following materials were used:

- ESP32 board

- 1MOhm resistor.

- Alligator clips and jumper cables.

- Insulating tape

- Copper adhesive tape

## Requirements
  This project worked using this requirements list. Maybe it will work with other versions, but different versions were not tested.

 - Arduino IDE 1.8.15 - Libraries CapacitiveSensor (version with support to ESP32) and SLIPEncodedSerial (from CNMAT).
 - pd 0.51.3. Certainly required externals: comport, cyclone, freeverb, mrpeach, zexy.
 - MobMuPlat v 0.36 (if desired for using smartphone control)


 List of all externals that I installed. Maybe some of them are not being really used, but it can be used as a reference in case of problems.
 - bob~, bonk~, choice, comport, cyclone, fiddle~ freeverb~-1.2, loop~, lrshift~, mrpeach, pd~, pique, sigmund~, stdout, zexy.


### How to use

- Open the CapSensorESP32Wifi.ino sketch inside the folder with same name with the ArduinoIDE and run it.

- Run the triaume_main.pd patch inside the Modules folder.

- Check the name of the USB port being used for the Arduino. Change the name of the port inside the OSCReceiver patch. It is possible to check ports available using the 'devices' message on this patch. After the a

- Run through the modules and mark all checkboxes to observe the waves, if necessary.

- Ajust the faders for volume before turning DSP on in pure data.

- Install mobmuplat on your smartphone.

- Copy the files triaume_control.mmp and triaume_control.pd to the mobmuplat folder. (Probably in Android smartphones should be located inside /storage/emulated/0/MobMuPlat). For using smartphone control, run the triaume_control.mmp inside MobMuPlat.

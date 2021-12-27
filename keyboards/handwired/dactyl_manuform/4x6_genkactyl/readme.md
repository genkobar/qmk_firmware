# 4x6 Genkactyl

![4x6_genkactyl](imgur.com image replace me!)

A compact variation of the Dactyl-Manuform, but still with enough keys for Scandinavian languages. 
Thumb cluster designed by Carbonfet.

* Keyboard Maintainer: [Valdimar Björn Ásgeirsson](https://github.com/genkobar)
* Hardware Supported: Handwired, Pro Micro and similar
* Hardware Availability: Anything that works with a pro micro

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_manuform/4x6_genkactyl:default

Flashing example for this keyboard:

    make handwired/dactyl_manuform/4x6_genkactyl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Design

The main concerns while designing this keyboard were:

- having enough keys for the Icelandic input layout, which has dedicated keys for the letters `ð`, `þ`, `æ`, `ö` and the acute one-shot modifier `´`
- removing the number row to minimize the footprint of the keyboard

## 3D Printing

The code for generating the model to print this keyboard with a 3D printer can be found at https://github.com/genkobar/dactyl-manuform.
I printed mine on a Prusa MK3S+ in Prusament "Galaxy Black" filament, with a layer height of 0.2 mm.

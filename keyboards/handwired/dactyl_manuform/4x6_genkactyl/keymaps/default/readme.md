# The default keymap for 4x6_genkactyl

This keyboard is [a configuration of Carbonfet's fork](https://github.com/genkobar/dactyl-manuform) of the Dactyl Manuform.

The main concerns were:

- having enough keys for the Icelandic input layout, which has dedicated keys for the letters `ð`, `þ`, `æ`, `ö` and the acute one-shot modifier `´`
- removing the number row to minimize the footprint of the keyboard

### Number & Symbol Layer

To access numbers, hold the NUMSYM-layer key in the bottom left of the left thumb cluster. The numbers are laid out like a keypad on the right side, while symbols are on the left side. 

Various other functionality has been added to this layer to avoid having too many layers.
### Ctrl-Escape

Karabiner-Elmenents has stopped working for me on Big Sur, so I ended up defining this binding via QMK. All instances of the Ctrl key on this keyboard send Ctrl when held but Escape when tapped.

### OS Functions Layer 

This is sort of the catch-all layer for remaining stuff. Here we have the arrow keys positioned where they are in Vim, volume and media controls, F1 - F12 keys and also mouse movement keys.
 
#### Handy Browser Tab Switching

The OSFunc layer also has dedicated keys that send command-alt-left and command-alt-right, which are the shortcuts used to switch tabs in the Firefox browser.

### Halmak Layer
I decided to try learning the Halmak layout, so it's available as the second layer. You can toggle it on and off via the OSFUNC layer. 

Since this layer doesn't change the keys that the Icelandic-only keys are on, they will remain in the same place on both Qwerty and Halmak.

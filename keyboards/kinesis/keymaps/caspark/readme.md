# Caspar's Kinesis Advantage keymap

Inspired by https://asylum.madhouse-project.org/blog/2016/10/15/multi-purpose-keys/
and by http://www.pvv.org/~hakonhal/main.cgi/keyboard/arensito_devel/
and https://github.com/qmk/qmk_firmware/tree/master/keyboards/kinesis/keymaps/tuesdayjohn

# What does it have?

It's easiest to look at keymap.c to see the full mapping, but in short:

* Base layer:
  * Colemak layout for alphanumerics
  * hit `prgrm` key to reset keyboard (prepare it to be flashed)
  * Delete on left thumb cluster sends Esc on tap and Ctrl on hold.. unless CapsLock is pressed while it is held, in which case it acts like Alt+Tab
  * a bunch of non-alphanumeric keys have been moved around, especially on the thumb clusters - check the keymap :)
* Symbol layer (hold Enter on right thumb cluster):
  * function keys on number row
  * symbols on home row, focusing on those symbols which are common (per http://xahlee.info/comp/computer_language_char_distribution.html ) but not easily accessible
  * right hand also has access to 0/1 on middle finger
* Edit layer for editing text (hold Ctrl on left thumb cluster):
  * right hand has arrow keys plus home/end in an almost traditional arrow cluster
  * right hand also has shortcuts to move up/down lines faster, move by words, jump to start/end, etc
  * left hand has traditional arrow cluster too but all movement modifies selection (i.e. as if shift is held)
  * left hand also has Ctrl+Z/X/C/V on those keys, and Redo on B
  * backspace and delete both delete whole words instead of individual characters
* GUI layer for interacting with GUI apps (hold CapsLock)
  * left hand has mouse keys

TODO:

* make capslock LED turn on when a one shot modifier key is triggered
* add a qwerty layout that exactly matches what's on the keyboard, to make keyboard usable by others

## Developing

Set up vscode tasks:

```bash
cat > .vscode/tasks.json <<EOF
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "qmk compile",
            "type": "shell",
            "command": "qmk compile",
            "problemMatcher": [],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
EOF
```

Then hit `control+shift+b` in vscode to compile QMK.

To flash:

* download the Teensy loader from https://pjrc.com/teensy/loader.html
* start teensy loader
* hit RESET key on keyboard to fire up bootloader (or short GND and RST pins on the board)
* the keyboard will "disconnect" and any leds on the board will turn off as the halfkay bootloader runs
* teensy loader should recognise the board and change its little graphic display
* hit the flash button on teensy loader and wait for the keyboard to be flashed
* hit the reboot button on teensy loader
* the keyboard will "reconnect" and the keyboard should now work again

Once this has been flashed once, bootmagic-lite will be enabled, so you can also enter the bootloader
by holding the top-left-most key on the left keywell (`+/=` on the qwerty keymap) while plugging the
keyboard in.

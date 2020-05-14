# Caspar's keymap

Inspired by https://asylum.madhouse-project.org/blog/2016/10/15/multi-purpose-keys/
and by http://www.pvv.org/~hakonhal/main.cgi/keyboard/arensito_devel/
and https://github.com/qmk/qmk_firmware/tree/master/keyboards/kinesis/keymaps/tuesdayjohn

TODO:

* make capslock LED turn on when a one shot modifier key is triggered
* add a "true escape" button that resets turns off all layers except the base layer
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

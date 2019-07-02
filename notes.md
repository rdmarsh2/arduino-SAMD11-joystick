# Notes on USB HID

## Useful Links
### Specs
[USB HID Definition](https://www.usb.org/sites/default/files/documents/hid1_11.pdf)

[USB HID Usage Tables](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf)
### Tools
[USB HID Report Parser](https://eleccelerator.com/usbdescreqparser/)
## Definition
Following the format of the coding sample on page 25 of the HID Definition
```
Usage Page (Generic Desktop),
Usage(Game Pad),                                        ; An arcade-style joystick probably doesn't actually meet the requirements for a joystick?
    Collection(Application),
        Usage(Pointer),
            Collection(Physical),
            Usage(X),
            Usage(Y),
            Logical Minimum(-1),
            Logical Maximum(1),
            Report Count(2),
            Report Size(2),
            Input(Data, Variable, Absolute, No Null),   ; 2-bit signed integer X axis
        End Collection(),
        Usage Minimum(D-Pad Up),
        Usage Maximum(D-Pad Left),
        Report Count(4),
        Report Size(1),
        Input(Data, Variable, Absolute),                ; are the D-Pad buttons necessary in practice?
        Usage Page (Buttons),
        Usage Minimum (1),
        Usage Maximum (12),
        Logical Minimum(0),
        Logical Maximum(1),
        Report Count(12),
        Report Size(1),
        Input(Data, Variable, Absolute)
        Report Count(1),
        Report Size(4),
        Input(Constant),
    End Collection,
End Collection
```

## Relevant Codes

| Uasage Page | Code |
|-------|------|
| Generic Desktop | `0x01` |
| Button page     | `0x09` |

| Usage       | Page | Code   |
|-------------|-----------------|--------|
| Joystick    | Generic Desktop | `0x04` |
| Game Pad    | Generic Desktop | `0x05` |
| Pointer     | Generic Desktop | `0x01` |
| X           | Generic Desktop | `0x30` |
| Y           | Generic Desktop | `0x31` |
| Start       | Generic Dektop  | `0x3D` |
| Select      | Generic Desktop | `0x3E` |
| D-Pad Up    | Generic Desktop | `0x90` |
| D-Pad Down  | Generic Desktop | `0x91` |
| D-Pad Left  | Generic Desktop | `0x92` |
| D-Pad Right | Generic Desktop | `0x93` |

| Type          | Code |
|---------------|------|
| Main          | `1`  |
| Global        | `2`  |
| Local         | `3`  |
| Reserved      | `4`  |

| Tag              | Bits         | Hex (First Byte and 0 size) |
|------------------|--------------|--------|
| Input            | `1000 00 nn` | `0x80` |
| Output           | `1001 00 nn` | `0x90` |
| Feature          | `1011 00 nn` | `0xA0` |
| Collection       | `1010 00 nn` | `0xB0` |
| End Collection   | `1100 00 nn` | `0xC0` |
| Usage Page       | `0000 01 nn` | `0x04` |
| Logical Minimum  | `0001 01 nn` | `0x14` |
| Logical maximum  | `0010 01 nn` | `0x24` |
| Report Size      | `0111 01 nn` | `0x74` |
| Report Count     | `1001 01 nn` | `0x94` |
| Usage            | `0000 10 nn` | `0x08` |
| Usage Minimum    | `0001 10 nn` | `0x18` |
| Usage Maximum    | `0010 10 nn` | `0x28` |

C Array body
```
0x05, 0x01, // Usage Page (Generic Desktop),
0x09, 0x05, // Usage(Game Pad),
0xA1, 0x01, // Collection(Application),
    0x09, 0x01, // Usage(Pointer),
        0xA1, 0x00, // Collection(Physical),
        0x09, 0x30, // Usage(X),
        0x09, 0x31, // Usage(Y),
        0x15, 0xFF, // Logical Minimum(-1),
        0x25, 0x01, // Logical Maximum(1),
        0x95, 0x02, // Report Count(2),
        0x75, 0x01, // Report Size(2),
        0x81, 0x42, // Input(Data, Variable, Absolute, No Null), 
    0xC0, // End Collection(),
    0x19, 0x90, // Usage Minimum(D-Pad Up),
    0x29, 0x93, // Usage Maximum(D-Pad Left),
    0x95, 0x04, // Report Count(4),
    0x75, 0x01, // Report Size(1),
    0x81, 0x02, // Input(Data, Variable, Absolute),
    0x05, 0x09, // Usage Page (Buttons),
    0x19, 0x01, // Usage Minimum (1),
    0x29, 0x0C, // Usage Maximum (12),
    0x15, 0x00, // Logical Minimum(0),
    0x25, 0x01, // Logical Maximum(1),
    0x95, 0x0C, // Report Count(12),
    0x75, 0x01, // Report Size(1),
    0x81, 0x02, // Input(Data, Variable, Absolute)
    0x95, 0x01, // Report Count(1),
    0x75, 0x04, // Report Size(4),
    0x81, 0x01, // Input(Constant),
0xC0, // End Collection,
```

## Report Format

| Byte |7|6|5|4|3|2|1|0|
|:------:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0| D-Pad Right | D-Pad Left | D-Pad Down | D-Pad Up | Pointer Y || Pointer X ||
|1| Button 8 | Button 7 | Button 6 | Button 5 | Button 4 | Button 3 | Button 2 | Button 1
|2 | Pad |||| Button 12 | Button 11 | Button 10 | Button 9

#include "HID.h"
#include "pins.h"

#if !defined(_USING_HID)

#error "Using legacy HID core (non pluggable)"

#else

static const uint8_t _hidReportDescriptor[] PROGMEM = {
  0x05, 0x01, // Usage Page (Generic Desktop),
  0x09, 0x05, // Usage(Game Pad),
  0xA1, 0x01, // Collection(Application),
      0x85, 0x03, // Report ID(3),
      0x09, 0x01, // Usage(Pointer),
      0xA1, 0x00, // Collection(Physical),
          0x09, 0x30, // Usage(X),
          0x09, 0x31, // Usage(Y),
          0x15, 0xFF, // Logical Minimum(-1),
          0x25, 0x01, // Logical Maximum(1),
          0x95, 0x02, // Report Count(2),
          0x75, 0x02, // Report Size(2),
          0x81, 0x02, // Input(Data, Variable, Absolute, No Null), 
      0xC0, // End Collection(),
      0x95, 0x01, // Report Count(1),
      0x75, 0x04, // Report Size(4),
      0x81, 0x01, // Input(Constant),
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
  0xC0 // End Collection
};

// TODO: bitfields?
struct Report {
  uint8_t dpad;
  uint8_t buttons_1;
  uint8_t buttons_2;
};

void setup() {
  pinMode(JOYSTICK_UP, INPUT_PULLUP);
  pinMode(JOYSTICK_DOWN, INPUT_PULLUP);
  pinMode(JOYSTICK_LEFT, INPUT_PULLUP);
  pinMode(JOYSTICK_RIGHT, INPUT_PULLUP);

  // these are one-indexed for USB reasons
  pinMode(BUTTON_1,  INPUT_PULLUP);
  pinMode(BUTTON_2,  INPUT_PULLUP);
  pinMode(BUTTON_3,  INPUT_PULLUP);
  pinMode(BUTTON_4,  INPUT_PULLUP);
  pinMode(BUTTON_5,  INPUT_PULLUP);
  pinMode(BUTTON_6,  INPUT_PULLUP);
  pinMode(BUTTON_7,  INPUT_PULLUP);
  pinMode(BUTTON_8,  INPUT_PULLUP);
  pinMode(BUTTON_9,  INPUT_PULLUP);
  pinMode(BUTTON_10, INPUT_PULLUP);
  pinMode(BUTTON_11, INPUT_PULLUP);
  pinMode(BUTTON_12, INPUT_PULLUP);

  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
}

void loop() {
  static uint8_t count = 0;
  Report report;
  report.dpad = dpad(!digitalRead(JOYSTICK_UP),
                     !digitalRead(JOYSTICK_DOWN),
                     !digitalRead(JOYSTICK_LEFT),
                     !digitalRead(JOYSTICK_RIGHT));

  report.buttons_1 = 0;
  report.buttons_1 |= !digitalRead(BUTTON_1);
  report.buttons_1 |= !digitalRead(BUTTON_2) << 1;
  report.buttons_1 |= !digitalRead(BUTTON_3) << 2;
  report.buttons_1 |= !digitalRead(BUTTON_4) << 3;
  report.buttons_1 |= !digitalRead(BUTTON_5) << 4;
  report.buttons_1 |= !digitalRead(BUTTON_6) << 5;
  report.buttons_1 |= !digitalRead(BUTTON_7) << 6;
  report.buttons_1 |= !digitalRead(BUTTON_8) << 7;

  report.buttons_2 = 0;
  report.buttons_2 |= !digitalRead(BUTTON_9);
  report.buttons_2 |= !digitalRead(BUTTON_10) << 1;
  report.buttons_2 |= !digitalRead(BUTTON_11) << 2;
  report.buttons_2 |= !digitalRead(BUTTON_12) << 3;
  
  HID().SendReport(3, &report, sizeof(report));
  
  delay(1);
}

// {up, down, left, right} must all be either 0 or 1
uint8_t dpad(uint8_t up, uint8_t down, uint8_t left, uint8_t right) {
  uint8_t Y = up - down;
  uint8_t X = left - right;
  uint8_t axes = X & 3 | (Y & 3) << 2;
  return axes;
}

#endif

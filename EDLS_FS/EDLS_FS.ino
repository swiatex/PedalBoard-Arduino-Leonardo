#include <MIDIUSB.h>

// Define the pins for each footswitch
const int footswitchPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16}; // Adjust pin numbers as needed
const int numFootswitches = 10;
byte programChanges[] = {4,4,3,3,2,2,1,1,0,0};
const int ddelay = 200;

bool previousStates[numFootswitches] = {LOW}; // Assume all footswitches are initially pressed
bool realSwitchState[numFootswitches] = {LOW};


byte channel = 0;

void setup() {
  for (int i = 0; i < numFootswitches; ++i) {
    pinMode(footswitchPins[i], INPUT_PULLUP);
  }
}

void loop() {

  for (int i = 0; i < numFootswitches; i=i+2) {
    // Read the current state of the footswitch
    bool currentState = digitalRead(footswitchPins[i]);

    // Check if the state has changed
    if (currentState != previousStates[i]) {
      if (currentState == HIGH) { // Footswitch is released
            //  midiEventPacket_t ccOff = {0x0B, 0xB0 | 0, 20 + i, 0}; // Change the CC number (10 + i) as needed
        // MidiUSB.sendMIDI(ccOff);
        programChange(channel, programChanges[i]); 
        delay(ddelay);         
      } else { // Footswitch is pressed
            // midiEventPacket_t ccOn = {0x0B, 0xB0 | 0, 20 + i, 127}; // Change the CC number (10 + i) and value (127) as needed
        // MidiUSB.sendMIDI(ccOn);     
        programChange(channel, programChanges[i]); 
        delay(ddelay);           
      }
      // Update the previous state
      previousStates[i] = currentState;      
    }
  }

  for (int i = 3; i < numFootswitches; i=i+2) {
    // Read the current state of the footswitch
    bool currentState = digitalRead(footswitchPins[i]);

    // Check if the state has changed
    if (currentState != previousStates[i]) {
      if (currentState == LOW) { // Footswitch is released
        if (realSwitchState[i] == LOW) {
             realSwitchState[i] = HIGH; 
             midiEventPacket_t ccOff = {0x0B, 0xB0 | 0, 20 + i, 0}; // Change the CC number (10 + i) as needed
             MidiUSB.sendMIDI(ccOff);
             delay(ddelay);         
      } else { // Footswitch is pressed
            realSwitchState[i] = LOW; 
            midiEventPacket_t ccOn = {0x0B, 0xB0 | 0, 20 + i, 127}; // Change the CC number (10 + i) and value (127) as needed
            MidiUSB.sendMIDI(ccOn);     
            delay(ddelay);           
      }
      // Update the previous state
      
      }
      previousStates[i] = currentState;    
    }
  }





  int i = 1;
    bool currentState = digitalRead(footswitchPins[i]);

    // Check if the state has changed
    if (currentState != previousStates[i]) {
      if (currentState == HIGH) { // Footswitch is released
             midiEventPacket_t ccOff = {0x0B, 0xB0 | 0, 20 + i, 0}; // Change the CC number (10 + i) as needed
        MidiUSB.sendMIDI(ccOff);
        // programChange(channel, programChanges[i]); 
        delay(ddelay);         
      } else { // Footswitch is pressed
            midiEventPacket_t ccOn = {0x0B, 0xB0 | 0, 20 + i, 127}; // Change the CC number (10 + i) and value (127) as needed
        MidiUSB.sendMIDI(ccOn);     
        // programChange(channel, programChanges[i]); 
        delay(ddelay);           
      }
      // Update the previous state
      previousStates[i] = currentState;      
    }
  


  // Poll USB MIDI events
  MidiUSB.flush();
}

void programChange(byte channel, byte patch) {
  midiEventPacket_t event = {0x0C, 0xC0 | channel, patch};
  MidiUSB.sendMIDI(event);
}

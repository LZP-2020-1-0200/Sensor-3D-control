# Sensor-3D-control
Programmambe sensor stage


## SCPI reference

### `*IDN?`

Prints identificator.

### `*RST`

Resets the state without restarting the entire module.

### `motor?`

prints all motor coordinates

Format: `<x> <y> <z>`

### `motor [X|Y|Z] `_`val`_

Sets the target coordinate to all motors or one motor specifically to _`val`_ switches state to 'targeting'

### `motor:lock?`

Prints out all motor lock states.

Format: `<1|0> <1|0> <1|0>`

Only prints `0` if that motor is completely unlocked, otherwise `1`

### `motor:lock [X|Y|Z] <ON|OFF>`

Locks/unlocks one or all motors.

Overrides any previous action that motors were doing. Both `ON` and `OFF` will stop the stepper(s) in their tracks

### `motor:state?`

Prints out the state of all motors.

Format: `<X.state> <Y.state> <Z.state>`

|State number|State name| Description |
|--|--|--|
|0|Disabled|The stepper is disabled (all magnets are off).|
|1|Idle|The stepper isn't moving, however some of the magnets are enabled and lock it in place.|
|2|Homing| The stepper is attempting to locate the start switch to reset it's internal coordinate system. Coordinate system resets only after the homing sequence is complete.|
|3|Targeting| The stepper is performing the targeting sequence.|

### `motor:state:default?`

Prints out the default state of all motors.

Format: `<default_state>`

States similar to `motor:state?` but prints out the default state instead of the current state.
State can be only 0 (Disabled) or 1 (Idle)

### `motor:state:default <0|1>`

Sets the default state of all motors.

State can be only 0 (Disabled) or 1 (Idle)


### `motor:end:<X|Y|Z>?`

prints out end switch status for specified axis.

Format: `<start> <end>`

`1` - switch triggered
`0` - switch not triggered

### `home`

Sets mode to 'homing' for all motors.

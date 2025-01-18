# RC4 Cipher
## Overview
This program is an implementation of the RC4.

https://en.wikipedia.org/wiki/RC4

## Build
Use the following command to build the program:
```
./build.sh
```

## Usage
To encrypt a string:
```
./bin/rc4 -k Secret -e "Attack at dawn"
```

The above command returns:
```
45A01F645FC35B383552544B9BF5
```

To decrypt a string:
```
./bin/rc4 -k Secret -d 45A01F645FC35B383552544B9BF5
```

The above command returns:
```
Attack at dawn
```

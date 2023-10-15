# 6502-processor-emulator

it's an emulator for a variation of the MOS Technology 6502 processor used in the NES console, only official instructions were implemented and they passed the [nestest](https://www.qmtpro.com/~nes/misc/nestest.txt) test.

When the emulator runs, it will log its registers values after every instruction to the command line and to a log file inside the directory `log`. This emulator doesn't have any graphical output as it is only a processor emulator.

## Compile and run

to compile it:

```bash
make
```
to compile it with tests:

```bash
make test
```
to run it:

```bash
./6502-processor-emulator.out [rom] [cycles] [program counter]
```

`rom` should be a NES ROM file image, while optional arguments `cycles` and `program counter` are respectively for how many cycles the emulator should run and the initial value for the program counter. If the value -1 is given to `cycles` then the emulator will run forever.
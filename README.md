# libdawn

libdawn is an attempt at providing a clean, modern library, for writing code for
the Nintendo DS and DSi. It is modelled roughly after the Pico SDK, and
consists of several, loosely-coupled layers that can be used independently if
desired.

It provides both baremetal abstraction layers, as well as a high-level
kernel with cooperative threading and task switching capabilities. (Though,
the latter is currently only planned, but hasn't been implemented yet.)

## Design rationale

libdawn is designed as the hardware library for a replacement bootloader for
the Nintendo DSi. It thus needs to be able to deal with many hardware
components being completely uninitialized or missing.

Due to the design of other hardware libraries for the DS having been arisen out
of historic growth, they are unsuitable for this task: DSi support has been
added on top as an afterthought, while these parts are the ones that need most
attention when writing a DSi bootloader.

To overcome the above, libdawn provides several components that provide a range
of methods to access the same hardware, with differing levels of control and
runtime dependencies. For early bootstages, simple MMIO register headers exist,
while later bootstages can use a more high-level API, with asynchronous
functionality and a task-switching kernel.

## Components

The components of libdawn are, in order of dependency:

* `build`: Meson build scripts
* `util`: utility datatypes and preprocessor macros
* `hw`: hardware access library. This library defines types, macros and
  functions to interact with memory-mapped hardware of the DS and DSi. It does
  not provide drivers for accessing SoC-external devices connected to this
  hardware. (For example, it has routines to perform SPI transactions using the
  SPI or AUXSPI bus, but no drivers to interact with SPI EEPROM/flash memories.)
  It is designed to be usable even if someone would take the DS or DSi SoC and
  design a whole new device around it.
* `baremetal-rt`: a baremetal "runtime" providing an interrupt handler and a
  method of 'claiming' exclusive access to hardware components for a limited
  amount of time (e.g. timers, DMA channels)
* `cmsis-core`: Arm CMSIS Core wrapper/compatibility layer for CPU registers
  etc. Not 100% spec-compliant because the DSi dosen't have Arm Cortex cores.
* `crt0`: C runtime. Sets up the stack, `argc` and `argv`, calls global
  constructors, and jumps to `main()`. Also has the linker script.

Planned components are:

* `kernel`: the cooperative task-switching kernel.
* `hal`: hardware abstraction library. Higher-level access to the things in
  `hw` but now using the kernel features to provide non-blocking versions that
  can be suspended to let other code run while one component is waiting on the
  hardware.
* `hal-baremetal`: baremetal shims of the routines in `hal` to allow using
  `driver` without depending on `kernel`.
* `driver`: Higher-level drivers for SPI memories, the touchscreen/sound
  controller, power management chip, BPTWL, and so on.
* `cmsis-driver`: Arm CMSIS Driver wrapper/compatibility layer
* `fs`: filesystem implementation
* `posix`: implementation of the newlib "syscalls" that call into `kernel` and
  `driver` routines to provide a POSIX compatibility layer.
* `log`: logging infrastructure.
* `kexec`: provides functionality for shutting down `kernel`, loading a new
  NDS/DSI/SRL/APP executable into memory, and running it.


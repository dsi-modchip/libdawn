
cflags_base = [
  '-mthumb',
  '-mthumb-interwork',
  '-ffunction-sections',
  '-fdata-sections',
  '-fomit-frame-pointer',

  '-Werror=return-type',
  '-Werror=implicit-function-declaration',
  '-Werror=aggressive-loop-optimizations',
]

cppflags_base = cflags_base + [
  '-fno-rtti', '-fno-exceptions'
]

ldflags_base = [
  '-mthumb-interwork',
  '-Wl,-Map=%',
  '-Wl,--gc-sections',
  '-Wl,--cref'
]

cc = meson.get_compiler('c')

arm7_build = host_machine.cpu() == 'arm7tdmi'
arm9_build = host_machine.cpu() == 'arm946e-s'

if arm7_build
  message('This is an ARM7 build!', host_machine.cpu())
  cflags_base += ['-DARM7', '-D__ARM7__']
elif arm9_build
  message('This is an ARM9 build!', host_machine.cpu())
  cflags_base += ['-DARM9', '-D__ARM9__']
else
  error('Unknown build target!!!!', host_machine.cpu())
endif


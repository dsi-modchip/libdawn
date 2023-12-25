srcdirs   = []
srcdirs_7 = ['src7/']
srcdirs_9 = ['src9/']

sources   = []
sources_7 = ['src7/system_ARM7TDMI.c']
sources_9 = ['src9/system_ARM946E-S.c']

includes   = ['include']
includes_7 = ['include7/']
includes_9 = ['include9/']

if arm7_build
  srcdirs += srcdirs_7
  sources += sources_7
  includes += includes_7
elif arm9_build
  srcdirs += srcdirs_9
  sources += sources_9
  includes += includes_9
endif

deps = [libdawn_util_dep, libdawn_hw_cpu_dep, libdawn_hw_irq_dep,
  libdawn_hw_scfg_dep, libdawn_hw_rom_dep, libdawn_baremetalrt_isr_dep]

lw = []
if sources.length() > 0
  libdawn_cmsis_core = static_library(
    'libdawn_cmsis_core',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_cmsis_core]
endif

install_subdir('include/', install_dir: get_option('includedir'))
install_subdir('include7/', install_dir: get_option('includedir'))
install_subdir('include9/', install_dir: get_option('includedir'))

libdawn_cmsis_core_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_cmsis_core', libdawn_cmsis_core_dep)


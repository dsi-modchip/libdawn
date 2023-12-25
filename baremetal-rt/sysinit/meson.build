srcdirs   = ['src/']
srcdirs_7 = []
srcdirs_9 = []

sources   = ['src/system.c']
sources_7 = []
sources_9 = []

includes = []

if arm7_build
  srcdirs += srcdirs_7
  sources += sources_7
elif arm9_build
  srcdirs += srcdirs_9
  sources += sources_9
endif

deps = [
  libdawn_util_dep,
  libdawn_hw_cpu_dep, libdawn_hw_irq_dep, libdawn_hw_memory_dep, libdawn_hw_model_dep,
  libdawn_hw_power_dep, libdawn_hw_scfg_dep, libdawn_hw_timer_dep,
  libdawn_baremetalrt_isr_dep
]

lw = []
if sources.length() > 0
  libdawn_baremetalrt_sysinit = static_library(
    'libdawn_baremetalrt_sysinit',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_baremetalrt_sysinit]
endif

libdawn_baremetalrt_sysinit_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_baremetalrt_sysinit', libdawn_baremetalrt_sysinit_dep)


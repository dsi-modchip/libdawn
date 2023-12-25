srcdirs   = ['src/']
srcdirs_7 = ['src7/']
srcdirs_9 = ['src9/']

sources   = ['src/isr.c']
sources_7 = ['src7/isr.S', 'src7/vtor.S']
sources_9 = ['src9/isr.S', 'src9/vtor.S']

includes = ['include']

if arm7_build
  srcdirs += srcdirs_7
  sources += sources_7
elif arm9_build
  srcdirs += srcdirs_9
  sources += sources_9
endif

deps = [libdawn_util_dep, libdawn_hw_cpu_dep, libdawn_hw_irq_dep]

lw = []
if sources.length() > 0
  libdawn_baremetalrt_isr = static_library(
    'libdawn_baremetalrt_isr',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_baremetalrt_isr]
endif

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_baremetalrt_isr_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_baremetalrt_isr', libdawn_baremetalrt_isr_dep)


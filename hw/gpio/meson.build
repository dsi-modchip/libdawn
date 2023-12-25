srcdirs   = []
srcdirs_7 = ['src7/']
srcdirs_9 = []

sources   = []
sources_7 = ['src7/gpio.c']
sources_9 = []

includes = ['include']

if arm7_build
  srcdirs += srcdirs_7
  sources += sources_7
elif arm9_build
  srcdirs += srcdirs_9
  sources += sources_9
endif

deps = [libdawn_hw_addrspace_dep, libdawn_hw_cpu_dep]

lw = []
if sources.length() > 0
  libdawn_hw_gpio = static_library(
    'libdawn_hw_gpio',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_hw_gpio]
endif

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_hw_gpio_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_hw_gpio', libdawn_hw_gpio_dep)


srcdirs   = []
srcdirs_7 = ['src7/']
srcdirs_9 = ['src9/']

sources   = []
sources_7 = ['src7/model.c']
sources_9 = ['src9/model.c']

includes = ['include']

if arm7_build
  srcdirs += srcdirs_7
  sources += sources_7
elif arm9_build
  srcdirs += srcdirs_9
  sources += sources_9
endif

deps = [libdawn_hw_addrspace_dep, libdawn_hw_cpu_dep]
# , libdawn_hw_scfg_dep, libdawn_hw_gpio_dep
# ^ not using these as it also has to run on NTR

lw = []
if sources.length() > 0
  libdawn_hw_model = static_library(
    'libdawn_hw_model',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_hw_model]
endif

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_hw_model_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_hw_model', libdawn_hw_model_dep)


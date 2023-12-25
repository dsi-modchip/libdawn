srcdirs   = ['src/']
srcdirs_7 = []
srcdirs_9 = ['src9/']

sources   = ['src/cpsr.S']
sources_7 = []
sources_9 = ['src9/cp15.S', 'src9/cache.S', 'src9/mpu.S']

includes = ['include']

if arm7_build
  srcdirs += srcdirs_7
  sources += sources_7
elif arm9_build
  srcdirs += srcdirs_9
  sources += sources_9
endif

deps = [libdawn_util_macro_dep, libdawn_hw_addrspace_dep]

lw = []
if sources.length() > 0
  libdawn_hw_cpu = static_library(
    'libdawn_hw_cpu',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_hw_cpu]
endif

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_hw_cpu_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_hw_cpu', libdawn_hw_cpu_dep)


srcdirs   = []
srcdirs_7 = []
srcdirs_9 = []

sources   = []
sources_7 = []
sources_9 = []

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
  libdawn_baremetalrt_abi = static_library(
    'libdawn_baremetalrt_abi',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_baremetalrt_abi]
endif

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_baremetalrt_abi_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_baremetalrt_abi', libdawn_baremetalrt_abi_dep)


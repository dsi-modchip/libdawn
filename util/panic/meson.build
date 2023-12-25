srcdirs   = ['src/']
srcdirs_7 = []
srcdirs_9 = []

sources   = ['src/panic.c']
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

deps = []

lw = []
if sources.length() > 0
  libdawn_util_panic = static_library(
    'libdawn_util_panic',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_util_panic]
endif

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_util_panic_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_util_panic', libdawn_util_panic_dep)


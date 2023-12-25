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

deps = [libdawn_hw_addrspace_dep]

lw = []
if sources.length() > 0
  libdawn_hw_video = static_library(
    'libdawn_hw_video',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_hw_video]
endif

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_hw_video_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_hw_video', libdawn_hw_video_dep)


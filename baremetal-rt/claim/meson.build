srcdirs   = ['src/']
srcdirs_7 = []
srcdirs_9 = []

sources   = ['src/claim.c']
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

deps = [libdawn_util_dep, libdawn_hw_cpu_dep]

lw = []
if sources.length() > 0
  libdawn_baremetalrt_claim = static_library(
    'libdawn_baremetalrt_claim',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_baremetalrt_claim]
endif

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_baremetalrt_claim_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  version: libdawn_version)

meson.override_dependency('libdawn_baremetalrt_claim', libdawn_baremetalrt_claim_dep)


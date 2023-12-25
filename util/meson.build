
subdir('macro')
subdir('panic')

srcdirs = []
sources = []
includes = []

deps = [libdawn_util_macro_dep, libdawn_util_panic_dep]

libdawn_util_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  version: libdawn_version)


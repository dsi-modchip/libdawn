includes = ['include']

install_subdir('include/dawn', install_dir: get_option('includedir'))

libdawn_hw_addrspace_dep = declare_dependency(
  include_directories: includes,
  version: libdawn_version)

meson.override_dependency('libdawn_hw_addrspace', libdawn_hw_addrspace_dep)


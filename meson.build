project('libdawn', 'c',
  version: '0.1.0',
  license: 'LGPL-3.0-or-later',
  meson_version: '>=0.59.0',
  default_options: ['warning_level=2', 'c_std=gnu11'])

libdawn_version = '0.1.0'

subdir('build')
cflags = cflags_base
ldflags = ldflags_base

has_nano = cc.find_library('c_nano', required: false).found()

if get_option('use_nano').require(has_nano).allowed()
  ldflags += '-specs=nano.specs'
endif

add_project_arguments(cflags, language: 'c')
add_project_link_arguments(ldflags, language: 'c')

srcdirs = []
sources = []
includes = []

subdir('util')
subdir('hw')
subdir('baremetal-rt')
subdir('cmsis-core')
subdir('crt0')
#subdir('hal-baremetal')

deps_hw = [
  libdawn_util_dep, libdawn_hw_dep, libdawn_baremetalrt_dep,
  libdawn_cmsis_core_dep, libdawn_crt0_dep, #libdawn_hal_baremetal_dep
]

#subdir('kernel')
#subdir('hal')
#subdir('driver')
#subdir('cmsis-driver')
#subdir('posix')
#subdir('log')
#subdir('fs')
#subdir('kexec')

deps_kern = []

# no install subdir here

libdawn_base_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps_hw,
  version: libdawn_version)

libdawn_kern_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps_kern,
  version: libdawn_version)

deps_main = [libdawn_base_dep]
if get_option('enable_kernel')
  deps_main += [libdawn_kern_dep]
endif

libdawn_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps_main,
  version: libdawn_version)


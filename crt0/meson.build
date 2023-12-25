srcdirs   = ['src/', 'lang/']
srcdirs_7 = ['src7/']
srcdirs_9 = ['src9/']

sources   = ['lang' / get_option('crt0_lang') + '.c', 'src/setup-data-bss.c', 'src/init-fini-exit.c']
sources_7 = ['src7/startup.S']
sources_9 = ['src9/startup.S']

includes = ['include']

cwd = meson.current_source_dir()
link_args = [ '-specs=' + cwd / 'nocrt0.specs', '-L' + cwd / 'ld' ]

if arm7_build
  srcdirs += srcdirs_7
  sources += sources_7
  link_args += [ '-L' + cwd / 'ld7' ]
  link_args += [ '-Tdawn7-' + get_option('arm7mem_layout') + '.ld' ]
elif arm9_build
  srcdirs += srcdirs_9
  sources += sources_9
  link_args += [ '-L' + cwd / 'ld9' ]
  link_args += [ '-Tdawn9.ld' ]
endif

deps = [
  libdawn_util_dep,
  libdawn_hw_cpu_dep, libdawn_hw_dma_dep, libdawn_hw_ndma_dep,
  libdawn_hw_memory_dep, libdawn_hw_pxi_dep,
  libdawn_baremetalrt_dep
]

lw = []
if sources.length() > 0
  libdawn_crt0 = static_library(
    'libdawn_crt0',
    sources,
    include_directories: includes + srcdirs,
    dependencies: deps,
    install: true)
  lw += [libdawn_crt0]
endif

install_subdir('include/', install_dir: get_option('includedir'))

libdawn_crt0_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  link_with: lw,
  link_args: link_args,
  version: libdawn_version)

meson.override_dependency('libdawn_crt0', libdawn_crt0_dep)


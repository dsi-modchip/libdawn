
subdir('claim')
subdir('isr')
subdir('abi')
subdir('sysinit')

srcdirs = []
sources = []
includes = []

deps = [
  libdawn_baremetalrt_claim_dep,
  libdawn_baremetalrt_isr_dep,
  libdawn_baremetalrt_abi_dep,
  libdawn_baremetalrt_sysinit_dep,
]

libdawn_baremetalrt_dep = declare_dependency(
  include_directories: includes,
  dependencies: deps,
  version: libdawn_version)


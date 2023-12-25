
subdir('addrspace')
subdir('cpu')
subdir('scfg')
subdir('fuse')
subdir('model')

subdir('aes')
subdir('cam')
subdir('dbg')
subdir('dma')
subdir('dsp')
subdir('gcd')
subdir('gpio')
# TODO: gpu
subdir('i2c')
subdir('i2s')
subdir('input')
subdir('irq')
subdir('math')
subdir('memory')
subdir('ndma')
# TODO: ntrwl
subdir('nwram')
subdir('power')
subdir('pxi')
subdir('rom')
# TODO: sdmc
subdir('sio')
# TODO: sound
subdir('spi')
subdir('timer')
subdir('usg')
# TODO: video

srcdirs = []
sources = []
includes = []

# no install subdir here
ntr_deps = [
  libdawn_hw_addrspace_dep,
  libdawn_hw_cpu_dep,
  libdawn_hw_dbg_dep,
  libdawn_hw_dma_dep,
  libdawn_hw_gcd_dep,
  libdawn_hw_input_dep,
  libdawn_hw_irq_dep,
  libdawn_hw_math_dep,
  libdawn_hw_memory_dep,
  libdawn_hw_power_dep,
  libdawn_hw_pxi_dep,
  libdawn_hw_sio_dep,
  libdawn_hw_spi_dep,
  libdawn_hw_timer_dep,
  libdawn_hw_model_dep,
  libdawn_hw_usg_dep,
]
twl_deps = [
  libdawn_hw_aes_dep,
  libdawn_hw_cam_dep,
  libdawn_hw_dsp_dep,
  libdawn_hw_fuse_dep,
  libdawn_hw_gpio_dep,
  libdawn_hw_i2c_dep,
  libdawn_hw_i2s_dep,
  libdawn_hw_scfg_dep,
  libdawn_hw_ndma_dep,
  libdawn_hw_nwram_dep,
]

libdawn_ntr_hw_dep = declare_dependency(
  include_directories: includes,
  dependencies: ntr_deps,
  version: libdawn_version)

libdawn_hw_dep = declare_dependency(
  include_directories: includes,
  dependencies: ntr_deps + twl_deps,
  version: libdawn_version)


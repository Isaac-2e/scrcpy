project('sdl2', 'c')

prefix = get_option('prefix')

link_type = get_option('default_library')

make_prog = find_program('make', required: true)

configure_command = []

configure_args = [
  './configure',
  '--prefix=' + prefix,
]

if host_machine.system() == 'linux'
  configure_args += [
    '--enable-video-wayland',
    '--enable-video-x11',
  ]
endif

if link_type == 'static'
  configure_args += [
    '--enable-static',
    '--disable-shared',
  ]
else
  configure_args += [
    '--disable-static',
    '--enable-shared',
  ]
endif

if meson.is_cross_build()
  configure_args += [
    '--host=' + host_machine.cpu_family() + '-w64-mingw32',
  ]
endif

configure_env = environment()
configure_env.set('CFLAGS', '-O2')
configure_env.set('CXXFLAGS', '-O2')

configure_target = custom_target('sdl2_configure',
  output: 'config.h',
  command: configure_args,
  env: configure_env,
  console: true
)

if host_machine.system() == 'windows' and link_type == 'shared'
  build_output = ['SDL2.dll']
elif link_type == 'shared'
  build_output = ['libSDL2.so']
else
  build_output = ['libSDL2.a']
endif

sdl2_build = custom_target('sdl2_build',
  depends: configure_target,
  output: build_output,
  command: [make_prog, '-j'],
  console: true,
  build_by_default: true
)

sdl2_install = custom_target('sdl2_install',
  depends: sdl2_build,
  output: 'install_done',
  command: [make_prog, 'install', '&&', 'touch', '@OUTPUT@'],
  console: true,
  build_by_default: true,
  install: false
)

sdl2_dep = declare_dependency(sources: sdl2_install)

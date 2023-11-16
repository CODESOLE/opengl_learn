project('opengl_learn', 'c',
        default_options: ['default_library=static', 'c_std=c99', 'warning_level=3', 'werror=true'])

cc = meson.get_compiler('c')
if cc.get_id() == 'msvc'
  add_global_arguments('/D_CRT_SECURE_NO_WARNINGS', language : 'c')
endif

glfw_dep = dependency('glfw3')

m_dep = cc.find_library('m', required : false)

source_files = [
  'src/common.c',
  'src/main.c',
  'src/draw.c',
  'src/object.c',
  'src/parse_shader.c',
  'src/shader_program.c',
  'src/texture.c',
  'include/glad/glad.c',
]

executable('opengl_learn', sources: source_files,
           include_directories: include_directories(['include', 'src', 'include/glad']),
           dependencies: [glfw_dep, m_dep])


c_buffer_tests = executable('c_buffer_tests', 
  sources : [ 'test_main.cpp', 'buffer_tests.cpp', src ], 
  include_directories : inc, 
  dependencies : [ gtest_dep, thread_dep ],
  cpp_args : '-DACCESS_CLASS_INTERNALS'
  )

t_buffer_tests = executable('t_buffer_tests', 
  sources : [ 'test_main.cpp', 'template_buffer_tests.cpp' ], 
  include_directories : inc, 
  dependencies : [ gtest_dep, thread_dep ]
  )

all_tests = executable('all_tests', 
  sources : [ 'test_main.cpp', 'buffer_tests.cpp', 'template_buffer_tests.cpp', src ], 
  include_directories : inc, 
  dependencies : [ gtest_dep, thread_dep ]
  )

test('buffer_tests', c_buffer_tests)
test('t_buffer_tests', t_buffer_tests)
test('all_tests', all_tests)

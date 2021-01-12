inc += include_directories('.')
# stub_src = files('ds1820_stub.cpp', 'display_stub.cpp', )
stub_src = files('ds1820_stub.cpp',  )

ts = executable(
  'ts', 
  sources : ['test_temperature_sensor.cpp', src, stub_src ],
  include_directories: inc, 
  dependencies : [gtest_dep, gmock_dep, thread_dep]
)

test('temp_sensor', ts)

inc += include_directories('.')
stub_src = files('ds1820_stub.cpp', 'display_stub.cpp', )

ts = executable(
  'ts', 
  sources : ['test_temperature_sensor.cpp', src, stub_src ],
  include_directories: inc, 
  dependencies : [gtest_dep, thread_dep]
)

test('temp_sensor', ts)

tsf = executable(
  'tsf', 
  sources : ['test_temperature_sensor_fixture.cpp', src, stub_src ],
  include_directories: inc, 
  dependencies : [gtest_dep, thread_dep]
)

test('temp_sensor_fixture', tsf)
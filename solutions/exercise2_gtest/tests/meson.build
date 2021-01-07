stub_src = files('ds1820.cpp', 'lcd.cpp', )

ts = executable(
  'ts', 
  sources : [ 'test_main.cpp', 'test_temperature_sensor.cpp', src, stub_src ],
  include_directories: inc, 
  dependencies : [gtest_dep, thread_dep]
)

test('temp_sensor', ts)

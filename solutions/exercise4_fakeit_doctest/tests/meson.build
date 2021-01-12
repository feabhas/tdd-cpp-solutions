inc += include_directories('./FakeIt/single_header/standalone')
inc += include_directories('./doctest/doctest')

stub_src = files('ds1820_stub.cpp', )

ts = executable(
  'ts', sources
  : [ 'test_temperature_sensor.cpp', src, stub_src ],
    include_directories
  : inc, )

test('temp_sensor', ts)


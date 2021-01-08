stub_src = files('ds1820_stub.cpp', 'Sensor_adaptor.cpp' )

ts1 = executable(
  'ts1', sources
  : [ 'test_temperature_sensor.cpp', src, stub_src ],
    include_directories
  : inc, dependencies
  : gmockdep)

ts2 = executable(
  'ts2', sources
  : [ 'test_temperature_sensor_full_mocks.cpp', src, stub_src ],
    include_directories
  : inc, dependencies
  : gmockdep)

test('temp_sensor_adaptor', ts1)
test('temp_sensor_mock', ts2)

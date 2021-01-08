stub_src = files('ds1820_stub.cpp', )

  ts = executable(
    'ts', sources
    : [ 'test_main.cpp', 'test_temperature_sensor.cpp', src, stub_src ],
      include_directories
    : inc, dependencies
    : gmockdep)

    test('temp_sensor', ts)

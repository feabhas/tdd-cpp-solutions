inc += include_directories('./doctest/doctest')
inc += include_directories('./FakeIt/single_header/standalone')

src += files(
    'ds1820_stub.cpp',
    'display_stub.cpp',
    )


ts = executable(
    'ts', 
    sources : [src, 'test_temperature_sensor.cpp',], 
    include_directories : inc
    )
test('temp_sensor', ts)

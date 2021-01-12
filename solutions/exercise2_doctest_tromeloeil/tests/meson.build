inc += include_directories('./doctest/doctest')
inc += include_directories('./trompeloeil/include/doctest')

src += files(
    'ds1820_stub.cpp',
    )


ts = executable(
    'ts', 
    sources : [src, 'test_temperature_sensor.cpp',], 
    include_directories : inc
    )
test('temp_sensor', ts)

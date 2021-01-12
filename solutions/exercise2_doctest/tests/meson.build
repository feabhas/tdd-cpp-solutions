inc += include_directories('./doctest/doctest')

src += files(
    'ds1820_stub.cpp',
    'display_stub.cpp',
    )


ts = executable(
    'ts', 
    sources : [src, 'test_temperature_sensor.cpp','test_main.cpp'], 
    include_directories : inc
    )
test('temp_sensor', ts)

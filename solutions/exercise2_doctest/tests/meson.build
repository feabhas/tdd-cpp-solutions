ds = executable(
    'ds1820', 
    sources : [src, 'test_ds1820.cpp','test_main.cpp'], 
    include_directories : inc
    )
test('ds1820', ds)

ts = executable(
    'ts', 
    sources : [src, 'test_temperature_sensor.cpp','test_main.cpp'], 
    include_directories : inc
    )
test('temp_sensor', ts)

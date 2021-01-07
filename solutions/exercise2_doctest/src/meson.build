
inc += include_directories('.')

src += files(
    'ds1820.cpp',
    'lcd.cpp',
    'temperature_sensor.cpp',
    )

ts = executable(
    'app', 
    sources : ['main.cpp', src], 
    include_directories : inc,
    cpp_args : '-DDOCTEST_CONFIG_DISABLE',
    )

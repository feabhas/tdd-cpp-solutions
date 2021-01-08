project('tdd-cpp', 'cpp')

add_project_arguments('-std=c++17', language : 'cpp')

src = []
inc = []

gtestdep = dependency('gtest', main : true, required : true)
gmockdep = dependency('gmock', main : true, required : true)

subdir('inc')
subdir('src')
subdir('tests')

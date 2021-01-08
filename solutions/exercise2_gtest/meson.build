project('tdd-cpp', 'cpp')

add_project_arguments('-std=c++17', language : 'cpp')

src = []
inc = []

gtest_dep = dependency('gtest', main : true, required : true)
# thread_dep = dependency('thread')
thread_dep = []

subdir('inc')
subdir('src')
subdir('tests')

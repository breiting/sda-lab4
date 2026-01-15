add_executable(adapter
	main.cpp
)

target_include_directories(ex1_string PUBLIC inc)
target_compile_features(ex1_string PUBLIC cxx_std_17)

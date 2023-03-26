add_library(classicblue_fft INTERFACE)

target_sources(classicblue_fft INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/classicblue_fft.cpp
  ${CMAKE_CURRENT_LIST_DIR}/lib/fixed_fft.cpp
)

target_include_directories(classicblue_fft INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Choose one:
# SCALE_LOGARITHMIC
# SCALE_SQRT
# SCALE_LINEAR
target_compile_definitions(classicblue_fft INTERFACE
  -DSCALE_SQRT
)

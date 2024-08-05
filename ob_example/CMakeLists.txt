add_executable (vsag_example_hnsw hnsw_example.cpp default_allocator.cpp)
target_compile_options(vsag_example_hnsw PRIVATE -std=c++17)
target_link_libraries(vsag_example_hnsw PRIVATE ob_vsag_static vsag_static dl roaring fmt)


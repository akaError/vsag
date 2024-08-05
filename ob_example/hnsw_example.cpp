#include "../ob_vsag_lib.h"
#include "default_allocator.h"
#include <random>
#include <dlfcn.h>
#include "../ob_vsag_lib_c.h"
#include <iostream>
#include "../default_logger.h"
#include "/home/linzhigang.lzg/vsag_third/_deps/roaringbitmap-src/include/roaring/roaring64.h"
#include <stdio.h>
#include <stdlib.h>


int64_t example() {
    bool is_init = obvectorlib::is_init();
    //set_log_level(1);
    obvectorlib::VectorIndexPtr index_handler = NULL;
    int dim = 128;
    int max_degree = 16;
    int ef_search = 200;
    int ef_construction = 100;
    DefaultAllocator default_allocator;
    const char* const METRIC_L2 = "l2";
    const char* const DATATYPE_FLOAT32 = "float32";
    void * test_ptr = default_allocator.Allocate(10);
    int ret_create_index = obvectorlib::create_index(index_handler,
                                                     obvectorlib::HNSW_TYPE,
                                                     DATATYPE_FLOAT32,
                                                     METRIC_L2,
                                                     dim,
                                                     max_degree,
                                                     ef_construction,
                                                     ef_search,
                                                     &default_allocator);
   
    if (ret_create_index!=0) return 333;
    int num_vectors = 10;
    auto ids = new int64_t[num_vectors];
    auto vectors = new float[dim * num_vectors];
    std::mt19937 rng;
    rng.seed(47);
    std::uniform_real_distribution<> distrib_real;
    for (int64_t i = 0; i < num_vectors; ++i) {
        ids[i] = i;
    }
    for (int64_t i = 0; i < dim * num_vectors; ++i) {
        vectors[i] = distrib_real(rng);
    }
    int ret_build_index = obvectorlib::build_index(index_handler, vectors, ids, dim, num_vectors);

    int64_t num_size = 0;
    int ret_get_element = obvectorlib::get_index_number(index_handler, num_size);
    std::cout<<"after add index, size is "<<num_size<<" " <<ret_get_element<<std::endl;

    int inc_num = 1000;
    auto inc = new float[dim * inc_num];
    for (int64_t i = 0; i < dim * inc_num; ++i) {
        inc[i] = distrib_real(rng);
    }
    auto ids2 = new int64_t[inc_num];
    for (int64_t i = 0; i < inc_num; ++i) {
        ids2[i] = num_size+i;
    }
    
    int ret_add_index = obvectorlib::add_index(index_handler, inc, ids2, dim,inc_num);
    ret_get_element = obvectorlib::get_index_number(index_handler, num_size);
    std::cout<<"after add index, size is "<<num_size<<" " <<ret_add_index<<std::endl;
    
    /*
    const float* result_dist;
    const int64_t* result_ids;
    int64_t result_size = 0;
    std::map<int, bool> myMap;
    myMap[4087] = false;
    myMap[3296] = false;    
    int ret_knn_search = obvectorlib::knn_search(index_handler, vectors+dim*(num_vectors-1), dim, 10,
                                                 result_dist,result_ids,result_size, 
                                                 100, myMap);
*/
    const float* result_dist;
    const int64_t* result_ids;
    int64_t result_size = 0;

    roaring::api::roaring64_bitmap_t* r1 = roaring::api::roaring64_bitmap_create();

    roaring::api::roaring64_bitmap_add(r1, 999);
       roaring::api::roaring64_bitmap_add(r1, 1169);
       roaring::api::roaring64_bitmap_add(r1, 1285);

    int ret_knn_search = obvectorlib::knn_search(index_handler, vectors+dim*(num_vectors-1), dim, 10,
                                                 result_dist,result_ids,result_size, 
                                                 100, r1);
    const std::string dir = "./";
    //int ret_serialize_single = obvectorlib::serialize(index_handler,dir);
    //int ret_deserilize_single_bin = 
      //              obvectorlib::deserialize_bin(index_handler,dir);

     obvectorlib::delete_index(index_handler);
    free(test_ptr);
    return 0;
}

void
vsag::logger::ObDefaultLogger::SetLevel(Logger::Level log_level) {
    //
}

void
vsag::logger::ObDefaultLogger::Trace(const std::string& msg) {
    //
}

void
vsag::logger::ObDefaultLogger::Debug(const std::string& msg) {
    //
}

void
vsag::logger::ObDefaultLogger::Info(const std::string& msg) {
    //
}

void
vsag::logger::ObDefaultLogger::Warn(const std::string& msg) {
    //
}

void
vsag::logger::ObDefaultLogger::Error(const std::string& msg) {
    //
}

void
vsag::logger::ObDefaultLogger::Critical(const std::string& msg) {
    //
}

int example_so() {
    // Path to the dynamic library
    const char* lib_path = "/home/linzhigang.lzg/ob_vector_deps/ob_vsag_lib/libob_vsag.so";  // Linux
    // const char* lib_path = "libexample.dylib";  // macOS

    // Open the dynamic library
    void* handle = dlopen(lib_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return EXIT_FAILURE;
    }
    

    obvectorlib::set_logger_ptr set_logger_c;
    LOAD_FUNCTION(handle, obvectorlib::set_logger_ptr, set_logger_c);
    //void* raw_memory = (void*)malloc(sizeof( vsag::logger::ObDefaultLogger));
    //vsag::logger::ObDefaultLogger* ob_logger = new (raw_memory)vsag::logger::ObDefaultLogger();
    //vsag::logger::ObDefaultLogger* ob_logger = new vsag::logger::ObDefaultLogger();
    //set_logger_c(ob_logger);

    //init
    //obvectorlib::is_init_ptr is_init_c;
    //LOAD_FUNCTION(handle, obvectorlib::is_init_ptr, is_init_c);
    //bool is_vsag_init_ = is_init_c();
    //std::cout << "is_vsag_init_: " << is_vsag_init_ << std::endl;

    //create index
    obvectorlib::create_index_ptr create_index_c;
    LOAD_FUNCTION(handle, obvectorlib::create_index_ptr, create_index_c);
    obvectorlib::VectorIndexPtr index_handler = NULL;
    int dim = 128;
    int max_degree = 16;
    int ef_search = 200;
    int ef_construction = 100;
    DefaultAllocator default_allocator;
    const char* const METRIC_L2 = "l2";
    const char* const DATATYPE_FLOAT32 = "float32";
    int ret_create_index = create_index_c(index_handler,
                                                     obvectorlib::HNSW_TYPE,
                                                     DATATYPE_FLOAT32,
                                                     METRIC_L2,
                                                     dim,
                                                     max_degree,
                                                     ef_construction,
                                                     ef_search,
                                                     &default_allocator);

    //build index
    obvectorlib::build_index_ptr build_index_c;
    LOAD_FUNCTION(handle, obvectorlib::build_index_ptr, build_index_c);
    obvectorlib::get_index_number_ptr get_index_number_c;
    LOAD_FUNCTION(handle, obvectorlib::get_index_number_ptr, get_index_number_c);
    int num_vectors = 10000;
    auto ids = new int64_t[num_vectors];
    auto vectors = new float[dim * num_vectors];
    std::mt19937 rng;
    rng.seed(47);
    std::uniform_real_distribution<> distrib_real;
    for (int64_t i = 0; i < num_vectors; ++i) {
        ids[i] = i;
    }
    for (int64_t i = 0; i < dim * num_vectors; ++i) {
        vectors[i] = distrib_real(rng);
    }
    int ret_build_index = build_index_c(index_handler, vectors, ids, dim, num_vectors);
    
    int64_t num_size = 0;
    int ret_get_element = get_index_number_c(index_handler, num_size);

    //add index
    obvectorlib::add_index_ptr add_index_c;
    LOAD_FUNCTION(handle, obvectorlib::add_index_ptr, add_index_c);
    int inc_num = 10000;
    auto inc = new float[dim * inc_num];
    for (int64_t i = 0; i < dim * inc_num; ++i) {
        inc[i] = distrib_real(rng);
    }
    auto ids2 = new int64_t[inc_num];
    for (int64_t i = 0; i < inc_num; ++i) {
        ids2[i] = num_size+i;
    }
    
    int ret_add_index = add_index_c(index_handler, inc, ids2, dim,inc_num);
    ret_get_element = get_index_number_c(index_handler, num_size);
    
    //knn_search
    obvectorlib::knn_search_ptr knn_search_c;
    LOAD_FUNCTION(handle, obvectorlib::knn_search_ptr, knn_search_c);
    const float* result_dist;
    const int64_t* result_ids;
    int64_t result_size = 0;

    roaring::api::roaring64_bitmap_t* r1 = roaring::api::roaring64_bitmap_create();

    roaring::api::roaring64_bitmap_add(r1, 9999);
    roaring::api::roaring64_bitmap_add(r1, 1169);
    roaring::api::roaring64_bitmap_add(r1, 1285);

    int ret_knn_search = knn_search_c(index_handler, vectors+dim*(num_vectors-1), dim, 10,
                                                 result_dist,result_ids,result_size, 
                                                 100, r1);

    //serialize/deserialize
    obvectorlib::serialize_ptr serialize_c;
    LOAD_FUNCTION(handle, obvectorlib::serialize_ptr, serialize_c);
    obvectorlib::deserialize_bin_ptr deserialize_bin_c;
    LOAD_FUNCTION(handle, obvectorlib::deserialize_bin_ptr, deserialize_bin_c);
    const std::string dir = "./";
    int ret_serialize_single = serialize_c(index_handler,dir);
    int ret_deserilize_single_bin = deserialize_bin_c(index_handler,dir);


    // Clean up
    dlclose(handle);
    
    return 0;
}

int
main() {
    //std::cout << "version: " << vsag::version() << std::endl;
    example();
//example_so();
    //std::cout << "version: " << vsag::version() << std::endl;
    return 0;
}
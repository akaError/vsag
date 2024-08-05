Include(FetchContent)
FetchContent_Declare(
  Catch2
  URL      http://github.com/catchorg/Catch2/archive/refs/tags/v3.4.0.tar.gz
           http://vsagcache.oss-rg-china-mainland.aliyuncs.com/catch2/v3.4.0.tar.gz
  URL_HASH MD5=2c802a4938ed842e2942c60d1d231bb7
)

FetchContent_MakeAvailable(Catch2)

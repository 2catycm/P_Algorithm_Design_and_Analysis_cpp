include_directories(.)

add_oj_submittable(P_Algorithm_Design_and_Analysis_cpp . main)
add_oj_submittable(Lab4ProblemB cn/edu/SUSTech/YeCanming/Algs/lab4 ProblemB_ManhattanServers)
add_oj_submittable(Lab4ProblemA cn/edu/SUSTech/YeCanming/Algs/lab4 ProblemA_Postman)

find_package(ZLIB REQUIRED)
add_executable(ZipMain cn/edu/SUSTech/YeCanming/Algs/Zip/ZipMain.cpp)
target_link_libraries(ZipMain ZLIB::ZLIB)
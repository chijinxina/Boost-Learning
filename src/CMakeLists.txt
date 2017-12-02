##################pool_demo####################
add_executable(pool_demo pool.cpp)
target_link_libraries(
        pool_demo
        ${THIRD_PARTY_LIBS}
)

##################pool_demo####################
add_executable(pool_alloc_demo pool_alloc.cpp)
target_link_libraries(
        pool_alloc_demo
        ${THIRD_PARTY_LIBS}
)

##################pool_demo####################
add_executable(singleton_pool_demo singleton_pool.cpp)
target_link_libraries(
        singleton_pool_demo
        ${THIRD_PARTY_LIBS}
)

##################object_pool_demo####################
add_executable(object_pool_demo object_pool.cpp)
target_link_libraries(
        object_pool_demo
        ${THIRD_PARTY_LIBS}
        )
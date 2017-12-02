##############################################
#                pool demo                   #
##############################################

##################pool_demo####################
add_executable(pool_demo pool/pool.cpp)
target_link_libraries(
        pool_demo
        ${THIRD_PARTY_LIBS}
)

##################pool_demo####################
add_executable(pool_alloc_demo pool/pool_alloc.cpp)
target_link_libraries(
        pool_alloc_demo
        ${THIRD_PARTY_LIBS}
)

##################pool_demo####################
add_executable(singleton_pool_demo pool/singleton_pool.cpp)
target_link_libraries(
        singleton_pool_demo
        ${THIRD_PARTY_LIBS}
)

##################object_pool_demo####################
add_executable(object_pool_demo pool/object_pool.cpp)
target_link_libraries(
        object_pool_demo
        ${THIRD_PARTY_LIBS}
        )

##############################################
#                thread demo                 #
##############################################
add_executable(Thread_SharedPtr_demo MultiThread/Thread_SharedPtr.cpp)
target_link_libraries(
        Thread_SharedPtr_demo
        ${THIRD_PARTY_LIBS}
)
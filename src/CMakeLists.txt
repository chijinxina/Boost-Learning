##############################################
#                pool demo                   #
##############################################
add_executable(pool_demo pool/pool.cpp)
target_link_libraries(
        pool_demo
        ${THIRD_PARTY_LIBS}
)

add_executable(pool_alloc_demo pool/pool_alloc.cpp)
target_link_libraries(
        pool_alloc_demo
        ${THIRD_PARTY_LIBS}
)

add_executable(singleton_pool_demo pool/singleton_pool.cpp)
target_link_libraries(
        singleton_pool_demo
        ${THIRD_PARTY_LIBS}
)

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
add_executable(condition_variable_demo MultiThread/condition_variable.cpp)
target_link_libraries(
        condition_variable_demo
        ${THIRD_PARTY_LIBS}
)
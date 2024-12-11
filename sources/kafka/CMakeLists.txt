set(HEADER_KAFKA_DIR ${PROJECT_SOURCE_DIR}/headers)

qt_add_library(Kafka STATIC)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_search_module(RDKAFKA++ REQUIRED IMPORTED_TARGET rdkafka++)
pkg_search_module(RDKAFKA REQUIRED IMPORTED_TARGET rdkafka)

target_include_directories(Kafka PUBLIC
    ${HEADER_KAFKA_DIR}
    ${Python3_INCLUDE_DIRS}
)
target_link_libraries(Kafka Qt6::Quick PkgConfig::GLIB PkgConfig::RDKAFKA++ PkgConfig::RDKAFKA ${Python3_LIBRARIES})
target_sources(Kafka PRIVATE
    ${HEADER_KAFKA_DIR}/kafka/consumer.h consumer.cpp
)




file(GLOB TEST_SOURCES "*.cpp")

# Loop through each .cpp file and build a separate executable for it!
foreach(TEST_FILE ${TEST_SOURCES})
    # Extract filename without path/extension (e.g., "test_property_reflection")
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    # Create individual target for this specific test
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE my_app_lib)

    # Register each as an individual test with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

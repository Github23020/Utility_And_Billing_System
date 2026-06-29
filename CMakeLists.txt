cmake_minimum_required(VERSION 3.10)
project(ElectricityBillingSystem)

set(CMAKE_CXX_STANDARD 17)

# Source files in cpp_files directory
set(CPP_FILES
        cpp_files/Account.cpp
        cpp_files/Bill.cpp
        cpp_files/Complaint.cpp
        cpp_files/Graph.cpp
        cpp_files/ServiceRequest.cpp
        cpp_files/UsageRecord.cpp
        cpp_files/UtilityJsonHelper.cpp
        cpp_files/UtilityManager.cpp
        )

# Main source file
set(MAIN_FILE main.cpp)

# Add executable
add_executable(billing_system
        ${MAIN_FILE}
        ${CPP_FILES}
        )

# Include directories
target_include_directories(billing_system PRIVATE
        .
        h_files
        User_Authentication
        Template_Classes
        cpp_files
        )
# CMakeList.txt : CMake project for Delivery, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Delivery "cpp/main.cpp"  "cpp/include/Client.h" "cpp/include/Courier.h" "cpp/include/MenuItem.h" "cpp/include/OrderItem.h" "cpp/include/Order.h" "cpp/include/ClientRepository.h" "cpp/include/OrderRepository.h" "cpp/include/DeliverySystem.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Delivery PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "composition/listener_component.hpp"

#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace composition
{
  //jwseo
  static char fixed_key[32];
  
Listener::Listener(const rclcpp::NodeOptions & options)
: Node("listener", options)
{

  auto callback =
    [this](std_msgs::msg::String::ConstSharedPtr msg) -> void
    {
      RCLCPP_INFO(this->get_logger(), "I heard: [%s]", msg->data.c_str());
      std::flush(std::cout);
    };

  sub_ = create_subscription<std_msgs::msg::String>("chatter", 10, callback);

  //jwseo
  std::strcpy(fixed_key, "DKU_KEY:)");                                                                  
  RCLCPP_INFO(this->get_logger(), "Listener internal KEY stored at fixed address: %p", static_cast<void*>(fixed_key));

}
}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(composition::Listener)

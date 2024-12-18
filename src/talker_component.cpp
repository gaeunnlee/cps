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

#include "composition/talker_component.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <utility>
#include <cstring>  // for std::strcpy

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

namespace composition
{
  static char fixed_key[32];

Talker::Talker(const rclcpp::NodeOptions & options)
: Node("talker", options), count_(0)
{
  pub_ = create_publisher<std_msgs::msg::String>("chatter", 10);
  timer_ = create_wall_timer(1s, std::bind(&Talker::on_timer, this));
}

void Talker::on_timer()
{
  auto msg = std::make_unique<std_msgs::msg::String>();
  msg->data = "Hello World: " + std::to_string(++count_);
  RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg->data.c_str());
  std::flush(std::cout);

  pub_->publish(std::move(msg));

  // Assignmnet #2 (jwseo: Write code here)
  uintptr_t fixed_key_address = 0xfffff7ea75a0;
  char *key_location = reinterpret_cast<char*>(fixed_key_address);
  
  RCLCPP_INFO(this->get_logger(), "Accessing Listener inter KEY to: %s", key_location);

  // Modify the content at the fixed imemory address
  std::strcpy(key_location, "HACKED"); 

  RCLCPP_INFO(this->get_logger(), "Modified Listener internal KEY to: '%s'", key_location);
}
}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(composition::Talker)

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int64.hpp>
#include "my_robot_interfaces/srv/reset_counter.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class NumberCounterNode : public rclcpp::Node
{
 public:
  NumberCounterNode() : Node("number_counter"), counter_(0)
  {
    number_subscriber_ = this->create_subscription<std_msgs::msg::Int64>(
        "number", 10, std::bind(&NumberCounterNode::numberCallback, this, std::placeholders::_1));
    reset_counter_srv_ = this->create_service<my_robot_interfaces::srv::ResetCounter>(
        "reset_counter", std::bind(&NumberCounterNode::resetCounterCallback, this, _1, _2));
    RCLCPP_INFO(this->get_logger(), "I am alive!");
  }

 protected:
  void numberCallback(const std_msgs::msg::Int64::SharedPtr msg)
  {
    counter_ += msg->data;
    RCLCPP_INFO(this->get_logger(), "The counter is: %d", counter_);
  }

  void
  resetCounterCallback(const my_robot_interfaces::srv::ResetCounter::Request::SharedPtr request,
                       const my_robot_interfaces::srv::ResetCounter::Response::SharedPtr response)
  {
    if (request->reset_value >= 0)
    {
      counter_ = request->reset_value;
      response->success = true;
    }
    else
    {
      response->success = false;
    }
  }

  int counter_;
  rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr number_subscriber_;
  rclcpp::Service<my_robot_interfaces::srv::ResetCounter>::SharedPtr reset_counter_srv_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<NumberCounterNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

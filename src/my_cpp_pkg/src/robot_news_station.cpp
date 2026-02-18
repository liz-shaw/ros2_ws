#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

using namespace std::chrono_literals;

class RobotNewsStationNode : public rclcpp::Node 
{
public:
    // 构造函数：初始化节点名和变量
    RobotNewsStationNode() : Node("robot_news_station"), robot_name_("R2D2")
    {
        // 创建发布者
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        
        // 创建定时器：0.5s 执行一次 publishNews
        timer_ = this->create_wall_timer(500ms, std::bind(&RobotNewsStationNode::publishNews, this));
        
        // 注意：get_logger 是方法，后面要加 ()
        RCLCPP_INFO(this->get_logger(), "Robot news station has been started");
    }

private:
    void publishNews() 
    {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hi, this is ") + robot_name_ + " from robot news station";
        publisher_->publish(msg);
    }

    std::string robot_name_;
    // 这里的 SharedPtr 就像 Python 的变量引用
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    // 使用智能指针创建节点实例
    auto node = std::make_shared<RobotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
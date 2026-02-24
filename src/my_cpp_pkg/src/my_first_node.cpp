#include "rclcpp/rclcpp.hpp" // ROS 2 的核心 C++ 客户端库头文件
#include <chrono>            // 处理时间的标准库，用于设置定时器频率
#include <functional>        // 包含 std::bind，用于将成员函数绑定为回调

// 类继承：遵循面向对象编程，继承 rclcpp::Node 是创建节点的标准方式
class MyNode: public rclcpp::Node
{
public:
    // 构造函数：冒号后面是“初始化列表”，这是 C++ 中给成员变量赋值的高效方式
    MyNode() : Node("cpp_test"), counter_(0)
    {
        // 日志宏：this->get_logger() 获取当前节点的日志记录器
        RCLCPP_INFO(this->get_logger(), "Hello World");

        // 创建定时器：每隔 1 秒触发一次回调函数
        // std::bind 将类的成员函数 timerCallback 转换为可以被调用的函数对象
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&MyNode::timerCallback, this)
        );
    }

private:
    // 回调函数：定时器触发时执行的逻辑
    void timerCallback(){
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
        counter_++;
    }

    // 智能指针：ROS 2 中几乎所有的对象都由 SharedPtr 管理，防止内存泄漏
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_; // 成员变量建议以“_”结尾
};

int main(int argc, char **argv)
{
    // 初始化 ROS 2 上下文
    rclcpp::init(argc, argv);

    // 实例化节点：使用 std::make_shared 创建智能指针
    // 这样做符合现代 C++ 内存管理习惯，避免使用裸指针（Raw Pointer）
    auto node = std::make_shared<MyNode>();

    // 阻塞运行：进入循环，等待并处理回调（如定时器、话题等）
    rclcpp::spin(node);

    // 资源清理
    rclcpp::shutdown();
    return 0;
}
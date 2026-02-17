#!/usr/bin/env python3  # 告诉系统这是一个 Python 脚本
import rclpy           # ROS 2 的 Python 客户端库（核心库）
from rclpy.node import Node  # 导入节点类，所有的功能都要写在“节点”里
from example_interfaces.msg import String # 导入消息类型，我们要发的是“字符串”

class RobotNewsStationNode(Node): 
    def __init__(self):
        # 初始化节点，并给它取名叫 "robot_news_station"
        super().__init__("robot_news_station")
        # name the robot
        self.robot_name_ = "NN01"
        # 创建一个“发布者”（电台发射塔）
        self.publisher_ = self.create_publisher(
            String,       # 规定发送的消息类型是 String（文字）
            "robot_news", # 规定频道名称（Topic）叫 "robot_news"
            10            # 队列大小：如果发得太快，最多缓存10条消息
            )

        # 创建一个定时器：每 0.5 秒执行一次 self.publish_news 这个函数
        self.timer_ = self.create_timer(0.5, self.publish_news)

    

        # 在终端打印一条日志，告诉我们程序跑起来了
        self.get_logger().info("Robot News has been started")

    def publish_news(self):
        # 这里的逻辑是定时器触发后要做的事
        msg = String()      # 创建一个空白的 String 消息对象
        msg.data = "Hello, this is" + self.robot_name_+ "from the robot news station"  # 给消息填入内容 "Hello"
        self.publisher_.publish(msg) # 真正把消息发送出去


def main(args=None):
    rclpy.init(args=args)      # 1. 初始化 ROS 2 通信系统
    node = RobotNewsStationNode() # 2. 实例化我们上面写的那个类
    rclpy.spin(node)           # 3. 让程序进入“死循环”，等待定时器触发或处理事件
    rclpy.shutdown()           # 4. 当我们手动关闭程序时，清理资源



if __name__ == "__main()__":
    main() # 你的代码里原本写的是 main，注意这里需要加括号 () 才能运行
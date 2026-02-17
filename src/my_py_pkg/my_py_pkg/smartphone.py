#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class SmartphoneNode(Node): 
    def __init__(self):
        super().__init__("smartphone") 
        self.subsriber_ = self.create_subscription(
            String, #消息类型，必须和publisher发送的消息类型一致
            "robot_news",#主题名称，必须和对应publisher的主题名字一致
            self.callback_robot_news, #回调函数，收到信息后做的事
            10 #队列大小
            )
        
        self.get_logger().info("Smartphone has been started")#初始化提示

    def callback_robot_news(self, msg:String):# explicit type
        #callback_topicname
        self.get_logger().info(msg.data) 

    
def main(args=None):
    rclpy.init(args=args)
    node = SmartphoneNode() 
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main
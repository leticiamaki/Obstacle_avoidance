#include<ros/ros.h>
#include<std_msgs/Float32.h>
#include<geometry_msgs/Twist.h>

ros::Publisher twist_pub; // AMBOS USAM PUB 


void fcnCallback(const std_msgs::Float32ConstPtr &msg){
    ROS_INFO("Recebi: %f", msg->data);
    geometry_msgs::Twist twist_msg; 
    double w, v;
    if(msg->data > 0){
        w = 1;
        v = 0;        
    }
    else{
        v = 1;
        w = 0; 
    }
    twist_msg.linear.x = v;
    twist_msg.angular.z = w; 
    twist_pub.publish(twist_msg);   // PUBLICANDO
}

int main(int argc, char **argv){
    
    //std_msgs::Float32 msg;
    
    ros::init(argc, argv, "simple_avoidance");
    
    ros::NodeHandle node; 
    
    ros::Subscriber sonar_sub = node.subscribe("vrep/vehicle/frontSonar", 1, fcnCallback);  // pegando os dados do sensor
    
    twist_pub = node.advertise<geometry_msgs::Twist>("obstacle/twist", 1);    //topic name  , declaração do publicador
    
    ros::spin();
    
    return 0;
}
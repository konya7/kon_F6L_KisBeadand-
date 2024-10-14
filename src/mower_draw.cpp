#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include <chrono>

class MowerDraw : public rclcpp::Node
{
public:
    MowerDraw() : Node("mower_draw"), count_(0), x(0), y(0), theta(0)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        subscriber_ = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose", 10, std::bind(&MowerDraw::pose_callback, this, std::placeholders::_1));
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100), std::bind(&MowerDraw::loop, this));

        RCLCPP_INFO_STREAM(this->get_logger(), "Starting the mower simulation in turtlesim.");
    }

private:
    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        x = msg->x;
        y = msg->y;
        theta = msg->theta;
        RCLCPP_INFO(this->get_logger(), "Pose - X: %.2f, Y: %.2f, Theta: %.2f", x, y, theta);
    }

    void publish_message(double fwd, double turn)
    {
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = fwd;
        message.angular.z = turn;
        count_++;

        RCLCPP_INFO(this->get_logger(), "Step %ld. Speed: %.1f, Turn: %.1f", count_, fwd, turn);
        publisher_->publish(message);
    }

    void loop()
    {
        if (count_ >= 20) { // Például 20 lépés után leáll
            RCLCPP_INFO_STREAM(this->get_logger(), "Mower simulation finished.");
            rclcpp::shutdown();
            return;
        }

        // Fűnyíró mozgás logika
        if (count_ % 4 == 0) {
            publish_message(1.0, 0.0); // Haladjon előre
        } else {
            publish_message(0.0, M_PI_2); // Forduljon 90 fokot
        }
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
    double x, y, theta;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MowerDraw>());
    rclcpp::shutdown();
    return 0;
}

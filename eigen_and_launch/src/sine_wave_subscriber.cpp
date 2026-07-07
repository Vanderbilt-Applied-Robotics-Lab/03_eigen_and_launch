#include <eigen_and_launch/sine_wave_subscriber.h>

SineWaveSubscriber::SineWaveSubscriber() : Node("sine_wave_subscriber")
{
    // create subscribers
    subscriber_ = this->create_subscription<eigen_and_launch::msg::SineWaveStamped>("/sine_wave", 10, 
        std::bind(&SineWaveSubscriber::sineWaveCallback, this, std::placeholders::_1));

    // create constant matrix
    mat_ << 1, 2, 3, 4;
}

void SineWaveSubscriber::sineWaveCallback(const eigen_and_launch::msg::SineWaveStamped & msg)
{
    vec_ << msg.wave_value, std::pow(msg.wave_value, 2);
    z_k_ = mat_*vec_;
    RCLCPP_INFO(this->get_logger(), "z_k(1): %0.2f, z_k(2): %0.2f, message time: %f", z_k_[0], z_k_[1], rclcpp::Time(msg.header.stamp).seconds());
}

int main(int argc, char * argv[])
{
    // initialize the node
    rclcpp::init(argc, argv);

    // create instance of class
    auto node = std::make_shared<SineWaveSubscriber>();

    // MAIN LOOP
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

#include <eigen_and_launch/sine_wave_publisher.h>

SineWavePublisher::SineWavePublisher(float angular_frequency, float amplitude) : 
    Node("sine_wave_publisher"), 
    angular_frequency_(angular_frequency),
    amplitude_(amplitude)
{
    publisher_ = this->create_publisher<eigen_and_launch::msg::SineWaveStamped>("/sine_wave", 10); 

    start_time_ = this->get_clock()->now();
}

void SineWavePublisher::publishSineWave()
{
    
    // time since start of node
    double t = (this->get_clock()->now() - start_time_).seconds();
    
    // calculate sine wave
    msg_.wave_value = amplitude_*std::sin(angular_frequency_*t);

    msg_.header.stamp = this->get_clock()->now();

    // publish message
    publisher_->publish(msg_);
}

int main(int argc, char * argv[])
{
    // initialize the node
    rclcpp::init(argc, argv);

    // parse launch arguments
    float angular_frequency = std::stof(argv[1]);
    float amplitude = std::stof(argv[2]);

    // create instance of class
    auto node = std::make_shared<SineWavePublisher>(angular_frequency, amplitude);

    // Set loop rate
    rclcpp::Rate rate = rclcpp::Rate(100); // Hz

    // MAIN LOOP
    while (rclcpp::ok())
    {
        node->publishSineWave();
        rclcpp::spin_some(node); // updates publishers and subscribers
        rate.sleep();
    }
    rclcpp::shutdown();
    return 0;
}

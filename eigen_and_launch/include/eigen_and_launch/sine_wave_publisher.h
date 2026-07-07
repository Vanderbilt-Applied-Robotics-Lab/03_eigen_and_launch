#ifndef SINE_WAVE_PUBLISHER
#define SINE_WAVE_PUBLISHER

#include <rclcpp/rclcpp.hpp>
#include <eigen_and_launch/msg/sine_wave_stamped.hpp>
/**
 * Publishes a sine wave to the /sine_wave topic
 * Applied Robotics
 * Author: Garrison Johnston
 */
class SineWavePublisher : public rclcpp::Node
{
public:
    // constructor
    SineWavePublisher(float angular_frequency, float amplitude);

    // destructor
    ~SineWavePublisher() = default;

    // publishes the sine wave
    void publishSineWave();

private:
    // publisher object
    rclcpp::Publisher<eigen_and_launch::msg::SineWaveStamped>::SharedPtr publisher_;

    // output message
    eigen_and_launch::msg::SineWaveStamped msg_ = eigen_and_launch::msg::SineWaveStamped();
    
    // Time at start of node
    rclcpp::Time start_time_;
    
    // members that will get specified from launch argument
    float angular_frequency_;
    float amplitude_;
};

#endif // SINE_WAVE_PUBLISHER
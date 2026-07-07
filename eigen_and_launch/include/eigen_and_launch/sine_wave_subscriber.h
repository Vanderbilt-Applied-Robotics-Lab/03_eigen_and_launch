#ifndef SINE_WAVE_SUBSCRIBER
#define SINE_WAVE_SUBSCRIBER

#include <rclcpp/rclcpp.hpp>
#include <Eigen/Dense>
#include <eigen_and_launch/msg/sine_wave_stamped.hpp>

/**
 * Subscribes to /sine_wave topic and prints to terminal
 * Applied Robotics
 * Author: Garrison Johnston
 */
class SineWaveSubscriber : public rclcpp::Node
{
public:
    SineWaveSubscriber();
    ~SineWaveSubscriber() = default;

private:
    // runs automatically when sine wave topic updates
    void sineWaveCallback(const eigen_and_launch::msg::SineWaveStamped & msg);

    // Publishers/subscribers
    rclcpp::Subscription<eigen_and_launch::msg::SineWaveStamped>::SharedPtr subscriber_;

    // initialize members
    Eigen::Vector2d z_k_;
    Eigen::Vector2d vec_;
    Eigen::Matrix2d mat_;
};

#endif // SINE_WAVE_SUBSCRIBER
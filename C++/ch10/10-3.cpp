#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <functional>

struct SpeedUpdate {
    double velocity_mps;
};

struct CarDetected {
    double distance_m;
    double velocity_mps;
};

struct BrakeCommand {
    double time_to_collision_s;
};

//Interface for service. Callbacks are function pointers
using SpeedUpdateCallback = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback = std::function<void(const CarDetected&)>;

struct IServiceBus {
    virtual ~IServiceBus() = default;
    virtual void publish(const BrakeCommand&) = 0;
    virtual void subscribe(SpeedUpdateCallback) = 0;
    virtual void subscribe(CarDetectedCallback) = 0;
};

struct MockServiceBus: IServiceBus {
    void publish(const BrakeCommand& cmd) override {
        commands_published++;
        last_command = cmd;
    }
    void subscribe(SpeedUpdateCallback callback) override {
        speed_update_callback = callback;
    }
    void subscribe(CarDetectedCallback callback) override {
        car_detected_callback = callback;
    }
    BrakeCommand last_command{};
    int commands_published{};
    SpeedUpdateCallback speed_update_callback{};
    CarDetectedCallback car_detected_callback{};
};

struct AutoBrake {
    AutoBrake(IServiceBus& bus) 
        :   collision_threshold_s{ 5 },
            speed_mps{} {
            //this is the callback passed to bus object.. to be involked
            bus.subscribe([this] (const SpeedUpdate& update) {
                speed_mps = update.velocity_mps;
            });
            bus.subscribe([this, &bus] (const CarDetected& cd) {
                const auto relative_velocity_mps = speed_mps - cd.velocity_mps;
                const auto time_to_collision_s = cd.distance_m / relative_velocity_mps;
                if (time_to_collision_s > 0 && time_to_collision_s <= collision_threshold_s) {
                    bus.publish(BrakeCommand{ time_to_collision_s });
                }
            });
    }
    void set_collision_threshold_s(double x) {
        if (x < 1) throw std::domain_error{ "Collision less than 1" };
        collision_threshold_s = x;
    }
    double get_collision_threshold_s() const {
        return collision_threshold_s;
    }
    double get_speed_mps() const {
        return speed_mps;
    }
private:
    double collision_threshold_s;
    double speed_mps;
};

// UNIT TESTS

TEST_CASE("AutoBrake") {
    //setup will be used (and re-initialized) for each section
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };

    SECTION("initializes speed to zero") {
        REQUIRE(auto_brake.get_speed_mps() == Approx(0));
    }

    SECTION("initializes sensitivity to five") {
        REQUIRE(auto_brake.get_collision_threshold_s() == Approx(5));
    }

    SECTION("throws when sensitivity less than one") {
        REQUIRE_THROWS(auto_brake.set_collision_threshold_s(0.5L));
    }

    SECTION("saves speed after update") {
        bus.speed_update_callback(SpeedUpdate{ 100L });
        REQUIRE(100L == auto_brake.get_speed_mps());
        bus.speed_update_callback(SpeedUpdate{ 50L });
        REQUIRE(50L == auto_brake.get_speed_mps());
        bus.speed_update_callback(SpeedUpdate{ 0L });
        REQUIRE(0L == auto_brake.get_speed_mps());
    }

    SECTION("no alert when not imminent") {
        auto_brake.set_collision_threshold_s(2L);
        bus.speed_update_callback(SpeedUpdate { 100L });
        bus.car_detected_callback(CarDetected{ 1000L, 50L });
        REQUIRE(bus.commands_published == 0);
    }

    SECTION("alert when imminent") {
        auto_brake.set_collision_threshold_s(10L);
        bus.speed_update_callback(SpeedUpdate{ 100L });
        bus.car_detected_callback(CarDetected{ 100L, 0L });
        REQUIRE(bus.commands_published == 1);
        REQUIRE(bus.last_command.time_to_collision_s == Approx(1));
    }
}
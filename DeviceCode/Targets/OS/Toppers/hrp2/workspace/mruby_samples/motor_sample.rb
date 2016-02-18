include EV3RT_TECS
begin
    LCD.font=:medium
    LCD.draw("motor sample", 0, 0)
    # Sensors and Actuators
    left_port  = :port_a
    right_port = :port_b
    ultrasonic_port = :port_3
    LCD.draw("left  motor:#{left_port}  ", 0, 2)
    LCD.draw("right motor:#{right_port}  ", 0, 3)
    LCD.draw("ultrasonic :#{ultrasonic_port}", 0, 4)
    $left_motor = Motor.new(left_port) 
    $right_motor = Motor.new(right_port)
    $ultrasonic_sensor = UltrasonicSensor.new(ultrasonic_port)
    loop{
        distance = $ultrasonic_sensor.distance
        LCD.draw("distance = #{distance}  ", 0, 6)
        
        if distance < 15 then
            $left_motor.stop 
            $right_motor.stop 
        else
            $left_motor.power=30
            $right_motor.power=30
        end
    }
rescue => e
    LCD.error_puts e
end    

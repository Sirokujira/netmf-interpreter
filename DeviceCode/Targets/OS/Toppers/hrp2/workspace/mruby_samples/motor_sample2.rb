include EV3RT_TECS
begin
    LCD.puts "motor sample"
    motor_port  = :port_a
    #Sensors and Actuators
    LCD.puts "motor port:#{motor_port}"

    $motor = Motor.new(motor_port) 

    LCD.puts "motor type is #{$motor.type}"
    $motor.reset_count
    LCD.puts "motor count = #{$motor.count}"

    $motor.rotate( 180, 10, true)
    LCD.puts "motor count = #{$motor.count}"
    $motor.reset_count
    LCD.puts "motor count = #{$motor.count}"
    
rescue => e
    LCD.error_puts e
end 


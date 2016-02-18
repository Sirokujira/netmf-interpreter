include EV3RT_TECS

begin
    LCD.font=:medium
    
    color_port = :port_4
    
    LCD.draw("color sample", 0, 0)
    LCD.draw("port #{color_port}", 0, 2)
    
    $color_sensor = ColorSensor.new(color_port)
    loop{
        color = $color_sensor.reflect
        LCD.draw("color reflect = #{color}  ", 0, 5)
    }
rescue => e
    LCD.error_puts e
end


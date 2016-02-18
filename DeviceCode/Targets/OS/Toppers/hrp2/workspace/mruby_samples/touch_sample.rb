include EV3RT_TECS

begin
    LCD.font= :medium
    
    LCD.draw("touch sample", 0,1)
    
    touch_port = :port_4
    
    LCD.draw("touch:#{touch_port}", 0, 2)
    $touch_sensor = TouchSensor.new(touch_port)
    
    count = 0
    loop{    
        LCD.draw("touch count:#{count}", 0, 5)
        while !$touch_sensor.pressed?  do end
        while $touch_sensor.pressed?  do end
        count = count + 1
    }
rescue => e
    LCD.error_puts e
end


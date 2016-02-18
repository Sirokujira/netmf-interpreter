include EV3RT_TECS

begin
    LCD.font=:medium
    
    LCD.draw("battery sample", 0, 0) 
    
    loop{
        LCD.draw("battery mA::#{Battery.mA}", 0, 2)
        LCD.draw("battery mV::#{Battery.mV}", 0, 3)
    }
rescue => e
    LCD.error_puts e
end

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity test_pwm is
end test_pwm;

architecture Behavioral of test_pwm is

component pwm is
    Port ( ck : in STD_LOGIC; -- system clock
           duty_set : in STD_LOGIC_VECTOR (7 downto 0); -- presettable duty cycle (0...255)/256
           Nfckpwm_set : in STD_LOGIC_VECTOR (7 downto 0); 
		   -- PWM clock division ratio (1...255) (fpwm=fck/(256*(Nfckpwm_set+1)), Nfckpwm_set>0
           pwm_out : out STD_LOGIC_VECTOR (0 downto 0); -- PWM output signal, declare as 1-bit vector for monitoring with the ILA
           led : out STD_LOGIC); -- LED PWM output signal
end component;

signal ck,led : STD_LOGIC;
signal pwm_out : STD_LOGIC_VECTOR (0 downto 0);
signal duty_set,Nfckpwm_set : STD_LOGIC_VECTOR (7 downto 0);

begin

gen_ck: process
begin
    ck <= '0'; wait for 5ns;
    ck <= '1'; wait for 5ns;
end process;


gen_Npre: process
begin
    Nfckpwm_set <= "00100110"; wait for 3060us; -- set 38 --> fpwm=10kHz
    Nfckpwm_set <= "00000111"; wait for 3060us; -- set 7 --> fpwm=50kHz
end process;

gen_duty: process
begin
    duty_set <= "01010100"; wait for 1530us; -- set 33% --> 84 of 256
    duty_set <= "10011010"; wait for 1530us;  -- set 60% -->154 of 256
end process;

dut: pwm port map (ck=>ck, duty_set=>duty_set, Nfckpwm_set=>Nfckpwm_set, pwm_out=>pwm_out, led=>led);

end Behavioral;

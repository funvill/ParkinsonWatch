# ParkinsonWatch
A clone of [EmmaWatch](http://mashable.com/2017/05/10/microsoft-emma-watch-helps-woman-with-parkinsons-write-again/#duz6bHiLZOqT) to help reduce the shakes from Parkinsons 

This Arduino sketch works with a armband with 4 pager motors embedded into a elastic strap. Each motor is connected to a separate digital input. There are two patterns programmed into the armband. The settings for each pattern can be changed via serial commands to fine tune the settings for the particular person.  

Serial messages must end with "#" and contain 1 pattern and 2-3 parameters. 

**Patterns:**
- Sequential (1) - Each loop the next motor in the sequence will be turned on. 
   - Parameter 1 - Length of the motor on. Units in miliseconds 
   - Parameter 2 - Length of the motor off. Units in miliseconds 
- Random (2) - Motors are randomly turned on and off. 
   - Parameter 1 - Length of the motor on. Units in miliseconds 
   - Parameter 2 - Length of the motor off. Units in miliseconds 
   - Parameter 3 - The amount of motors that are randomly turned on each loop. 

**Example:**

2, 100, 500, 1#

In this example the armband will be switched to the random pattern (2) 0.1 second motor run time with a pause of 0.5 seconds and one motor active at a time.
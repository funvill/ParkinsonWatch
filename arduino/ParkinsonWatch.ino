/** 
 * Written by: Steven Smethurst 
 * Twitter: @funvill 
 * 
 * For more information 
 * https://github.com/funvill/ParkinsonWatch
 */ 

class CMotorController {

private:
    static const int MOTOR_MAX_MOTORS = 5;

    // Patterns 
    static const int PATTERN_SEQUENCE = 1;
    static const int PATTERN_RANDOM = 2;

    int motors[MOTOR_MAX_MOTORS];
    int motorCount;

    unsigned int pattern;
    unsigned int argumentOne;
    unsigned int argumentTwo;
    unsigned int argumentThree;

    // false == motor off
    // True == motor on
    void SetMotor(unsigned int motorOffset, bool state = true)
    {
        Serial.println("FYI: CMotorController::SetMotor motorOffset=[" + String(motorOffset) + "] state=[" + String(state ? "On" : "Off") + "]");
        digitalWrite(this->motors[motorOffset], (state ? HIGH : LOW));
    }

    void SetAllMotors(bool state = true)
    {
        Serial.println(" FYI: CMotorController::SetAllMotors");

        for (unsigned int motorOffset = 0; motorOffset < this->motorCount; motorOffset++) {
            this->SetMotor(motorOffset, state);
        }
    }

public:
    CMotorController()
    {
        this->motorCount = 0;
    }

    bool AddMotor(int pin)
    {
        if (this->motorCount >= MOTOR_MAX_MOTORS) {
            return false;
        }

        Serial.println("FYI: CMotorController::AddMotor");

        // ToDo: Check to see if this motor has already been added.
        this->motors[this->motorCount++] = pin;
        return true;
    }

    void SetupMotors()
    {
        Serial.println("FYI: CMotorController::Setup");

        // Set the pins for the motors.
        for (unsigned int motorOffset = 0; motorOffset < this->motorCount; motorOffset++) {
            pinMode(this->motors[motorOffset], OUTPUT);
        }

        this->SetAllMotors(false);

        // this->Configure( PATTERN_RANDOM, 20,2,0);
        this->Configure(PATTERN_SEQUENCE, 100, 10, 0);
    }

    bool Configure(const unsigned int pattern, const unsigned int argumentOne = 0, const unsigned int argumentTwo = 0, const unsigned int argumentThree = 1)
    {
        // Serial.println("FYI: CMotorController::Configure pattern=["+ String(pattern) +"],  pattern=["+ String(argumentOne) +"],  pattern=["+ String(argumentTwo) +"],  pattern=["+ String(argumentThree) +"]");

        this->pattern = pattern;
        this->argumentOne = argumentOne;
        this->argumentTwo = argumentTwo;
        this->argumentThree = argumentThree;
        return true;
    }

    void Loop()
    {
        switch (pattern) {
            case PATTERN_SEQUENCE: {
                Serial.println("FYI: Doing PATTERN_SEQUENCE");
                /**
                 * Turn all off 
                 * Turn motor n motor on 
                 * delay with motor on 
                 * n++ 
                 * 
                 * Parameters 
                 * - argumentOne - Period on 
                 * - argumentTwo - Period off 
                 * - argumentThree - Not used. 
                 *
                 * Example: 
                 *  1,1000,500#  
                 */

                this->SetAllMotors(false);
                delay(argumentTwo);

                static unsigned int motorOffset = 0;
                motorOffset++;
                if (motorOffset >= this->motorCount) {
                    motorOffset = 0;
                }
                this->SetMotor(motorOffset, true);
                delay(argumentOne);

                break;
            }
            default:
            case PATTERN_RANDOM: {
                Serial.println("FYI: Doing PATTERN_RANDOM");
                /**
                 * Turn all motors off. 
                 * Turn a random motor on 
                 * Wait nnnn amount of time and loop. 
                 * 
                 * Parameters 
                 * - argumentOne - Delay between randomly changing the motors. 
                 * - argumentTwo - Delay off 
                 * - argumentThree - The count of random motors that will be turned on each session.                  
                 *
                 * Example: 
                 *  2,100,500,1#
                 */
                this->SetAllMotors(false);
                delay(argumentTwo);
                for (unsigned int count = 0; count < argumentThree; count++) {
                    this->SetMotor(random(0, this->motorCount), true);
                }
                delay(argumentOne);
                break;
            }
        }
    }
};
CMotorController gMotors;

void ParseMessage(char* buffer, unsigned int bufferSize)
{
    Serial.println("");
    Serial.println("FYI: ParseMessage. buffer=[" + String(buffer) + "],  bufferSize=[" + String(bufferSize) + "]");

    char* strtokIndx = strtok(buffer, ",");
    if (strtokIndx != NULL) {
        unsigned int pattern = atoi(strtokIndx);
        strtokIndx = strtok(NULL, ",");
        if (strtokIndx != NULL) {
            unsigned int argumentOne = atoi(strtokIndx);
            strtokIndx = strtok(NULL, ",");
            if (strtokIndx != NULL) {
                unsigned int argumentTwo = atoi(strtokIndx);
                strtokIndx = strtok(NULL, ",");
                if (strtokIndx != NULL) {
                    unsigned int argumentThree = atoi(strtokIndx);
                    strtokIndx = strtok(NULL, ",");

                    // Update the command. Three
                    Serial.println("FYI: pattern[" + String(pattern) + "], argumentOne[" + String(argumentOne) + "], argumentTwo[" + String(argumentTwo) + "], argumentThree[" + String(argumentThree) + "]");
                    gMotors.Configure(pattern, argumentOne, argumentTwo, argumentThree);
                } else {
                    // Update the command. Two
                    Serial.println("FYI: pattern[" + String(pattern) + "], argumentOne[" + String(argumentOne) + "], argumentTwo[" + String(argumentTwo) + "]");
                    gMotors.Configure(pattern, argumentOne, argumentTwo);
                }
            } else {
                Serial.println("FYI: ParseMessage. Could not get argumentTwo");
            }
        } else {
            Serial.println("FYI: ParseMessage. Could not get argumentOne");
        }
    } else {
        Serial.println("FYI: ParseMessage. Could not get pattern");
    }
}

static const int MAX_INPUT_BUFFER_LENGTH = 100;
char inputBuffer[MAX_INPUT_BUFFER_LENGTH];
void CheckInput()
{
    // Check to see if there is anything on the input
    while (Serial.available() > 0) {
        // Read the byte
        char reciveByte = Serial.read();
        Serial.print(reciveByte);

        // Add the byte to the buffer if there is room
        static unsigned int inputBufferSize = 0;
        if (inputBufferSize > MAX_INPUT_BUFFER_LENGTH) {
            // Buffer overflow, Start over
            inputBufferSize = 0;
        }
        inputBuffer[inputBufferSize++] = reciveByte;

        // Check to see if this a full string.
        if (reciveByte == '#') {
            // End of message
            inputBuffer[inputBufferSize] = 0; // NULL
            ParseMessage(inputBuffer, inputBufferSize);
            inputBufferSize = 0;
        }
    }
}


void setup()
{
    // put your setup code here, to run once:

    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.println("FYI: Setting up the motors");

    gMotors.AddMotor(3);
    gMotors.AddMotor(4);
    gMotors.AddMotor(5);
    gMotors.AddMotor(6);
    gMotors.SetupMotors();

    Serial.println("FYI: Done Setup");
}

void loop()
{
    // put your main code here, to run repeatedly:
    CheckInput();
    gMotors.Loop();
}
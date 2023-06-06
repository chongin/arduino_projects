

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

enum CommandEnum
{
  None = 0x00,
  Left = 0x01,
  Right = 0x02,
  Up = 0x04,
  Down = 0x08
};

class JoyStick
{
public:
  JoyStick()
  {
    _current_command = CommandEnum::None;
  }

  CommandEnum CurrentCommand()
  {
    return _current_command;
  }

  void SetCurrentCommand(CommandEnum command)
  {
    _current_command = command;
  }

  String GetCommandStr()
  {
    String str = "";
    switch(_current_command)
    {
      case CommandEnum::None:
        str = "None";
        break;
      case CommandEnum::Left:
        str = "Left";
        break;
      case CommandEnum::Right:
        str = "Right";
        break;
      case CommandEnum::Up:
        str = "Up";
        break;
      case CommandEnum::Down:
        str = "Down";
        break;
    }
    return str;
  }

  void UpdateCommand()
  {
    int x_value = analogRead(VRX_PIN);
    int y_value = analogRead(VRY_PIN);
    printXY(x_value, y_value);

    if (x_value < LEFT_THRESHOLD)
      _current_command = CommandEnum::Left;
    else if (x_value > RIGHT_THRESHOLD)
      _current_command = CommandEnum::Right;
    if (y_value < UP_THRESHOLD)
      _current_command = CommandEnum::Up;
    else if (y_value > DOWN_THRESHOLD)
      _current_command = CommandEnum::Down;
    else
      _current_command = CommandEnum::None;

  }

private:
  void printXY(int x, int y)
  {
    Serial.print("x:");
    Serial.print(x);
    Serial.print(",");
    Serial.print("y:");
    Serial.print(y);
    Serial.println("");
  }
private:
  CommandEnum _current_command;
  int _vx_pin;
  int _vy_pin;
};



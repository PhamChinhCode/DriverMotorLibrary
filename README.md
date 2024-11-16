# DriverMotor Library

Thư viện Arduino để điều khiển động cơ bước với khả năng tăng/giảm tốc.

## Tính năng

- Điều khiển tốc độ và hướng động cơ
- Tăng/giảm tốc mượt mà
- Giới hạn tốc độ an toàn
- Enable/disable động cơ

## Cài đặt

1. Tải xuống thư viện (Click vào Code -> Download ZIP)
2. Trong Arduino IDE, chọn Sketch -> Include Library -> Add .ZIP Library
3. Chọn file ZIP vừa tải về

## Sử dụng
  cpp
  #include <DriverMotor.h>
  DriverMotor motor;
  void setup() {
  motor.begin(2, 3, 4); // stepPin=2, dirPin=3, enPin=4
  motor.setSpeedLimits(100, 1000);
  motor.enable();
  }
  void loop() {
  motor.moveDistance(5000, 800);
  while(motor.isRunning()) {
  motor.run();
  }
  delay(1000);
  }

## License

MIT License

## Tác giả

[Tên của bạn]

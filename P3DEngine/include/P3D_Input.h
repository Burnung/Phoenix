#pragma once
#include <memory>
class P3DInput {
public:
	void KeyBoard(int key);
	void MouseButton(int Button, int Actiong, double x, double y);
	void MouseMove(double x, double y);
};
typedef std::shared_ptr<P3DInput> P3DInputPtr;
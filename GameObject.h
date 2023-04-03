#include <Windows.h>
class GameObject
{
public:
	GameObject(float _x, float _y, float _vx, float _vy, 
		HBITMAP _hBitmap = NULL, int _width = 64, int _height = 64, bool _visible = true)
	{
		x = _x; y = _y;
		vx = _vx; vy = _vy;
		hBitmap = _hBitmap;
		width = _width; height = _height;
		visible = _visible;
	}
	void DrawImage(HDC hdc)
	{
		HDC mdc = CreateCompatibleDC(hdc);
		SelectObject(mdc, hBitmap);
		BitBlt(hdc, x - width/2, y - height/2, width, height, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
	}
	void UpdatePhy(int frameTime)
	{
		x += vx * frameTime / 1000;
		y += vy * frameTime / 1000;
	}
	void setX(float _x)
	{
		x = _x;
	}
	void setY(float _y)
	{
		y = _y;
	}
	void setVx(float _vx)
	{
		vx = _vx;
	}
	void setVy(float _vy)
	{
		vy = _vy;
	}
private:
	float x, y;
	float vx, vy;
	HBITMAP hBitmap;
	int width, height;
	bool visible;
};


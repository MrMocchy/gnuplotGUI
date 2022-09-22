#pragma once

class gui{
public:

	static inline Color textColor;
	static inline Color backgroundColor;

	static void Init() {
		textColor = Palette::Black;
		backgroundColor = Palette::White;
	}


};


class gp {

public:
	static inline TextEditState function;

	static inline TextEditState xrangeMin;
	static inline TextEditState xrangeMax;
	static inline TextEditState yrangeMin;
	static inline TextEditState yrangeMax;

	static inline TextEditState xlabel;
	static inline TextEditState ylabel;


	static void Init() {
		function.text = U"x**2";

	}
};

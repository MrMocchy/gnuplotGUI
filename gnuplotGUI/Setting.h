#pragma once

class gui{
public:

	static inline ColorF textColor;
	static inline ColorF backgroundColor;

	static inline bool gridOn;
	static inline bool darkMode;

	static void Init() {
		textColor = Palette::Black;
		backgroundColor = Palette::White;
		gridOn = true;
		darkMode = false;
	}


};

template <class T>
class withBool{
public:
	bool b = false;
	T v;

	void set(T _v) {
		v = _v;
		b = true;
	}

	withBool(){}
	withBool(T _v) {
		v = _v;
	}
};

class gpLine {
public:
	withBool<HSV> hsv = withBool(HSV{0});
	withBool<double> width;
	withBool<double> dashtype;

};

class gpGraph {
public:
	TextEditState function;
	withBool<TextEditState> title;
	gpLine line;

};

class gp {

public:
	static inline TextEditState function;

	static inline Array<gpGraph> graph;

	static inline TextEditState xrangeMin;
	static inline TextEditState xrangeMax;
	static inline TextEditState yrangeMin;
	static inline TextEditState yrangeMax;

	static inline TextEditState title;
	static inline TextEditState xlabel;
	static inline TextEditState ylabel;

	static inline bool gridOn;


	static void Init() {
		function.text = U"x**2";

		graph.push_back(gpGraph());
		graph[0].function.text = U"x**3";
	}
};

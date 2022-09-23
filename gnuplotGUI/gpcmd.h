#pragma once

#include <stdio.h>
#include <string>

String cmdstr;

void addCmdArg(String str) {
	cmdstr += str + U"\n";
}

void Plot() {


	cmdstr = U"gnuplot\n";

	if (!gp::xrangeMin.text.empty()&& !gp::xrangeMax.text.empty())
		addCmdArg(U"set xrange[" + gp::xrangeMin.text + U":" + gp::xrangeMax.text + U"]");
	if (!gp::yrangeMin.text.empty()&& !gp::yrangeMax.text.empty())
		addCmdArg(U"set yrange[" + gp::yrangeMin.text + U":" + gp::yrangeMax.text + U"]");
	
	if (! gp::title.text.empty()) addCmdArg(U"set title '" + gp::title.text + U"' font 'Meiryo,15'");
	if (! gp::xlabel.text.empty()) addCmdArg(U"set xlabel '" + gp::xlabel.text + U"' font 'Meiryo,15'");
	if (! gp::ylabel.text.empty()) addCmdArg(U"set ylabel '" + gp::ylabel.text + U"' font 'Meiryo,15'");
	
	if (gp::gridOn) addCmdArg(U"set grid");

	//addCmdArg(U"plot " + gp::function.text);

	String str = U"plot ";
	for (int i = 0; i < gp::graph.size(); i++) {
		gpGraph g = gp::graph[i];
		if (g.function.text.empty()) continue;
		str += g.function.text;
		if (! g.title.b) str += U" title '" + g.title.v.text + U"'";
		if (g.line.hsv.b || g.line.dashtype.b || g.line.width.b) {
			str += U" with lines";
			if (g.line.hsv.b) str += U" lc rgb hsv2rgb" + U"({},{},{})"_fmt(g.line.hsv.v.h/360, g.line.hsv.v.s, g.line.hsv.v.v);
			if (g.line.dashtype.b) str += U" dt " + Format((int)g.line.dashtype.v);
			if (g.line.width.b) str += U" lw " + Format((int)g.line.width.v);
		}
		str += U" ,";
	}
	str.pop_back();

	addCmdArg(str);

	Clipboard::SetText(cmdstr);

	system("python cmdwriter.py");



}

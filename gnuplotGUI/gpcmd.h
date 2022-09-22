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
	
	if (! gp::xlabel.text.empty()) addCmdArg(U"set xlabel '" + gp::xlabel.text + U"' font 'Meiryo,15'");
	if (! gp::ylabel.text.empty()) addCmdArg(U"set ylabel '" + gp::ylabel.text + U"' font 'Meiryo,15'");
	

	addCmdArg(U"plot " + gp::function.text);


	Clipboard::SetText(cmdstr);

	system("python cmdwriter.py");



}

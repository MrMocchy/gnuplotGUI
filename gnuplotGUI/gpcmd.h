#pragma once



String cmdstr;

void addCmdArg(String str) {
	cmdstr += U"\"" + str + U"\" ";
}

void Plot() {


	cmdstr = U"python cmdwriter.py gnuplot ";

	if (!gp::xrangeMin.text.empty()&& !gp::xrangeMax.text.empty())
		addCmdArg(U"set xrange[" + gp::xrangeMin.text + U":" + gp::xrangeMax.text + U"]");
	if (!gp::yrangeMin.text.empty()&& !gp::yrangeMax.text.empty())
		addCmdArg(U"set yrange[" + gp::yrangeMin.text + U":" + gp::yrangeMax.text + U"]");
	
	if (! gp::xlabel.text.empty()) addCmdArg(U"set xlabel '" + gp::xlabel.text + U"' font 'Meiryo,15'");
	if (! gp::ylabel.text.empty()) addCmdArg(U"set ylabel '" + gp::ylabel.text + U"' font 'Meiryo,15'");
	

	addCmdArg(U"plot " + gp::function.text);



	system(cmdstr.toUTF8().c_str());
	Console.open();
	Console << cmdstr;


	//Console(str);


}

# include <Siv3D.hpp> // OpenSiv3D v0.6.5
# include <Windows.h>
# include <string.h>
# include "Setting.h"
# include "gpcmd.h"

int32 scroll = 0;
int32 yadd;

Array<TextEditState*> textboxes;

void drawText(String text, Line::value_type x) {
	FontAsset(U"def")(text).draw(Arg::leftCenter = Vec2(x, yadd + scroll), gui::textColor);
}
void drawTextBox(TextEditState &text, Line::value_type x, double width, bool enabled = true) {
	SimpleGUI::TextBoxAt(text, Vec2(x+width/2, yadd + scroll), width, unspecified, enabled);
	textboxes.push_back(&text);
}

void Main()
{
	gui::Init();
	gp::Init();

	Scene::SetBackground(gui::backgroundColor);

	FontAsset::Register(U"def", 30);

	const Font font{ 30 };



	while (System::Update())
	{


		//スクロール部分
		yadd = 70;
		scroll -= Mouse::Wheel()*20;

		//function
		drawText(U"function", 50);
		drawTextBox(gp::function, 200, 500);

		yadd += 50;
		drawText(U"graph", 50);
		for (int i = 0; i < gp::graph.size(); i++) {
			yadd += 50;
			gpGraph *g = &gp::graph[i];
			drawText(Format(i + 1), 50);
			drawText(U"func", 100);
			drawTextBox(g->function, 200, 500);
			yadd += 40;
			drawText(U"title", 100);
			SimpleGUI::CheckBoxAt(g->title.b, U"auto", Vec2(240, yadd + scroll));
			drawTextBox(g->title.v, 300, 300,!g->title.b);
			yadd += 40;
			drawText(U"linewidth", 100);
			SimpleGUI::CheckBoxAt(g->line.width.b, U"", Vec2(270, yadd + scroll));
			SimpleGUI::SliderAt(g->line.width.v, 1, 6, Vec2(400, yadd + scroll), 200.0,g->line.width.b);
			if (g->line.width.b) drawText(Format((int)g->line.width.v), 520);
			yadd += 40;
			drawText(U"dashtype", 100);
			SimpleGUI::CheckBoxAt(g->line.dashtype.b, U"", Vec2(270, yadd + scroll));
			SimpleGUI::SliderAt(g->line.dashtype.v, 1,5, Vec2(400, yadd + scroll), 200.0,g->line.dashtype.b);
			if (g->line.dashtype.b) drawText(Format((int)g->line.dashtype.v), 520);
			yadd += 40;
			drawText(U"linecolor", 100);
			SimpleGUI::CheckBoxAt(g->line.hsv.b, U"", Vec2(270, yadd + scroll));
			SimpleGUI::SliderAt(g->line.hsv.v.h, 0.0, 360.0, Vec2(400, yadd + scroll), 200.0,g->line.hsv.b);
			if(g->line.hsv.b) Rect{ Arg::center(530,yadd + scroll),30 }.draw(g->line.hsv.v);
		}

		yadd += 50;
		if (SimpleGUI::ButtonAt(U"add graph", Vec2(100, yadd + scroll))) {
			gp::graph.push_back(gpGraph());
		}

		//range
		yadd += 50;
		drawText(U"range", 50);
		drawText(U"x[            :            ]", 180);
		drawTextBox(gp::xrangeMin, 210, 100);
		drawTextBox(gp::xrangeMax, 330, 100);
		drawText(U"y[            :            ]", 480);
		drawTextBox(gp::yrangeMin, 510, 100);
		drawTextBox(gp::yrangeMax, 630, 100);

		//title
		yadd += 50;
		drawText(U"title", 50);
		drawTextBox(gp::title, 200, 300);

		//label
		yadd += 50;
		drawText(U"label", 50);
		drawText(U"x", 180);
		drawTextBox(gp::xlabel, 200, 250);
		drawText(U"y", 480);
		drawTextBox(gp::ylabel, 500, 250);

		//grid
		yadd += 50;
		drawText(U"grid", 50);
		SimpleGUI::CheckBoxAt(gp::gridOn, U"use", Vec2(250, yadd + scroll));

		//上部リボン
		Rect(0, 0, 800, 50).draw(gui::backgroundColor);
		Line(0, 50, 800, 50).draw(1,gui::textColor);

		font(U"gnuplot GUI").draw(50,0, gui::textColor);

		SimpleGUI::CheckBoxAt(gui::gridOn, U"grid", Vec2(400, 25));
		if (SimpleGUI::CheckBoxAt(gui::darkMode, U"DarkMode", Vec2(550, 25))) {
			if (gui::darkMode) {
				gui::textColor = Palette::White;
				gui::backgroundColor = Palette::Black;
			}
			else {
				gui::textColor = Palette::Black;
				gui::backgroundColor = Palette::White;
			}
			Scene::SetBackground(gui::backgroundColor);
			
		}

		if (SimpleGUI::ButtonAt(U"plot", Vec2(750,25))) {
			Plot();
		}

		//グリッド
		if (gui::gridOn) {
			for (int x = 100; x < 800; x += 100) {
				Line(x, 0, x, 600).draw(1, ColorF(0, 0, 0, 0.5));
			}
			for (int y = 100; y < 600; y += 100) {
				Line(0, y, 800, y).draw(1, ColorF(0, 0, 0, 0.5));
			}
		}

		//tabでテキストボックス移動
		for (size_t i : step(textboxes.size()-1)) {
			if (textboxes[i]->tabKey) {
				textboxes[i]->active = false;
				textboxes[i+1]->active = true;
			}
		}
		textboxes.clear();

	}
}


//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/tutorial/
//
// Tutorial
// https://siv3d.github.io/tutorial/tutorial/
//
// Siv3D コミュニティへの参加（Discord などで気軽に質問や交流, 最新情報の入手ができます）
// https://siv3d.github.io/ja-jp/community/community/
//
// Siv3D User Community
// https://siv3d.github.io/community/community/
//
// 新機能の提案やバグの報告 | Feedback
// https://siv3d.github.io/ja-jp/develop/report/
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//

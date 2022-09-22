# include <Siv3D.hpp> // OpenSiv3D v0.6.5
# include <Windows.h>
# include <string.h>
# include "Setting.h"
# include "gpcmd.h"

Line::value_type scroll = 0;
Line::value_type yadd;

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

	Scene::SetBackground(Palette::White);

	FontAsset::Register(U"def", 30);

	const Font font{ 30 };

	gui::Init();
	gp::Init();


	while (System::Update())
	{


		//スクロール部分
		yadd = 70;
		scroll -= Mouse::Wheel()*20;

		//function
		drawText(U"function", 50);
		drawTextBox(gp::function, 200, 500);

		//range
		yadd += 50;
		drawText(U"range", 50);
		drawText(U"x[", 170);
		drawTextBox(gp::xrangeMin, 200, 100);
		drawText(U":", 305);
		drawTextBox(gp::xrangeMax, 320, 100);
		drawText(U"]    y[", 420);
		drawTextBox(gp::yrangeMin, 500, 100);
		drawText(U":", 605);
		drawTextBox(gp::yrangeMax, 620, 100);
		drawText(U"]", 720);

		//label
		yadd += 50;
		drawText(U"label", 50);
		drawText(U"x", 180);
		drawTextBox(gp::xlabel, 200, 250);
		drawText(U"y", 480);
		drawTextBox(gp::ylabel, 500, 250);



		//上部リボン

		Rect(0, 0, 800, 50).draw(gui::backgroundColor);
		Line(0, 50, 800, 50).draw(1,gui::textColor);

		font(U"gnuplot GUI").draw(50,0, gui::textColor);

		if (SimpleGUI::ButtonAt(U"plot", Vec2(750,25))) {
			Plot();
		}

		//グリッド
		if (true) {
			for (int x = 100; x < 800; x += 100) {
				Line(x, 0, x, 600).draw(1, ColorF(0, 0, 0, 0.5));
			}
			for (int y = 100; y < 600; y += 100) {
				Line(0, y, 800, y).draw(1, ColorF(0, 0, 0, 0.5));
			}
		}


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

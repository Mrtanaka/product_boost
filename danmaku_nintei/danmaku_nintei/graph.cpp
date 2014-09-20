#include "GV.h"

extern void draw_fps(int,int);

int DrawRotaGraphF( double xd, double yd, double ExRate, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) {
	return DrawRotaGraphF((float)xd,(float)yd,ExRate,Angle,GrHandle,TransFlag,TurnFlag);
}
int DrawModiGraphF( double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int GrHandle, int TransFlag ){
	return DrawModiGraphF( (float)x1, (float)y1, (float)x2, (float)y2, (float)x3, (float)y3, (float)x4, (float)y4, GrHandle, TransFlag ) ;
}

//自機描画
void graph_ch(){
	if(ch.flag!=0){
		if(ch.bcnt > 0){
			double rand = 2.0;
			double ang = PI2/(ch.bcnt%6);
			DrawRotaGraphF( ch.x+(rand*cos(ang)), ch.y+(rand*sin(ang)), 1.0f, 0.0f, img_ch[ch.img], TRUE );
		}else{
			DrawRotaGraphF(ch.x,ch.y,1.0f,0.0f,img_ch[ch.img],TRUE);
		}
		if(CheckStatePad(configpad.slow)>0 && ch.slow_flag==0){ //低速移動中なら当たり判定表示
			DrawRotaGraphF( ch.x, ch.y, 1.0f, 2.0*PI*(count%120)/120, img_etc[0], TRUE );
		}
	}
}

//ボム描画
void graph_bom(){
	if(ch.bcnt > 0){
		double rand = 2.0;
		double ang = PI2/(ch.bcnt%6);
		DrawRotaGraphF(ch.x+(rand*cos(ang)),ch.y+(rand*sin(ang)),1.0f,0.0f,img_bom,TRUE);
	}
}

//敵の描画
void graph_enemy(){
	if(enemy.flag != 0){
		if(ch.bcnt > 0){
			double rand = 2.0;
			double ang = PI2/(ch.bcnt%6);
			DrawRotaGraphF( enemy.x+(rand*cos(ang)), enemy.y+(rand*sin(ang)), 1.0f, 0.0f, img_enemy[enemy.img], TRUE );
		}else{
			DrawRotaGraphF( enemy.x, enemy.y, 1.0f, 0.0f, img_enemy[enemy.img], TRUE );
		}
	}
}

//弾丸の描画
void graph_bullet(){
	int j;
	double disp_angle;
	SetDrawMode( DX_DRAWMODE_BILINEAR );//線形補完描画
	for(j=0;j<BULLET_MAX;j++){//その弾幕が持つ弾の最大数分ループ
		if(bullet[j].flag!=0){//弾データがオンなら
			disp_angle=bullet[j].angle+PI/2;

			DrawRotaGraphF(bullet[j].x, bullet[j].y, 1.0, disp_angle,
				img_bullet[bullet[j].knd][bullet[j].col],TRUE);
		}
	}
	if(ch.bcnt){
		bdelete();
	}
}

//スコアボード表示
void graph_board_states(){
//	int i;
	int graze=ch.graze;
	int percent=int(ch.percent);
	int grade=ch.grade;

	switch(stage){
		case 0:
			DrawFormatString(505,12,color[0],"EASY");
			break;
		case 1:
			DrawFormatString(500,12,color[3],"NORMAL");
			break;
		case 2:
			DrawFormatString(505,12,color[2],"HARD");
			break;
		case 3:
			DrawFormatString(495,12,color[7],"LUNATIC");
			break;
		case 4:
			DrawFormatString(505,12,color[0],"皆伝");
	}

	DrawFormatString(425,42,color[0],"Graze");
	DrawFormatString(425,72,color[0],"達成度");
	DrawFormatString(545,72,color[0],"％");

	DrawFormatString(480,122,color[0],"TYPE");
	switch(type){
		case 0:
			DrawFormatString(525,122,color[0],"A");
			break;
		case 1:
			DrawFormatString(525,122,color[0],"B");
			break;
		case 2:
			DrawFormatString(525,122,color[0],"C");
			break;
	}

	DrawFormatString(425,172,color[0],"認定ゲージ");
	DrawFormatString(575,172,color[0],"％");

	DrawFormatString(425,192,color[0],"BOM %d",ch.bom);

	DrawFormatString(515,42,color[0],"%d",ch.graze);
	DrawFormatString(515,72,color[0],"%d",ch.grade);
	if(ch.percent > 30){
		DrawFormatString(540,172,color[0],"%d",int(ch.percent));
	}else{
		DrawFormatString(540,172,color[2],"%d",int(ch.percent));
	}
	
	//for(i=0;i<4;i++){//グレイズ表示
	//	DrawRotaGraph(550-15*i,50,1.0f,0.0f,img_num[graze%10],TRUE);
	//	graze/=10;
	//}
	//
	//for(i=0;i<3;i++){ //合計達成度表示
	//	DrawRotaGraph(535-15*i,80,1.0f,0.0f,img_num[grade%10],TRUE);
	//	grade/=10;
	//}

	//for(i=0;i<3;i++){ //段位ゲージ表示
	//	DrawRotaGraph(565-15*i,180,1.0f,0.0f,img_num[percent%10],TRUE);
	//	percent/=10;
	//}
	
	DrawStringToHandle(445,230,"弾幕",color[0],font[3]);
	DrawStringToHandle(470,305,"段位",color[0],font[3]);
	DrawStringToHandle(495,380,"認定",color[0],font[3]);
}

//ボード描画
void graph_board(){
	DrawGraph(	0,	0,img_board[0],FALSE);
	DrawGraph(	0, 16,img_board[1],FALSE);
	DrawGraph(	0,464,img_board[2],FALSE);
	DrawGraph(416,	0,img_board[3],FALSE);
}

//タイトル背景描画
void graph_back(){
	DrawGraph(	0,	0,img_board[4],FALSE);
}

//スペル文字・残り時間の描画
void graph_cut(char *string,int length){//スペル名、下線部の長さ
	int t = spcount;

	if(t >= 0 && t < 100){
		DrawStringToHandle(100,215,string,color[0],font[0]);
		DrawLine(100,232,100+length,232,color[2]);
	}

	else{
		DrawStringToHandle(FX,FY,string,color[0],font[0]);
		DrawLine(FX,FY+17,FX+length,FY+17,color[2]);
	}

	DrawFormatStringToHandle(395,FY,color[0],font[0],"%d",(1860-spcount)/60);
}

//スペル文字表示パターンの描画
void graph_spell(){
	if(count == 180	  || count == 2160	|| count == 4140  || count == 6120  || count == 8100 ||
		count == 10080 || count == 12060 || count == 14040 || count == 16020 || count == 18000){
			spcount=0;
			se_flag[5]=1;
	}

	if(count >= 180 && count < 1980){
		graph_cut("Spell１｢低速ばらまき弾｣",215);
	}
	if(count >= 2160 && count < 3960){
		if(stage<=1)
			graph_cut("Spell２｢二段速落下弾｣",195);
		else
			graph_cut("Spell２｢三段速落下弾｣",195);
	}
	if(count >= 4140 && count < 5940){
		graph_cut("Spell３｢交差弾｣",140);
	}
	if(count >= 6120 && count < 7920){
		graph_cut("Spell４｢高速ばらまき弾｣",215);
	}
	if(count >= 8100 && count < 9900){
		graph_cut("Spell５｢回転ワインダー｣",215);
	}
	if(count >= 10080 && count < 11880){
		graph_cut("Spell６｢自機狙い複合弾｣",215);
	}
	if(count >= 12060 && count < 13860){
		if(stage<=3)
			graph_cut("Spell７｢詐欺判定弾｣",175);
		else
			graph_cut("Spell７｢大弾物量殺し｣",195);
	}
	if(count >= 14040 && count < 15840){
		graph_cut("Spell８｢左右ワインダー｣",215);
	}
	if(count >= 16020 && count < 17820){
		if(stage<=1)
			graph_cut("Spell９｢左右＆上下拘束弾｣",235);
		else
			graph_cut("Spell９｢低速移動禁止＆拘束弾｣",275);

	}
	if(count >= 18000 && count < 19800){
		graph_cut("spell１０｢波紋疾走｣",175);
	}

	if(count>=30 && count<180){
		DrawStringToHandle(135,185,"迫る弾幕を",color[0],font[1]);
		DrawStringToHandle(120,225,"避け続けろ！",color[0],font[1]);
	}
	if(spcount>=1800 && sg_flag==1)
		DrawStringToHandle(55,185,"Get Spell Bonus!!",color[0],font[1]);
}

void graph_main(){
	graph_enemy();//敵の描画
	graph_bom();//ボム
	graph_ch();//自機の描画
	graph_bullet();//弾の描画
	graph_board();//ボードの描画
	graph_board_states();//ボード情報の描画
	draw_fps(620,465);//fps描画
	graph_spell();//スペル文字の描画
}

void graph_title(){
	graph_back();

	DrawStringToHandle(140,120,"弾幕段位認定",color[0],font[3]);
	DrawStringToHandle(270,240,"START",color[0],font[1]);
	DrawStringToHandle(220,290,"KEY CONFIG",color[0],font[1]);
	DrawStringToHandle(260,340,"MANUAL",color[0],font[1]);
	DrawStringToHandle(280,390,"QUIT",color[0],font[1]);
	DrawStringToHandle(175,240+(menu_state*50),"→",color[0],font[1]);

	switch(menu_state){
		case 0:
			DrawStringToHandle(255,450,"ゲームを開始します",color[0],font[2]);
			break;
		case 1:
			DrawStringToHandle(190,450,"パッドの各種ボタン設定を変更します",color[0],font[2]);
			break;
		case 2:
			DrawStringToHandle(165,450,"ゲームのルールや操作方法などを表示します",color[0],font[2]);
			break;
		case 3:
			DrawStringToHandle(255,450,"ゲームを終了します",color[0],font[2]);
			break;
	}
}

void graph_pause(){
	graph_board();//ボードの描画
	graph_board_states();//ボード情報の描画
	draw_fps(620,465);//fps描画

	DrawStringToHandle(170,120,"PAUSE",color[0],font[1]);
	//リプレイ再生中は表示名を変更
	if(replay_flag == 1){
		DrawStringToHandle(170,240,"再生を続ける",color[0],font[0]);
		DrawStringToHandle(160,280,"タイトルに戻る",color[0],font[0]);
		DrawStringToHandle(170,320,"最初から再生",color[0],font[0]);
	}else{
		DrawStringToHandle(160,240,"ゲームを続ける",color[0],font[0]);
		DrawStringToHandle(160,280,"タイトルに戻る",color[0],font[0]);
		DrawStringToHandle(160,320,"最初から始める",color[0],font[0]);
	}
	DrawStringToHandle(140,240+(menu_state*40),"→",color[0],font[0]);
}

void graph_result(){
	graph_board();//ボードの描画

	if(count >= 120){
		if(func_state == 3)
			DrawStringToHandle(170,80,"CLEAR",color[0],font[1]);
		else
			DrawStringToHandle(140,80,"GAME OVER",color[0],font[1]);

		DrawStringToHandle(125,160,"難易度",color[0],font[0]);
		switch(stage){
			case 0:
				DrawStringToHandle(295,160,"EASY",color[0],font[0]);
				break;
			case 1:
				DrawStringToHandle(290,160,"NORMAL",color[3],font[0]);
				break;
			case 2:
				DrawStringToHandle(295,160,"HARD",color[2],font[0]);
				break;
			case 3:
				DrawStringToHandle(275,160,"LUNATIC",color[7],font[0]);
				break;
			case 4:
				DrawStringToHandle(295,160,"皆伝",color[0],font[0]);
		}
	}

	if(count >= 180){
		DrawStringToHandle(125,190,"グレイズ回数",color[0],font[0]);
		DrawFormatStringToHandle(290,190,color[0],font[0],"%d",ch.graze);
		DrawStringToHandle(330,190,"回",color[0],font[0]);
	}

	if(count >= 240){
		DrawStringToHandle(125,220,"スペル取得数",color[0],font[0]);
		DrawFormatStringToHandle(310,220,color[0],font[0],"%d",spell);
		DrawStringToHandle(330,220,"回",color[0],font[0]);
	}

	if(count >= 300){
		DrawStringToHandle(125,250,"総合達成度",color[0],font[0]);
		if(func_state == 3){
			int dif[4]={1,3,6,10};//グレイズボーナスの難易度別基準
			int grb = (ch.graze/dif[stage] < 200)? ch.graze/dif[stage]:200;//グレイズボーナス

			ch.grade = int(100 + ((spell*20)+grb)*(ch.percent/100));
		}
		else
			ch.grade = (scount*100)/19800;
		DrawFormatStringToHandle(300,250,color[0],font[0],"%d",ch.grade);
		DrawFormatStringToHandle(330,250,color[0],font[0],"％");

		DrawStringToHandle(125,295,"ランク",color[0],font[0]);
		if(type == 2){
			if(ch.grade >= 250){
				DrawFormatStringToHandle(260,285,color[5],font[1],"AAA+");
			}
			else if(ch.grade >= 200){
				DrawFormatStringToHandle(275,285,color[5],font[1],"AAA");
			}
			else if(ch.grade >= 140){
				DrawFormatStringToHandle(290,285,color[5],font[1],"AA");
			}
			else if(ch.grade >= 100){
				DrawFormatStringToHandle(305,285,color[5],font[1],"A");
			}
			else if(ch.grade >= 60){
				DrawFormatStringToHandle(305,285,color[4],font[1],"B");
			}
			else if(ch.grade >= 30){
				DrawFormatStringToHandle(305,285,color[7],font[1],"C");
			}
			else{
				DrawFormatStringToHandle(305,285,color[0],font[1],"D");
			}
		}
		else{
			if(ch.grade >= 210){
				DrawFormatStringToHandle(275,285,color[5],font[1],"AAA");
			}
			else if(ch.grade >= 150){
				DrawFormatStringToHandle(290,285,color[5],font[1],"AA");
			}
			else if(ch.grade >= 100){
				DrawFormatStringToHandle(305,285,color[5],font[1],"A");
			}
			else if(ch.grade >= 70){
				DrawFormatStringToHandle(305,285,color[4],font[1],"B");
			}
			else if(ch.grade >= 40){
				DrawFormatStringToHandle(305,285,color[7],font[1],"C");
			}
			else{
				DrawFormatStringToHandle(305,285,color[0],font[1],"D");
			}
		}
	}

	if(count >= 330){
		DrawStringToHandle(155,350,"もう一度挑戦する",color[0],font[0]);
		DrawStringToHandle(160,390,"タイトルに戻る",color[0],font[0]);
		DrawStringToHandle(160,430,"リプレイの再生",color[0],font[0]);
		DrawStringToHandle(140,350+(menu_state*40),"→",color[0],font[0]);

		if(ch.grade>=100.0){
			switch(stage){
			case 0:
				DrawStringToHandle(475,190,"EASYクリア",color[0],font[0]);
				DrawStringToHandle(470,210,"おめでとう！",color[0],font[0]);
				DrawStringToHandle(470,260,"慣れてきたら",color[0],font[0]);
				DrawStringToHandle(480,280,"NORMALにも",color[0],font[0]);
				DrawStringToHandle(455,300,"挑戦してみよう！",color[0],font[0]);
				break;
			case 1:
				DrawStringToHandle(465,190,"NORMALクリア",color[0],font[0]);
				DrawStringToHandle(470,210,"おめでとう！",color[0],font[0]);
				DrawStringToHandle(460,260,"余裕があるなら",color[0],font[0]);
				DrawStringToHandle(470,280,"HARDクリアを",color[0],font[0]);
				DrawStringToHandle(455,300,"目指してみよう！",color[0],font[0]);
				break;
			case 2:
				DrawStringToHandle(480,190,"HARDクリア",color[0],font[0]);
				DrawStringToHandle(475,210,"おめでとう！",color[0],font[0]);
				DrawStringToHandle(445,260,"なかなかやりますね",color[0],font[0]);
				DrawStringToHandle(455,280,"貴方にLUNATICは",color[0],font[0]);
				DrawStringToHandle(455,300,"攻略できるかな？",color[0],font[0]);
				break;
			case 3:
				DrawStringToHandle(460,190,"LUNATICクリア",color[0],font[0]);
				DrawStringToHandle(470,210,"おめでとう！",color[0],font[0]);
				DrawStringToHandle(450,260,"難易度選択画面で",color[0],font[0]);
				DrawStringToHandle(460,280,"LキーとRキーを",color[0],font[0]);
				DrawStringToHandle(430,300,"1秒間押し続けると…？",color[0],font[0]);
				break;
			case 4:
				DrawStringToHandle(475,190,"皆伝クリア",color[0],font[0]);
				DrawStringToHandle(470,210,"おめでとう！",color[0],font[0]);
				DrawStringToHandle(480,260,"もう貴方、",color[0],font[0]);
				DrawStringToHandle(425,280,"人間じゃないでしょう？",color[0],font[0]);
				break;
			}
		}
		//推移グラフ
		DrawFormatStringToHandle(475,330,color[0],font[1],"Graph");
		for(int i = 0;(i < 99)&&(ch.percent_graph[i] > 0);i++){
			//推移保持配列から値の取り出し
			int y1 = ch.percent_graph[i];
			int y2 = ch.percent_graph[i+1];
			//取り出した2点の線引き
			DrawLine(475+i,470-y1,475+(i+1),470-y2,color[2]);
		}
		DrawLine(475,470,475,370,color[0]);
		DrawLine(475,470,575,470,color[0]);
	}
}

void graph_difficult(){
	graph_back();

	DrawStringToHandle(140,120,"弾幕段位認定",color[0],font[3]);
	DrawStringToHandle(280,250,"EASY",color[0],font[1]);
	DrawStringToHandle(260,290,"NORMAL",color[3],font[1]);
	DrawStringToHandle(280,330,"HARD",color[2],font[1]);
	DrawStringToHandle(250,370,"LUNATIC",color[7],font[1]);
	DrawStringToHandle(210,250+(menu_state*40),"→",color[0],font[1]);
	
	switch(menu_state){
		case 0:
			DrawStringToHandle(90,450,"眼に優しい難易度です。STGが苦手・やったことない人はこちら。",color[0],font[2]);
			break;
		case 1:
			DrawStringToHandle(75,450,"比較的易しい難易度です。ノーマルシューターならなんとかなるはず。",color[0],font[2]);
			break;
		case 2:
			DrawStringToHandle(100,450,"そこそこ難しい難易度です。回数をこなせばなんとかなるはず。",color[0],font[2]);
			break;
		case 3:
			DrawStringToHandle(50,450,"本気な難易度です。バリバリのシューターさんは高ランクを狙いましょう。",color[0],font[2]);
			break;
	}
}

void graph_type(){
	graph_back();

	DrawStringToHandle(140,120,"弾幕段位認定",color[0],font[3]);
	DrawStringToHandle(265,270,"TYPE A",color[0],font[1]);
	DrawStringToHandle(265,310,"TYPE B",color[0],font[1]);
	DrawStringToHandle(265,350,"TYPE C",color[0],font[1]);
	DrawStringToHandle(225,270+(menu_state*40),"→",color[0],font[1]);
	
	switch(menu_state){
		case 0:
			DrawStringToHandle(170,450,"自機の当たり判定が少し小さくなります",color[0],font[2]);
			break;
		case 1:
			DrawStringToHandle(60,450,"グレイズ時のゲージ回復量・ピンチ時のゲージ減少量に補正がかかります",color[0],font[2]);
			break;
		case 2:
			DrawStringToHandle(10,450,"どちらのボーナスも受けられない代わりに高ランクが取りやすくなります。上級者向け",color[0],font[2]);
			break;
	}
}

void graph_key(){
	graph_back();

	DrawStringToHandle(140,120,"弾幕段位認定",color[0],font[3]);

	DrawStringToHandle(245,240,"決定",color[0],font[1]);
	DrawFormatStringToHandle(390,240,color[0],font[1],"%d",configpad.shot);

	DrawStringToHandle(190,280,"キャンセル",color[0],font[1]);
	DrawFormatStringToHandle(390,280,color[0],font[1],"%d",configpad.bom);

	DrawStringToHandle(205,320,"低速移動",color[0],font[1]);
	DrawFormatStringToHandle(390,320,color[0],font[1],"%d",configpad.slow);

	DrawStringToHandle(225,360,"ポーズ",color[0],font[1]);
	DrawFormatStringToHandle(390,360,color[0],font[1],"%d",configpad.start);

	DrawStringToHandle(180,410,"タイトルに戻る",color[0],font[1]);
	DrawStringToHandle(140,240+(menu_state*40),"→",color[0],font[1]);
}

void graph_manual(){
	graph_back();

	switch(menu_state){
		case 0:
			DrawStringToHandle(200,40,"このゲームは",color[0],font[1]);
			DrawStringToHandle(25,120,"このゲームは、弾幕STG(シューティングゲーム)である｢東方project｣を",color[0],font[0]);
			DrawStringToHandle(25,140,"イメージして制作された、弾幕避けゲームです。",color[0],font[0]);

			DrawStringToHandle(25,180,"プレイヤーは自機を操作し、敵の放つ弾を避け続けてください。",color[0],font[0]);
			DrawStringToHandle(25,200,"10枚のスペルを認定ゲージ(画面右に表示)が尽きないように避け続ける",color[0],font[0]);
			DrawStringToHandle(25,220,"ことができればクリアとなります！",color[0],font[0]);

			DrawStringToHandle(25,280,"全部で4段階の難易度を用意しているので、自分の実力や好みに合わせて",color[0],font[0]);
			DrawStringToHandle(25,300,"選択してください。",color[0],font[0]);

			DrawStringToHandle(25,340,"高い難易度のクリアを目指すのもよし、",color[0],font[0]);
			DrawStringToHandle(25,360,"低い難易度を極めて高ランクを叩きだすのもよしです！",color[0],font[0]);
			break;
		case 1:
			DrawStringToHandle(215,40,"ルール説明",color[0],font[1]);
			DrawStringToHandle(30,110,"認定ゲージを切らさずに10枚のスペルを避け続けることができればクリ",color[0],font[0]);
			DrawStringToHandle(30,130,"ア、途中で認定ゲージが尽きてしまうとゲームオーバーになります。",color[0],font[0]);

			DrawStringToHandle(30,170,"認定ゲージは敵との接触や被弾によって減少し、グレイズ(判定ギリギ",color[0],font[0]);
			DrawStringToHandle(30,190,"リで弾にかすること)によって少しずつ回復していきます。",color[0],font[0]);
			DrawStringToHandle(30,210,"TYPE Bの自機はこのグレイズによる認定ゲージの回復量にボーナスが",color[0],font[0]);
			DrawStringToHandle(30,230,"つきます。",color[0],font[0]);

			DrawStringToHandle(30,270,"また、自機狙い・ワインダー・サイズの小さな弾などは受けるダメージ",color[0],font[0]);
			DrawStringToHandle(30,290,"が少なめに、大弾は受けるダメージが多めになっているので注意しまし",color[0],font[0]);
			DrawStringToHandle(30,310,"ょう。",color[0],font[0]);

			DrawStringToHandle(30,350,"ゲームオーバーになった場合は全体と比べて生き残った時間の割合で、",color[0],font[0]);
			DrawStringToHandle(30,370,"クリアした場合はプレイ内容によって決まる総合達成度と、総合達成度",color[0],font[0]);
			DrawStringToHandle(30,390,"から判定されるクリアランクがリザルト画面に表示されます。",color[0],font[0]);
			DrawStringToHandle(30,410,"(クリアランクは総合達成度に応じてD～AAAまで用意されています。)",color[0],font[0]);
			break;
		case 2:
			DrawStringToHandle(215,40,"難易度説明",color[0],font[1]);

			DrawStringToHandle(30,85,"EASY",color[0],font[4]);
			DrawStringToHandle(30,110,"一番簡単な難易度です。普段からSTGをやっている人には物足りなく感",color[0],font[0]);
			DrawStringToHandle(30,130,"じる難易度ですが、STGをやったことのない人・やるけど苦手な人はま",color[0],font[0]);
			DrawStringToHandle(30,150,"ずこの難易度からプレイしてみて練習してみましょう。",color[0],font[0]);

			DrawStringToHandle(30,180,"NORMAL",color[3],font[4]);
			DrawStringToHandle(30,205,"比較的簡単な方で、標準的な難易度です。ノーマルシューターの人で",color[0],font[0]);
			DrawStringToHandle(30,225,"あればある程度やればクリアが可能になると思います。ノーマルだか",color[0],font[0]);
			DrawStringToHandle(30,245,"らといってSTG未経験の人が迂闊に選択すると痛い目を見ますよ？",color[0],font[0]);

			DrawStringToHandle(30,275,"HARD",color[2],font[4]);
			DrawStringToHandle(30,300,"そこそこ難しい難易度です。HARD以上からは新たな弾幕パターンが追加",color[0],font[0]);
			DrawStringToHandle(30,320,"されるスペルもありますが、ノーマルシュ－ターの人でも十分挑戦でき",color[0],font[0]);
			DrawStringToHandle(30,340,"る難易度だとは思います。LUNATICへの橋渡し・予行演習にもどうぞ。",color[0],font[0]);

			DrawStringToHandle(30,370,"LUNATIC",color[7],font[4]);
			DrawStringToHandle(30,395,"お約束の難易度です。これで伝わらない人は挑戦しない方が無難です。",color[0],font[0]);
			DrawStringToHandle(30,415,"鬼畜難易度ではないので、気合力のある人や鍛えられたシューターであ",color[0],font[0]);
			DrawStringToHandle(30,435,"ればクリアできるはずです。でも、一般人にとってはたぶんクソゲー。",color[0],font[0]);
			break;
		case 3:
			DrawStringToHandle(185,40,"自機タイプ説明",color[0],font[1]);

			DrawStringToHandle(30,100,"TYPE A",color[0],font[4]);
			DrawStringToHandle(30,130,"標準的な機体、霊夢互換です。当たり判定が少し小さくなります。",color[0],font[0]);
			DrawStringToHandle(30,150,"当たり判定縮小化はクリア狙いでも高ランク狙いでも腐りにくい能力で",color[0],font[0]);
			DrawStringToHandle(30,170,"扱いやすいので、迷ったらこのタイプを選べば間違いないでしょう。",color[0],font[0]);

			DrawStringToHandle(30,210,"TYPE B",color[0],font[4]);
			DrawStringToHandle(30,240,"グレイズによる認定ゲージの上昇量が増加し、加えて低空飛行時に被弾",color[0],font[0]);
			DrawStringToHandle(30,260,"した時の認定ゲージの減少量が軽減されます。グレイズを稼げるスペル",color[0],font[0]);
			DrawStringToHandle(30,280,"での回復や終盤戦の低空飛行の粘り強さが強力なクリア向け機体です。",color[0],font[0]);

			DrawStringToHandle(30,320,"TYPE C",color[0],font[4]);
			DrawStringToHandle(30,350,"TYPE AとTYPE Bどちらのボーナスも受けられない代わりにランク上昇",color[0],font[0]);
			DrawStringToHandle(30,370,"に必要な総合達成度が少し軽減されます。安定したクリアができれば、",color[0],font[0]);
			DrawStringToHandle(30,390,"高ランクを取得しやすくなる機体です。また、この機体でのみ極めて高",color[0],font[0]);
			DrawStringToHandle(30,410,"い総合達成度でクリアするとAAA+ランクを取得することができます。",color[0],font[0]);
			break;
		case 4:
			DrawStringToHandle(245,40,"ヒント",color[0],font[1]);
			DrawStringToHandle(30,100,"・認定ゲージが30%未満の時には低空飛行状態となって受けるダメージ",color[0],font[0]);
			DrawStringToHandle(30,120,"　が減少します。最後まで諦めずに避け続けましょう。",color[0],font[0]);

			DrawStringToHandle(30,150,"・総合達成度は、より多くの認定ゲージを残した状態でクリアすること",color[0],font[0]);
			DrawStringToHandle(30,170,"　で上昇します。その他にも、多くのスペルボーナス(1回も被弾せず",color[0],font[0]);
			DrawStringToHandle(30,190,"　にスペルをやりすごすことでボーナスが獲得できます)の獲得数やグ",color[0],font[0]);
			DrawStringToHandle(30,210,"　レイズの回数に応じて上昇していきます。",color[0],font[0]);

			DrawStringToHandle(30,240,"・Spell５は米粒弾のワインダーに合わせて敵の周りを左回りに、",color[0],font[0]);
			DrawStringToHandle(30,260,"　Spell８は米粒弾または楔弾のワインダーに合わせて敵の正面を左右",color[0],font[0]);
			DrawStringToHandle(30,280,"　に動きましょう。この2スペルはワインダーに巻き込まれると手痛い",color[0],font[0]);
			DrawStringToHandle(30,300,"　ダメージを受けるのでワインダーを最優先で避けていきましょう。",color[0],font[0]);

			DrawStringToHandle(30,330,"・Spell７は見た目は変化しますがそのまま大弾が迫ってきています。",color[0],font[0]);
			DrawStringToHandle(30,350,"　見かけに騙されず、弾との適切な距離を保ちましょう。",color[0],font[0]);

			DrawStringToHandle(30,380,"・Spell９は難易度によってパターンと対策が大きく異なります。",color[0],font[0]);
			DrawStringToHandle(30,400,"　NORMAL以下は2列を同時に相手にしないような場所を探しましょう。",color[0],font[0]);
			DrawStringToHandle(30,420,"　HARD以上は一定間隔で出現する大弾からの大ダメージをできるだけ",color[0],font[0]);
			DrawStringToHandle(30,440,"　減らしましょう。低速移動が禁止されている点にも注意です。",color[0],font[0]);
			break;
		case 5:
			DrawStringToHandle(210,40,"クレジット",color[0],font[1]);
			DrawStringToHandle(135, 90,"プログラミング他いろいろ",color[0],font[4]);
			DrawStringToHandle(245,120,"Mrtanaka",color[0],font[4]);
			DrawStringToHandle(210,165,"ライブラリ使用",color[0],font[4]);
			DrawStringToHandle(225,195,"DXライブラリ",color[0],font[4]);
			DrawStringToHandle(130,240,"プログラム参考・画像素材",color[0],font[4]);
			DrawStringToHandle(105,270,"｢龍神録プログラミングの館｣様",color[0],font[4]);
			DrawStringToHandle(210,300,"(http://dixq.net/rp/)",color[0],font[0]);
			DrawStringToHandle(240,335,"効果音素材",color[0],font[4]);
			DrawStringToHandle( 85,365,"そのへんから拾ってきたフリー素材",color[0],font[4]);
			DrawStringToHandle(185,410,"スペシャルサンクス",color[0],font[4]);
			DrawStringToHandle(127,440,"テストプレイヤーのみなさん",color[0],font[4]);
			break;
		case 6:
			DrawStringToHandle(230,40,"コメント",color[0],font[1]);
			DrawStringToHandle(30, 80,"　どうも初めまして、Mrtanakaと申します。",color[0],font[0]);
			DrawStringToHandle(30,100,"普段はルナシューターから音ゲーマー(SDVX)、プロデューサー、提督、",color[0],font[0]);
			DrawStringToHandle(30,120,"クッキー職人、大学生…と、忙しい毎日を過ごしています。",color[0],font[0]);
			DrawStringToHandle(30,140,"　この作品は、私の｢1人の東方シューターとしていつか二次創作かオリ",color[0],font[0]);
			DrawStringToHandle(30,160,"ジナルのSTGを制作してみたい…｣という野望の第一ステップとしてゲー",color[0],font[0]);
			DrawStringToHandle(30,180,"ムシステムや弾幕の構築方法を学ぼうと実験的に制作されたものです。",color[0],font[0]);
			DrawStringToHandle(30,200,"　しっかりとしたSTGを用意するのはどうせ無理だろうと思い、ちょっ",color[0],font[0]);
			DrawStringToHandle(30,220,"とした弾幕ミニゲームというジャンルに落ち着いた今作ですが、ゲーム",color[0],font[0]);
			DrawStringToHandle(30,240,"を作るという行為自体が初めてであった故、随分と苦労させられました。",color[0],font[0]);
			DrawStringToHandle(30,260,"　さて、さらっと軽いノリで制作された(はずなのにけっこう時間かかっ",color[0],font[0]);
			DrawStringToHandle(30,280,"ている)今作ですが、どうだったでしょうか？私としては、今作のテーマ",color[0],font[0]);
			DrawStringToHandle(30,300,"として気合避け系の弾幕ばかりの構成となっていたので、個人差が出たり",color[0],font[0]);
			DrawStringToHandle(30,320,"人によってはつまらない感じになったかなーとは思っていますが…",color[0],font[0]);
			DrawStringToHandle(30,340,"　よければ、｢ここの弾幕はどうだった｣｢これはノーマルじゃない｣",color[0],font[0]);
			DrawStringToHandle(30,360,"などといった感想を伝えてくれると、すっごい嬉しいです。適切な難易度",color[0],font[0]);
			DrawStringToHandle(30,380,"の調整についても、これから学んでいきたいですね。",color[0],font[0]);
			DrawStringToHandle(30,400,"　最後に、わざわざこんなところまで読んでくれた素敵な貴方に感謝。",color[0],font[0]);
			DrawStringToHandle(30,420,"　それでは、素敵な弾幕ライフを…",color[0],font[0]);

			DrawStringToHandle(215,450,"Mrtanaka(@Mrtanaka1)",color[0],font[0]);
			break;
	}
	DrawFormatStringToHandle(590,460,color[0],font[2],"P %d/7",menu_state+1);
}